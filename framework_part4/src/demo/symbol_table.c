/*****************************************************************************
 *
 * Module: symbol_table
 *
 * Prefix: SYM
 *
 * Description: Makes the symbol tables and renames variables
 *
 * @author Carly Hill & Tamme Thijs
 *
 *****************************************************************************/


#include "symbol_table.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "str.h"
#include "memory.h"
#include "ctinfo.h"
#include "types_nodetype.h"


 struct INFO {
  node *root_node;  
  node *funbody;
  node *root_fun_vardec;
  int state;
  int forcount[5];
  char *forvar[5];
  int forinforcount;
  int totalforcount;
};

#define INFO_ROOT_NODE(n) ((n)->root_node)
#define INFO_ROOT_FUNBODY(n) ((n)->funbody)
#define INFO_FUN_VARDEC(n) ((n)->root_fun_vardec)
#define INFO_STATE(n) ((n)->state)
#define INFO_FORCOUNT(n) ((n)->forcount)
#define INFO_FORVARNAME(n) ((n)->forvar)
#define INFO_FORINFORCOUNT(n) ((n)->forinforcount)
#define INFO_TOTALFORCOUNT(n) ((n)->totalforcount)
#define RENAME_STR_SIZE 20


static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_ROOT_NODE( result) = NULL;
  INFO_ROOT_FUNBODY( result) = NULL;
  INFO_FUN_VARDEC( result) = NULL;
  INFO_STATE( result) = 0;
  INFO_FORINFORCOUNT( result) = 0;
  INFO_TOTALFORCOUNT( result) = 0;
  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}

/*
 * Traversal functions
 */

node *SYMprogram( node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMprogram");

  INFO_ROOT_NODE(arg_info) = arg_node;

  PROGRAM_DECLARATIONS(arg_node) =  TRAVdo(PROGRAM_DECLARATIONS( arg_node), arg_info);  

  DBUG_RETURN( arg_node);
}

//traverse over declarations
node *SYMdeclarations( node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMdeclarations");

  DECLARATIONS_DECL( arg_node) = TRAVdo( DECLARATIONS_DECL( arg_node), arg_info);
  DECLARATIONS_NEXT( arg_node) = TRAVopt( DECLARATIONS_NEXT( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}

//rename globaldec and put in program symbol table
node *SYMglobaldec( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMglobaldec");

  char *name;
  char buffer[RENAME_STR_SIZE];

  node *symbol = TBmakeSymbol(GLOBALDEC_TYPE( arg_node), STRcpy(GLOBALDEC_NAME( arg_node)), INFO_STATE(arg_info), TRUE, FALSE, NULL);
  //snprintf(buffer, RENAME_STR_SIZE, "%p_", (void*)&symbol);

  name = STRcpy(SYMBOL_NAME( symbol));
  //SYMBOL_NAME( symbol) = STRcat(buffer , name);
  GLOBALDEC_NAME(arg_node) = SYMBOL_NAME(symbol);

  //if there is no program symboltable then make one.
  if(PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }
  else{
    SYMBOL_NEXT(symbol) = PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }

  MEMfree(name); 

  DBUG_RETURN(arg_node);
}

//change name globaldef and put into symbol table program
node *SYMglobaldef(node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMglobaldef");

  char *name;
  char buffer[RENAME_STR_SIZE];
  node *symbol;
  if(GLOBALDEF_EXPORT(arg_node) == TRUE){
    symbol = TBmakeSymbol(GLOBALDEF_TYPE( arg_node), STRcpy(GLOBALDEF_NAME( arg_node)), INFO_STATE(arg_info), FALSE, TRUE, NULL);
  }
  else{
    symbol = TBmakeSymbol(GLOBALDEF_TYPE( arg_node), STRcpy(GLOBALDEF_NAME( arg_node)), INFO_STATE(arg_info), FALSE, FALSE, NULL);
  }
  
  //snprintf(buffer, RENAME_STR_SIZE, "%p_", (void*)&symbol);

  name = STRcpy(SYMBOL_NAME( symbol));
  //SYMBOL_NAME( symbol) = STRcat(buffer , name);
  GLOBALDEF_NAME(arg_node) = SYMBOL_NAME(symbol);

  //make a symbol table if there is none.
  if(PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }
  else{
    SYMBOL_NEXT(symbol) = PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }

  MEMfree(name); 
  DBUG_RETURN(arg_node);
}

//put function definition in the right fsymboltable
node *SYMfundef( node *arg_node, info *arg_info)
{
  node * fsymbol;
  DBUG_ENTER("SYMfundef");
  INFO_TOTALFORCOUNT(arg_info) = 0;
  if(FUNDEF_EXTERN(arg_node) == TRUE){
    fsymbol =  TBmakeFsymbol(arg_node, FUNDEF_NAME(arg_node), INFO_STATE(arg_info), TRUE, NULL);
  }
  else{
    fsymbol =  TBmakeFsymbol(arg_node, FUNDEF_NAME(arg_node), INFO_STATE(arg_info), FALSE, NULL);
  }
  

//check which type root node is, and make new fsymbol table if there is none
  if( NODE_TYPE(INFO_ROOT_NODE(arg_info)) == N_program){
  
    if(PROGRAM_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      PROGRAM_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = fsymbol;
    }
    else{
      FSYMBOL_NEXT(fsymbol) = PROGRAM_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      PROGRAM_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = fsymbol;
    }
  } 
  else if(NODE_TYPE(INFO_ROOT_NODE(arg_info)) == N_fundef) {
    
     if(FUNDEF_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      FUNDEF_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = fsymbol;
    }
      else{
      FSYMBOL_NEXT(fsymbol) = FUNDEF_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      FUNDEF_FSYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = fsymbol;
    }

  }
  if(FUNDEF_PARAMS(arg_node)!=NULL || FUNDEF_FUNBODY(arg_node) != NULL){

    // // change state root node
    node *tmp = INFO_ROOT_NODE(arg_info);
    INFO_ROOT_NODE(arg_info) = arg_node;

    // increment state in table
    INFO_STATE(arg_info) = INFO_STATE(arg_info)+1;

    // trav params
    FUNDEF_PARAMS( arg_node) = TRAVopt( FUNDEF_PARAMS( arg_node), arg_info);
    FUNDEF_FUNBODY( arg_node) = TRAVopt( FUNDEF_FUNBODY( arg_node), arg_info);

    //set root node back
    INFO_ROOT_NODE(arg_info) = tmp;
    INFO_STATE(arg_info) = INFO_STATE(arg_info)-1;
  }
  DBUG_RETURN(arg_node);
}

//rename param and put in right symbol table
node *SYMparam( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMparam");


  char *name;
  char buffer[RENAME_STR_SIZE];

  node *symbol = TBmakeSymbol(PARAM_TYPE( arg_node), STRcpy(PARAM_NAME( arg_node)), INFO_STATE(arg_info), FALSE, FALSE, NULL);
  snprintf(buffer, RENAME_STR_SIZE, "%p_", (void*)&symbol);

  name = STRcpy(SYMBOL_NAME( symbol));
  SYMBOL_NAME( symbol) = STRcat(buffer , name);
  PARAM_NAME(arg_node) = SYMBOL_NAME(symbol);

  //check type of root node of the moment, make a new symbol table if there is none
  if( NODE_TYPE(INFO_ROOT_NODE(arg_info)) == N_program){
      if(PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
      else{
      SYMBOL_NEXT(symbol) = PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
  } else if(NODE_TYPE(INFO_ROOT_NODE(arg_info)) == N_fundef) {
     if(FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
      else{
      SYMBOL_NEXT(symbol) = FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }

  } 
  MEMfree(name);  
  
  //keep traversing
  PARAM_NEXT( arg_node) = TRAVopt( PARAM_NEXT( arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

//traverse through funbody
node *SYMfunbody( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMfunbody");
  INFO_ROOT_FUNBODY(arg_info) = arg_node;

  FUNBODY_VARDEC( arg_node)= TRAVopt(FUNBODY_VARDEC(arg_node), arg_info);
  FUNBODY_LOCALFUNDEFS( arg_node)= TRAVopt(FUNBODY_LOCALFUNDEFS(arg_node), arg_info);

  INFO_FUN_VARDEC(arg_info) = FUNBODY_VARDEC(arg_node);
  FUNBODY_STATEMENT( arg_node)= TRAVopt(FUNBODY_STATEMENT(arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

//rename and put in the right symbol table
node *SYMvardec( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMvardec");

  char *name;
  char buffer[RENAME_STR_SIZE];

  node *symbol = TBmakeSymbol(VARDEC_TYPE( arg_node), STRcpy(VARDEC_NAME( arg_node)), INFO_STATE(arg_info), FALSE, FALSE, NULL);
  snprintf(buffer, RENAME_STR_SIZE, "%p_", (void*)&symbol);

  name = STRcpy(SYMBOL_NAME( symbol));
  SYMBOL_NAME( symbol) = STRcat(buffer , name);
  VARDEC_NAME(arg_node) = SYMBOL_NAME(symbol);


  //put symbol in right symbol table, check root node type first. 
   
  if(FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
  FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }
  else{
  SYMBOL_NEXT(symbol) = FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
  FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }

  //keep traversing
  VARDEC_NEXT( arg_node) = TRAVopt( VARDEC_NEXT( arg_node), arg_info);

  MEMfree(name); 
  DBUG_RETURN(arg_node);
}

//traverse over fundefs
node *SYMfundefs( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMfundefs");  

  FUNDEFS_FUNDEF(arg_node) = TRAVdo( FUNDEFS_FUNDEF(arg_node), arg_info);
  FUNDEFS_NEXT(arg_node) = TRAVopt( FUNDEFS_NEXT(arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

//traverse over stmts
node *SYMstmts( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMstmts");  

  STMTS_STMT(arg_node) = TRAVdo( STMTS_STMT(arg_node), arg_info);  
  STMTS_NEXT(arg_node) = TRAVopt( STMTS_NEXT(arg_node), arg_info);
  DBUG_RETURN(arg_node);

}

//put loopvar in symbol table. 
node *SYMfor( node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMfor"); 
  INFO_TOTALFORCOUNT(arg_info) = INFO_TOTALFORCOUNT(arg_info) + 1;
  INFO_FORINFORCOUNT(arg_info)  = INFO_FORINFORCOUNT(arg_info) + 1;
  INFO_FORCOUNT(arg_info)[INFO_FORINFORCOUNT(arg_info)] = INFO_TOTALFORCOUNT(arg_info);
  char *name;
  char buffer[RENAME_STR_SIZE];
  char buffercount[5];
  node *vardec = FOR_STARTVARDEC(arg_node);
  node *symbol = TBmakeSymbol(T_int, VARDEC_NAME(vardec), INFO_STATE(arg_info), FALSE, FALSE, NULL);
  INFO_FORVARNAME(arg_info)[INFO_FORINFORCOUNT(arg_info)] = VARDEC_NAME(vardec);
  snprintf(buffer, RENAME_STR_SIZE, "%p_", (void*)&symbol);
  sprintf(buffercount, "%d", INFO_FORCOUNT(arg_info)[INFO_FORINFORCOUNT(arg_info)]);
  name = STRcpy(SYMBOL_NAME( symbol));
  SYMBOL_NAME( symbol) = STRcatn(3, buffer , name, buffercount);
  printf("for variabele hernoemd: %s", SYMBOL_NAME(symbol));
  VARDEC_NAME(vardec) = SYMBOL_NAME(symbol);

  node *tmpvar = TBmakeVar(SYMBOL_NAME(symbol), NULL);
  FOR_START(arg_node) = tmpvar;
  FOR_STARTVARDEC(arg_node) = NULL;

  node *rootfunbody = INFO_ROOT_FUNBODY(arg_info);

  node *tmp = FUNBODY_VARDEC(rootfunbody) ;
  VARDEC_NEXT(vardec) = tmp;

  FUNBODY_VARDEC(rootfunbody) = vardec;

  FOR_STARTVARDEC(arg_node) = NULL;

  //put symbol in right symbol table, check root node type first.    
  if(FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
  FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }
  else{
  SYMBOL_NEXT(symbol) = FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
  FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }

    FOR_BLOCK(arg_node) = TRAVopt(FOR_BLOCK(arg_node), arg_info);
    FOR_BLOCKSINGLE(arg_node) = TRAVopt(FOR_BLOCKSINGLE(arg_node), arg_info);
  
  
  INFO_FORVARNAME(arg_info) [INFO_FORINFORCOUNT(arg_info)]= "";
  INFO_FORINFORCOUNT(arg_info) = INFO_FORINFORCOUNT(arg_info)-1;
  MEMfree(name);
  DBUG_RETURN(arg_node);
}
node *SYMvar(node *arg_node, info *arg_info){
  DBUG_ENTER("SYMvar");
  if(STReq(VAR_NAME(arg_node), INFO_FORVARNAME(arg_info)[INFO_FORINFORCOUNT(arg_info)])){
    char buffer[5];
    sprintf(buffer, "%d", INFO_FORCOUNT(arg_info)[INFO_FORINFORCOUNT(arg_info)]);
    VAR_NAME(arg_node) = STRcat(VAR_NAME(arg_node), buffer);
    printf("nieuwe var name: %s\n", VAR_NAME(arg_node));
  }
  else if(INFO_FORINFORCOUNT(arg_info) > 1){
    for(int i = INFO_FORINFORCOUNT(arg_info); i >0; i--){
      if(STReq(VAR_NAME(arg_node), INFO_FORVARNAME(arg_info)[i])){
      char buffer[5];
      sprintf(buffer, "%d", INFO_FORCOUNT(arg_info)[i]);
      VAR_NAME(arg_node) = STRcat(VAR_NAME(arg_node), buffer);
      printf("nieuwe var name: %s\n", VAR_NAME(arg_node));
  }
    }
  }
  DBUG_RETURN(arg_node);
}
/*
 * Traversal start function
 */

node *SYMcreatesymboltable( node *syntaxtree)
{

  info *arg_info;

  DBUG_ENTER("SYMcreatesymboltable");

  arg_info = MakeInfo();

  TRAVpush( TR_sym);   // Push traversal "sym" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);
}
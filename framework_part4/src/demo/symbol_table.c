/*****************************************************************************
 *
 * Module: symbol_table
 *
 * Prefix: SYM
 *
 * Description:
 *
 * TODO
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


 struct INFO {
  node *root_node;
  int state;
};

#define INFO_ROOT_NODE(n) ((n)->root_node)
#define INFO_STATE(n) ((n)->state)


static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_ROOT_NODE( result) = NULL;
  INFO_STATE( result) = 0;

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

node *SYMdeclarations( node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMdeclarations");

  DECLARATIONS_DECL( arg_node) = TRAVdo( DECLARATIONS_DECL( arg_node), arg_info);
  DECLARATIONS_NEXT( arg_node) = TRAVopt( DECLARATIONS_NEXT( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}


node *SYMglobaldec( node *arg_node, info * arg_info)
{
  node *symbol = TBmakeSymbol(GLOBALDEC_TYPE( arg_node), GLOBALDEC_NAME( arg_node), INFO_STATE(arg_info), NULL);
  DBUG_ENTER("SYMglobaldec");

  if(PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }
  else{
    SYMBOL_NEXT(symbol) = PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }

  DBUG_RETURN(arg_node);
}


node *SYMglobaldef(node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMglobaldef");

  node *symbol = TBmakeSymbol(GLOBALDEF_TYPE (arg_node), GLOBALDEF_NAME(arg_node), INFO_STATE(arg_info), NULL);

  if(PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }
  else{
    SYMBOL_NEXT(symbol) = PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
    PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
  }

  DBUG_RETURN(arg_node);
}

node *SYMfundef( node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMfundef");


  if(FUNDEF_PARAMS(arg_node)!=NULL || FUNDEF_FUNBODY(arg_node) != NULL){

    // // change state root node
    node *tmp = INFO_ROOT_NODE(arg_info);
    INFO_ROOT_NODE(arg_info) = arg_node;

    // increment state in table
    INFO_STATE(arg_info) = INFO_STATE(arg_info)+1;

    // trav params
    FUNDEF_PARAMS( arg_node) = TRAVopt( FUNDEF_PARAMS( arg_node), arg_info);
    FUNDEF_FUNBODY( arg_node) = TRAVopt( FUNDEF_FUNBODY( arg_node), arg_info);

    INFO_ROOT_NODE(arg_info) = tmp;
    INFO_STATE(arg_info) = INFO_STATE(arg_info)-1;
  }

  

  DBUG_RETURN(arg_node);
}

node *SYMparam( node *arg_node, info * arg_info)
{

  node *symbol = TBmakeSymbol(PARAM_TYPE( arg_node), PARAM_NAME( arg_node), INFO_STATE(arg_info), NULL);
  DBUG_ENTER("SYMparam");

  if( NODE_TYPE(INFO_ROOT_NODE(arg_info)) == 1){
      if(PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
      else{
      SYMBOL_NEXT(symbol) = PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      PROGRAM_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
  } else if(NODE_TYPE(INFO_ROOT_NODE(arg_info)) == 5) {
     if(FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
      else{
      SYMBOL_NEXT(symbol) = FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }

  } 

  PARAM_NEXT( arg_node) = TRAVopt( PARAM_NEXT( arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

node *SYMfunbody( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMfunbody");

  FUNBODY_VARDEC( arg_node)= TRAVopt(FUNBODY_VARDEC(arg_node), arg_info);
  FUNBODY_LOCALFUNDEFS( arg_node)= TRAVopt(FUNBODY_LOCALFUNDEFS(arg_node), arg_info);
  FUNBODY_STATEMENT( arg_node)= TRAVopt(FUNBODY_STATEMENT(arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

node *SYMvardec( node *arg_node, info * arg_info)
{
  node *symbol = TBmakeSymbol(VARDEC_TYPE( arg_node), VARDEC_NAME( arg_node), INFO_STATE(arg_info), NULL);
  DBUG_ENTER("SYMglobaldec");

   if(NODE_TYPE(INFO_ROOT_NODE(arg_info)) == 5) {
     if(FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
      else{
      SYMBOL_NEXT(symbol) = FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      FUNDEF_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }

  } else if(NODE_TYPE(INFO_ROOT_NODE(arg_info))== 16){
     if(FOR_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) == NULL){
      FOR_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
      else{
      SYMBOL_NEXT(symbol) = FOR_SYMBOLTABLE(INFO_ROOT_NODE(arg_info));
      FOR_SYMBOLTABLE(INFO_ROOT_NODE(arg_info)) = symbol;
    }
  }


  VARDEC_NEXT( arg_node) = TRAVopt( VARDEC_NEXT( arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

node *SYMfundefs( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMfundefs");  

  FUNDEFS_FUNDEF(arg_node) = TRAVdo( FUNDEFS_FUNDEF(arg_node), arg_info);
  FUNDEFS_NEXT(arg_node) = TRAVopt( FUNDEFS_NEXT(arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

node *SYMstmts( node *arg_node, info * arg_info)
{
  DBUG_ENTER("SYMstmts");  

  STMTS_STMT(arg_node) = TRAVdo( STMTS_STMT(arg_node), arg_info);  
  STMTS_NEXT(arg_node) = TRAVopt( STMTS_NEXT(arg_node), arg_info);
  DBUG_RETURN(arg_node);

}

node *SYMfor( node *arg_node, info *arg_info)
{
  DBUG_ENTER("SYMfor");  

  node *symbol = TBmakeSymbol(T_int, FOR_LOOPVAR( arg_node), INFO_STATE(arg_info), NULL);
  node *tmp = INFO_ROOT_NODE(arg_info);

  FOR_SYMBOLTABLE(arg_node) = symbol;
  INFO_ROOT_NODE(arg_info) = arg_node;

  INFO_STATE(arg_info) = INFO_STATE(arg_info)+1;

  FOR_BLOCK(arg_node) = TRAVdo(FOR_BLOCK(arg_node), arg_info);


  INFO_ROOT_NODE(arg_info) = tmp;
  INFO_STATE(arg_info) = INFO_STATE(arg_info)-1;

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

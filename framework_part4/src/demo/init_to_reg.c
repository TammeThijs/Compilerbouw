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


#include "init_to_reg.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "str.h"
#include "memory.h"
#include "ctinfo.h"

 struct INFO {
  node *rootNode;
  node *stmtStack [20];  
  int count;
};

#define INFO_ROOTNODE(n) ((n)->rootNode)
#define INFO_QUEUE(n) ((n)->stmtStack)
#define INFO_COUNTER(n) ((n)->count)

info *enqueue(info * arg_info, node *stmt){
  INFO_COUNTER(arg_info) = INFO_COUNTER(arg_info)+1;
  INFO_QUEUE(arg_info)[INFO_COUNTER(arg_info)-1] = stmt;
  return arg_info;
}

node *dequeue(info * arg_info){
  node *returnNode = INFO_QUEUE(arg_info)[INFO_COUNTER(arg_info)-1];  
  INFO_COUNTER(arg_info) = INFO_COUNTER(arg_info)-1;
  return returnNode;
}

static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_ROOTNODE( result) = NULL;
  INFO_COUNTER( result) = 0;


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

node *INITdeclarations (node *arg_node, info *arg_info){
  DBUG_ENTER("INITdeclarations");

  node *stmts;
  node *initbody;
  node *fundef;
  node *declarations;
  node *assign;

  int counter = 0;


  if(DECLARATIONS_DECL(arg_node) != NULL && INFO_ROOTNODE(arg_info) == NULL &&
   NODE_TYPE(DECLARATIONS_DECL(arg_node)) == 7){
    initbody = TBmakeFunbody(NULL, NULL, NULL);
    fundef = TBmakeFundef(T_unknown, "__init", NULL, initbody, NULL, NULL);
    declarations = TBmakeDeclarations(fundef, NULL);
    INFO_ROOTNODE(arg_info) = initbody;
  }

  // node *tmp = arg_node;
  // while(DECLARATIONS_NEXT(tmp) != NULL){
  //   tmp = DECLARATIONS_NEXT(tmp);
  //   counter++;
  // }

  DECLARATIONS_DECL( arg_node) = TRAVopt( DECLARATIONS_DECL( arg_node), arg_info);
  DECLARATIONS_NEXT( arg_node) = TRAVopt( DECLARATIONS_NEXT( arg_node), arg_info);

  if(INFO_COUNTER(arg_info) > 0){
  assign = dequeue(arg_info);  
  stmts = TBmakeStmts(assign, NULL);
  printf("type %d\n", NODE_TYPE(assign));
  // FUNBODY_STATEMENT(INFO_ROOTNODE(arg_info)) = stmts;
  }


  
  

  DBUG_RETURN(arg_node);
 }


 node *INITglobaldef (node *arg_node, info *arg_info){
  DBUG_ENTER("INITglobaldef");

  if(GLOBALDEF_INIT(arg_node) != NULL){
      node *varlet = TBmakeVarlet(GLOBALDEF_NAME(arg_node), NULL);
      node *assign = TBmakeAssign(varlet, GLOBALDEF_INIT(arg_node));
      arg_info = enqueue(arg_info, assign);
  }

  node *returnNode = TBmakeGlobaldef(GLOBALDEF_TYPE(arg_node), GLOBALDEF_NAME(arg_node), GLOBALDEF_DIMS(arg_node), NULL);


  DBUG_RETURN(returnNode);
 }

 node *INITfunbody (node *arg_node, info *arg_info){
  DBUG_ENTER("INITfunbody");

  INFO_ROOTNODE(arg_info) = arg_node;

  FUNBODY_VARDEC( arg_node)= TRAVopt(FUNBODY_VARDEC(arg_node), arg_info);
  FUNBODY_STATEMENT( arg_node)= TRAVopt(FUNBODY_STATEMENT(arg_node), arg_info);
  FUNBODY_LOCALFUNDEFS( arg_node)= TRAVopt(FUNBODY_LOCALFUNDEFS(arg_node), arg_info);


  DBUG_RETURN(arg_node);
 }

  node *INITvardec (node *arg_node, info *arg_info){
      DBUG_ENTER("INITvardec");

    if(VARDEC_INIT(arg_node) != NULL){

      node *stmts;
      node *vardec = TBmakeVardec(VARDEC_TYPE(arg_node), VARDEC_NAME(arg_node), NULL, NULL, VARDEC_NEXT(arg_node));
      node *varlet = TBmakeVarlet(VARDEC_NAME(arg_node), NULL);
      node *assign = TBmakeAssign(varlet, VARDEC_INIT(arg_node));

       if(FUNBODY_STATEMENT(INFO_ROOTNODE(arg_info)) == NULL){
        stmts = TBmakeStmts(assign, NULL);
        FUNBODY_STATEMENT(INFO_ROOTNODE(arg_info)) = stmts;
      }
       else{
         stmts = TBmakeStmts(assign, FUNBODY_STATEMENT(INFO_ROOTNODE(arg_info)));
         FUNBODY_STATEMENT(INFO_ROOTNODE(arg_info)) = stmts; 
      }

      VARDEC_NEXT( vardec) = TRAVopt( VARDEC_NEXT( vardec), arg_info);
      DBUG_RETURN(vardec);
    }

    VARDEC_NEXT( arg_node) = TRAVopt( VARDEC_NEXT( arg_node), arg_info);
    DBUG_RETURN(arg_node);

  }

  node *INITstmts (node *arg_node, info *arg_info){
  DBUG_ENTER("INITstmts");
  DBUG_RETURN(arg_node);
 }

/*
 * Traversal start function
 */

node *INITdoInitToReg( node *syntaxtree)
{

  info *arg_info;

  DBUG_ENTER("INITinitiasationstoregular");

  arg_info = MakeInfo();

  TRAVpush( TR_init);   

  syntaxtree = TRAVdo( syntaxtree, arg_info);  

  TRAVpop(); 

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);
}

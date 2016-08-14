/*****************************************************************************
 *
 * Module: init_to_reg
 *
 * Prefix: INIT
 *
 * Description: Turning Variable Initialisations into Regular Assignments.
 *
 * Tamme
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
  node *funBody;
  node *stmtStack [20];
  node *forassigns [20];
  int firstTime;
  int count;
  int amountFor;
};

#define INFO_ROOTNODE(n) ((n)->rootNode)
#define INFO_FUNBODY(n) ((n)->funBody)
#define INFO_QUEUE(n) ((n)->stmtStack)
#define INFO_COUNTER(n) ((n)->count)
#define INFO_FIRSTTIME(n) ((n)->firstTime)
#define INFO_FORASSIGNS(n) ((n)->forassigns)
#define INFO_AMOUNTFOR(n) ((n)->amountFor)


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
  INFO_FUNBODY( result) = NULL;
  INFO_COUNTER( result) = 0;
  INFO_FIRSTTIME( result) = 0;
  INFO_AMOUNTFOR( result) = 0;


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

  if(INFO_FIRSTTIME(arg_info) == 0 && DECLARATIONS_DECL(arg_node) != NULL){

    initbody = TBmakeFunbody(NULL, NULL, NULL);
    fundef = TBmakeFundef(T_unknown, STRcpy("__init"), TRUE, FALSE, NULL, initbody, NULL, NULL);
    declarations = TBmakeDeclarations(fundef, arg_node);

    INFO_FUNBODY(arg_info) = initbody;
    INFO_FIRSTTIME(arg_info) = 1;

    arg_node = declarations;
  }

  DECLARATIONS_DECL( arg_node) = TRAVopt( DECLARATIONS_DECL( arg_node), arg_info);
  DECLARATIONS_NEXT( arg_node) = TRAVopt( DECLARATIONS_NEXT( arg_node), arg_info);

  if(INFO_COUNTER(arg_info) > 0 && DECLARATIONS_NEXT(arg_node) == NULL){

    node *ret = TBmakeReturn(NULL);
    node *lastStmt = TBmakeStmts(ret, NULL);
    FUNBODY_STATEMENT(INFO_FUNBODY(arg_info)) = lastStmt;

    while(INFO_COUNTER(arg_info) >0){
          node *assign = dequeue(arg_info);  
          stmts = TBmakeStmts(assign, lastStmt);
          FUNBODY_STATEMENT(INFO_FUNBODY(arg_info)) = stmts;
          lastStmt = stmts;
    }
  } 
   

  DBUG_RETURN(arg_node);
 }


 node *INITglobaldef (node *arg_node, info *arg_info){
  DBUG_ENTER("INITglobaldef");

  if(GLOBALDEF_INIT(arg_node) != NULL){
      node *varlet = TBmakeVarlet(STRcpy(GLOBALDEF_NAME(arg_node)), NULL);
      node *assign = TBmakeAssign(varlet, GLOBALDEF_INIT(arg_node));
      arg_info = enqueue(arg_info, assign);
  }

  node *returnNode = TBmakeGlobaldef(GLOBALDEF_TYPE(arg_node), GLOBALDEF_NAME(arg_node), GLOBALDEF_EXPORT(arg_node), GLOBALDEF_DIMS(arg_node), NULL);


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
      ASSIGN_VARDECNAME(assign) = STRcpy(VARDEC_NAME(arg_node));

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
node *INITfor (node *arg_node, info *arg_info){
  DBUG_ENTER("INITfor");
 /* node *vardec = TBmakeVardec(T_int, STRcpy(FOR_LOOPVAR(arg_node)), NULL, NULL, NULL);
  node *varlet = TBmakeVarlet(FOR_LOOPVAR(arg_node), NULL);
  node *assign = TBmakeAssign(varlet, FOR_START(arg_node));
  node *var = TBmakeVar(FOR_LOOPVAR(arg_node), NULL);
  FOR_START(arg_node) = var;
  vardec = TBmakeVardec(T_int, FOR_LOOPVAR(arg_node), NULL, NULL, FUNBODY_VARDEC(INFO_ROOTNODE(arg_info)));
  FUNBODY_VARDEC(INFO_ROOTNODE(arg_info)) = vardec;
  INFO_FORASSIGNS(arg_info)[INFO_AMOUNTFOR(arg_info)] = assign;
  INFO_AMOUNTFOR(arg_info) = INFO_AMOUNTFOR(arg_info) + 1;*/
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

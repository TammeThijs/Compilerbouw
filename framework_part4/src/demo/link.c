
/*****************************************************************************
 *
 * Module: link
 *
 * Prefix: LINK
 *
 * Description: makes links between variables and corresponding symbols and 
 * function calls with the corresponding functions
 * 
 *
 *****************************************************************************/


#include "link.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"
#include "stdbool.h"
#include "str.h"
#include "memory.h"
#include "ctinfo.h"


 struct INFO {
  node * symboltableStack [20];
  int top;
  int size;
};

#define INFO_STACK(n) ((n)->symboltableStack)
#define INFO_TOP(n) ((n)->top)
#define INFO_SIZE(n) ((n)->size)

info *push(info *arg_info, node *symbol){
  INFO_TOP(arg_info) = INFO_TOP(arg_info) + 1;
  INFO_STACK(arg_info)[INFO_TOP(arg_info)] = symbol;
  return arg_info;
}

info *pop(info *arg_info){
  INFO_STACK(arg_info)[INFO_TOP(arg_info)] = NULL;
  INFO_TOP(arg_info) = INFO_TOP(arg_info) -1;
  return arg_info;
}

static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_TOP( result)= 0;
  INFO_SIZE(result) = 20;
  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}
node *LINKprogram( node *arg_node, info *arg_info){
  DBUG_ENTER("LINKprogram");
  arg_info = push(arg_info, PROGRAM_SYMBOLTABLE(arg_node));
  DBUG_RETURN(arg_node);
}

node *LINKfundef( node *arg_node, info *arg_info){
  DBUG_ENTER("LINKfundef");
  arg_info = push(arg_info, FUNDEF_SYMBOLTABLE(arg_node));
  FUNDEF_FUNBODY(arg_node) =TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
  arg_info = pop(arg_info);
  DBUG_RETURN(arg_node);
}
node *LINKvar(node *arg_node, info *arg_info){
  DBUG_ENTER("LINKvar");
  int scope = INFO_TOP(arg_info);
  node *symbol = INFO_STACK(arg_info)[scope];
  bool found = false;
  
  while(!found && scope >= 0){
    while(SYMBOL_NEXT(symbol)!= NULL && !found){
      if(STReq(SYMBOL_NAME(symbol), VAR_NAME(arg_node))){
        VAR_DECL(arg_node) = symbol;
        found = true;
      }
      else{
        symbol = SYMBOL_NEXT(symbol);
      }
    }
    if(!found){
      symbol = NULL;
      while(symbol == NULL && scope>=0){}
        scope--;
        symbol = INFO_STACK(arg_info)[scope];
      }
    }
  

  if(!found){
    printf("Variable has not been declared!");
  }
  DBUG_RETURN(arg_node);
}

node *LINKvarlet(node *arg_node, info *arg_info){
  DBUG_ENTER("LINKvarlet");
  int scope = INFO_TOP(arg_info);
  node *symbol = INFO_STACK(arg_info)[scope];
  bool found = false;
  
  while(!found && scope >= 0){
    while(SYMBOL_NEXT(symbol)!= NULL && !found){
      if(STReq(SYMBOL_NAME(symbol), VAR_NAME(arg_node))){
        VAR_DECL(arg_node) = symbol;
        found = true;
      }
      else{
        symbol = SYMBOL_NEXT(symbol);
      }
    }
    if(!found){
      symbol = NULL;
      while(symbol == NULL && scope>=0){}
        scope--;
        symbol = INFO_STACK(arg_info)[scope];
      }
    }
  

  if(!found){
    printf("Variable has not been declared!");
  }
  DBUG_RETURN(arg_node);
}

node *LINKfuncall(node *arg_node, info *arg_info){
  DBUG_ENTER("Linkfuncall");
  DBUG_RETURN(arg_node);
}

node *LINKcreatelinks( node *syntaxtree)
{

  info *arg_info;

  DBUG_ENTER("LINKcreatelinks");

  arg_info = MakeInfo();

  TRAVpush( TR_link);   // Push traversal "link" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);
}
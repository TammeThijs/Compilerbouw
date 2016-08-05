
/*****************************************************************************
 *
 * Module: link
 *
 * Prefix: LINK
 *
 * Description: makes links between variables and corresponding symbols and 
 * function calls with the corresponding functions
 * 
 *  @author Carly Hill 10523162
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
  node *symboltableStack [20];
  node *functionList[20];
  int top;
  int size;
  int scope;
  int counter;
};

#define INFO_STACK(n) ((n)->symboltableStack)
#define INFO_LIST(n) ((n)->functionList)
#define INFO_TOP(n) ((n)->top)
#define INFO_SIZE(n) ((n)->size)
#define INFO_SCOPE(n) ((n)->scope)
#define INFO_COUNTER(n) ((n)->counter)

info *push(info *arg_info, node *symbol){
  INFO_TOP(arg_info) = INFO_TOP(arg_info) + 1;
  INFO_STACK(arg_info)[INFO_TOP(arg_info)] = symbol;
  return arg_info;
}

info *add(info * arg_info, node *fsymbol){
  INFO_COUNTER(arg_info) = INFO_COUNTER(arg_info)+1;
  INFO_LIST(arg_info)[INFO_COUNTER(arg_info)] = fsymbol;
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

  INFO_TOP( result)= 1;
  INFO_SIZE(result) = 20;
  INFO_SCOPE( result) = 0;
  INFO_COUNTER( result) = 0;
  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}

//push symbol table on stack and add fsymboltable to list
node *LINKprogram( node *arg_node, info *arg_info){
  DBUG_ENTER("LINKprogram");
  if(PROGRAM_SYMBOLTABLE(arg_node)!=NULL){
    arg_info = push(arg_info, PROGRAM_SYMBOLTABLE(arg_node));
  }
  if(PROGRAM_FSYMBOLTABLE(arg_node)!=NULL){
    arg_info = add(arg_info, PROGRAM_FSYMBOLTABLE(arg_node));
  }
  PROGRAM_DECLARATIONS(arg_node) =  TRAVdo(PROGRAM_DECLARATIONS( arg_node), arg_info); 
  DBUG_RETURN(arg_node);
}

//push symboltable on stack, add fsymboltable to list and traverser
node *LINKfundef( node *arg_node, info *arg_info){
  DBUG_ENTER("LINKfundef");

  if(FUNDEF_SYMBOLTABLE(arg_node)!=NULL){
    INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) + 1;
    arg_info = push(arg_info, FUNDEF_SYMBOLTABLE(arg_node));
  }
  if(FUNDEF_FSYMBOLTABLE(arg_node)!=NULL){
    arg_info = add(arg_info, FUNDEF_FSYMBOLTABLE(arg_node));
  }

  FUNDEF_FUNBODY(arg_node) =TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);

  if(FUNDEF_SYMBOLTABLE(arg_node) != NULL){
    INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) - 1;
    arg_info = pop(arg_info); 
  }
  

  DBUG_RETURN(arg_node);
}

//search var in symbol tables and fill link or give error
node *LINKvar(node *arg_node, info *arg_info){
  DBUG_ENTER("LINKvar");

  int scope = INFO_TOP(arg_info);
  int scopeVar = INFO_SCOPE(arg_info);
  node *symbol = INFO_STACK(arg_info)[scope];
  bool found = false;
  
  //while not found and still a symbol table to be searched
  while(!found && scope >= 0){
    while(symbol == NULL && scope>0){
      scope--;
      symbol = INFO_STACK(arg_info)[scope];
    }
    if(symbol == NULL){
      break;
    }
    else{
      char *symbolName = SYMBOL_NAME(symbol);
      char *varName = VAR_NAME(arg_node);
      if(STRsuffix(varName, symbolName)){
        VAR_DECL(arg_node) = symbol;
        VAR_NAME(arg_node) = SYMBOL_NAME(symbol);
        found = true;
        SYMBOL_STATE(symbol) = -1;
        SYMBOL_SCOPE(symbol) = scopeVar;
      }
      else{
          symbol = SYMBOL_NEXT(symbol);
      }
    }
  }
  
  //if the symbol is not found: give an error
  if(!found){
    CTIerrorLine(NODE_LINE(arg_node), "Var has not been declared");
  }

  DBUG_RETURN(arg_node);
}

node *LINKassign( node *arg_node, info *arg_info){
  DBUG_ENTER("LINKassign");

  ASSIGN_LET(arg_node) =  TRAVdo(ASSIGN_LET( arg_node), arg_info);
  ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info); 
  DBUG_RETURN(arg_node);
}

//search varlet in symbol tables and fill link (decl)
node *LINKvarlet(node *arg_node, info *arg_info){
  DBUG_ENTER("LINKvarlet");

  int scope = INFO_TOP(arg_info);
  int scopeVar = INFO_SCOPE(arg_info);
  node *symbol = INFO_STACK(arg_info)[scope];


  bool found = false;
  
  //search through stack
  while(!found && scope >= 0){

    while(symbol == NULL && scope>0){
      scope--;
      symbol = INFO_STACK(arg_info)[scope];
    }
    if(symbol == NULL){
      break;
    }
    else{
      char *symbolName = SYMBOL_NAME(symbol);
      char *varletName = VARLET_NAME(arg_node);
      if(STRsuffix(varletName, symbolName)){
        VARLET_DECL(arg_node) = symbol; 
        VARLET_NAME(arg_node) = SYMBOL_NAME(symbol); 
        found = true;
        SYMBOL_SCOPE(symbol) = scopeVar;
        SYMBOL_STATE(symbol) = -1;     
      }
      else{
          symbol = SYMBOL_NEXT(symbol);
      }
    }
  }
  
  //giver error if not found
  if(!found){
    CTIerrorLine(NODE_LINE(arg_node), "Varlet has not been declared");
  }

  DBUG_RETURN(arg_node);
}

//search funcall in the list and fill decl
node *LINKfuncall(node *arg_node, info *arg_info){
  DBUG_ENTER("Linkfuncall");

  int i = INFO_COUNTER(arg_info);
  node *fsymbol = INFO_LIST(arg_info)[i];
  bool found = false;
  
  while(!found && i > 0){
    while(fsymbol == NULL && i>0){
      i--;
      fsymbol = INFO_LIST(arg_info)[i];
    }
    if(fsymbol == NULL){
      break;
    }
    else{
      char *symbolName = FSYMBOL_NAME(fsymbol);
      char *funName = FUNCALL_NAME(arg_node);
      if(STReq(funName, symbolName)){
        FUNCALL_DECL(arg_node) = fsymbol;
        found = true;
      }
      else{
          fsymbol = FSYMBOL_NEXT(fsymbol);
      }
    }
  }
  
  //give error if not found
  if(!found){
    CTIerrorLine(NODE_LINE(arg_node), "function has not been declared");
  }
  //check if the amount of parameters matches the amount of given arguments
  else{
    int paramcount = 0;
    int argumentcount = 0;
    node * param = FUNDEF_PARAMS(FSYMBOL_FUNCTION(fsymbol));
    node *args = FUNCALL_ARGS(arg_node);
    if(param!=NULL){
      paramcount++;
      while(PARAM_NEXT(param)!=NULL){
        paramcount++;
        param = PARAM_NEXT(param);
      }
    }
    if(args!=NULL){
      argumentcount++;
      while(EXPRS_NEXT(args)!=NULL){
        argumentcount++;
        args = EXPRS_NEXT(args);
      }
    }
    if(paramcount != argumentcount){
      CTIerrorLine(NODE_LINE(arg_node), "Number of given arguments does not match the number of parameters.");
    }
  }
  FUNCALL_ARGS(arg_node) = TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
  DBUG_RETURN(arg_node);
}

//start function
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
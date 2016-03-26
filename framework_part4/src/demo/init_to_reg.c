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
  node *lastVardec;
};

#define INFO_INIT_VARDEC(n) ((n)->lastVardec)


static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_INIT_VARDEC( result) = NULL;

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

 node *INITglobaldec (node *arg_node, info *arg_info){
  DBUG_ENTER("INITglobaldec");

  node *vardec;

  if(INFO_INIT_VARDEC(arg_info) == NULL){

    vardec = TBmakeVardec(GLOBALDEC_TYPE(arg_node), GLOBALDEC_NAME(arg_node), NULL, NULL, NULL);
    node *initbody = TBmakeFunbody(vardec, NULL, NULL);
    TBmakeFundef(T_unknown, "__init", NULL, initbody, NULL, NULL);
    INFO_INIT_VARDEC(arg_info) = vardec;

  } else {
    vardec = TBmakeVardec(GLOBALDEC_TYPE(arg_node), GLOBALDEC_NAME(arg_node), NULL, NULL, INFO_INIT_VARDEC(arg_info));
    INFO_INIT_VARDEC(arg_info) = vardec;  
  }

  DBUG_RETURN(arg_node);
 }

 node *INITglobaldef (node *arg_node, info *arg_info){
  DBUG_ENTER("INITglobaldef");

  node *vardec;

  if(INFO_INIT_VARDEC(arg_info) == NULL){

    vardec = TBmakeVardec(GLOBALDEF_TYPE(arg_node), GLOBALDEF_NAME(arg_node), NULL, NULL, NULL);
    node *initbody = TBmakeFunbody(vardec, NULL, NULL);
    TBmakeFundef(T_unknown, "__init", NULL, initbody, NULL, NULL);
    INFO_INIT_VARDEC(arg_info) = vardec;

  } else {
    vardec = TBmakeVardec(GLOBALDEF_TYPE(arg_node), GLOBALDEF_NAME(arg_node), NULL, NULL, INFO_INIT_VARDEC(arg_info));
    INFO_INIT_VARDEC(arg_info) = vardec;  
  }

  node *varlet = TBmakeVarlet(GLOBALDEF_NAME(arg_node), NULL);
  node *returnnode = TBmakeAssign(varlet, GLOBALDEF_INIT(arg_node));

  DBUG_RETURN(returnnode);
 }

  node *INITfunbody (node *arg_node, info *arg_info){
      DBUG_ENTER("INITglobaldef");

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

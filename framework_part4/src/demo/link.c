
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
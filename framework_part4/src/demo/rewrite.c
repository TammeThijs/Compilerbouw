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

};

static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}

node *RWbinop(node *arg_node, info *arg_info){
	DBUG_ENTER("RWbinop");
	DBUG_RETURN(arg_node);
}

node *RWcast(node *arg_node, info *arg_info){
	DBUG_ENTER("RWcast");
	DBUG_RETURN(arg_node);
}
node *RWrewritecode( node *syntaxtree)
{

  info *arg_info;

  DBUG_ENTER("RWrewritecode");
  printf("Code &&, || en cast omschrijven\n");

  arg_info = MakeInfo();

  TRAVpush( TR_rw);   // Push traversal "link" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);
}
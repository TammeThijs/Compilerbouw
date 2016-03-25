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

//rewrite and and or to a conditionexpression and return the conditionexpression
node *RWbinop(node *arg_node, info *arg_info){
	DBUG_ENTER("RWbinop");
  printf("in de binop node\n");
  node *leftexpr = BINOP_LEFT(arg_node);
  node *rightexpr = BINOP_RIGHT(arg_node);
  //rewrite and
  if(BINOP_OP(arg_node)==BO_and){
  
    node *pred = TBmakeMonop(MO_not, leftexpr);
    node *then = TBmakeBool(0);
    node *otherthen = TBmakeBool(1);
    node *otherother = TBmakeBool(0);
    node *other = TBmakeConditionexpr(rightexpr, otherthen, otherother);
    arg_node = TBmakeConditionexpr(pred, then, other);
  }

  //rewrite or
  else if(BINOP_OP(arg_node) == BO_or){
    node *orthen = TBmakeBool(1);
    node *orotherthen = TBmakeBool(1);
    node *orotherother = TBmakeBool(0);
    node *orother = TBmakeConditionexpr(rightexpr, orotherthen, orotherother);
    arg_node = TBmakeConditionexpr(leftexpr, orthen, orother);
  }

	DBUG_RETURN(arg_node);
}

//rewrite cast
node *RWcast(node *arg_node, info *arg_info){
	DBUG_ENTER("RWcast");
	DBUG_RETURN(arg_node);
}

//begin traversal
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
/*****************************************************************************
 *
 * Module: count_operators
 *
 * Prefix: COP
 *
 * Description:
 *
 * This module implements a demo traversal of the abstract syntax tree that 
 * counts the number of occurrences of the addition and the subtraction 
 * operator and prints the result at the end of the traversal.
 *
 *****************************************************************************/


#include "count_operators.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "ctinfo.h"


/*
 * INFO structure
 */

struct INFO {
  int add;
  int sub;
  int mul;
  int div; 
  int mod;
};


/*
 * INFO macros
 */

#define INFO_ADD(n)  ((n)->add)
#define INFO_SUB(n)  ((n)->sub)
#define INFO_MUL(n)  ((n)->mul)
#define INFO_DIV(n)  ((n)->div)
#define INFO_MOD(n)  ((n)->mod)


/*
 * INFO functions
 */

static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_ADD( result) = 0;
  INFO_SUB( result) = 0;
  INFO_MUL( result) = 0;
  INFO_DIV( result) = 0;
  INFO_MOD( result) = 0;

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

node *COPbinop (node *arg_node, info *arg_info)
{
  DBUG_ENTER("COPbinop");

  switch (BINOP_OP( arg_node)) {
  case BO_add:
    INFO_ADD( arg_info) = INFO_ADD( arg_info) + 1;
    break;
  case BO_sub:
    INFO_SUB( arg_info) = INFO_SUB( arg_info) + 1;
    break;
    case BO_mul:
    INFO_MUL( arg_info) = INFO_MUL( arg_info) + 1;
    break;
    case BO_div:
    INFO_DIV( arg_info) = INFO_DIV( arg_info) + 1;
    break;
    case BO_mod:
    INFO_MOD( arg_info) = INFO_MOD( arg_info) + 1;
    break;
  default:
    break;
  }

  /*
   * Extremely important:
   *  we must continue to traverse the abstract syntax tree !!
   */
  BINOP_LEFT( arg_node) = TRAVdo( BINOP_LEFT( arg_node), arg_info);
  BINOP_RIGHT( arg_node) = TRAVdo( BINOP_RIGHT( arg_node), arg_info);

  DBUG_RETURN( arg_node);
}


/*
 * Traversal start function
 */

node *COPdoCountOperators( node *syntaxtree)
{
  info *arg_info;

  DBUG_ENTER("COPdoCountOperators");

  arg_info = MakeInfo();

  TRAVpush( TR_cop);
  syntaxtree = TRAVdo( syntaxtree, arg_info);
  TRAVpop();

 
  arg_info = FreeInfo( arg_info);

  DBUG_RETURN( syntaxtree);
}


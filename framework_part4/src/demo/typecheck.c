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
  type typeStack[20];
  int counter;
};

#define INFO_STACK(n) ((n)->typeStack)
#define INFO_COUNTER(n) ((n)->counter)

static info *MakeInfo(void)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  result = (info *)MEMmalloc(sizeof(info));
  INFO_COUNTER(result) = 0;

  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}
node *CTprogram(node *arg_node, info *arg_info){
	DBUG_ENTER("CTprogram");
	PROGRAM_DECLARATIONS(arg_node) =  TRAVdo(PROGRAM_DECLARATIONS( arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *CTfuncall(node *arg_node, info *arg_info){
	DBUG_ENTER("CTfuncall");

	DBUG_RETURN(arg_node);
}

node *CTvarlet(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvarlet");
	DBUG_RETURN(arg_node);
}

node *CTvardec(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvardec");
	if(VARDEC_INIT(arg_node)!= NULL){
		printf("In de init van de vardec\n");
		VARDEC_INIT(arg_node) = TRAVdo(VARDEC_INIT(arg_node), arg_info);
		type vartype = INFO_STACK(arg_info)[INFO_COUNTER(arg_info)];
		if(vartype == T_int){
			printf("vartype is int");
		}
	}
	DBUG_RETURN(arg_node);
}

node *CTvar(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvar");

	DBUG_RETURN(arg_node);
}

node *CTnum(node *arg_node, info *arg_info){
	DBUG_ENTER("CTNum");
	INFO_STACK(arg_info)[INFO_COUNTER(arg_info)] = T_int;
	INFO_COUNTER(arg_info) = INFO_COUNTER(arg_info) + 1;
	printf("Int op de stack\n");
	DBUG_RETURN(arg_node);
}

node *CTbool(node *arg_node, info *arg_info){
	DBUG_ENTER("CTBool");
	INFO_STACK(arg_info)[INFO_COUNTER(arg_info)] = T_boolean;
	INFO_COUNTER(arg_info) = INFO_COUNTER(arg_info) + 1;
	printf("boolean op de stack");
	DBUG_RETURN(arg_node);
}

node *CTfloat(node *arg_node, info *arg_info){
	DBUG_ENTER("CTFloat");
	INFO_STACK(arg_info)[INFO_COUNTER(arg_info)] = T_float;
	INFO_COUNTER(arg_info) = INFO_COUNTER(arg_info) + 1;
	printf("float op de stack");
	DBUG_RETURN(arg_node);
}

node *CTchecktypes( node *syntaxtree)
{


  DBUG_ENTER("CTchecktypes");
  printf("Types checken\n");
  info *arg_info;

  TRAVpush( TR_ct);   // Push traversal "link" as defined in ast.xml
  arg_info = MakeInfo();
  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal
  arg_info = FreeInfo(arg_info);
  DBUG_RETURN( syntaxtree);
}
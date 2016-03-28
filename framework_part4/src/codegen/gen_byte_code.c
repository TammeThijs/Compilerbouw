/*****************************************************************************
 *
 * Module: generate byte code
 *
 * Prefix: GBC
 *
 * Description: prints asssembly code corresponding to the intermediate representation to output file
 * 
 *  @author Carly Hill 10523162
 *****************************************************************************/

#include "gen_byte_code.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"
#include "memory.h"
#include "stdio.h"
#include "str.h"

struct INFO {
	FILE *code;
	int subroutine;
	int varcount;
	int constantcount;
	int constints [50];
};

#define INFO_CODE(n) ((n)->code)
#define INFO_SUBROUTINE(n) ((n)->subroutine)
#define INFO_VARCOUNT(n) ((n)->varcount)
#define INFO_CONSTCOUNT(n) ((n)->constantcount)
#define INFO_CONSTINTS(n) ((n)->constints)

static info *MakeInfo(void)
{
	info *result;

	DBUG_ENTER( "MakeInfo");

	result = (info *)MEMmalloc(sizeof(info));
	INFO_CODE(result) = fopen("program.out", "w+");
	INFO_SUBROUTINE(result) = 2;
	INFO_VARCOUNT(result) = 0;
	INFO_CONSTCOUNT(result) = 0;
	DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");
  fclose(INFO_CODE(info));
  info = MEMfree( info);

  DBUG_RETURN( info);
}

//check if function name = main, if so then traverser
node *GBCfundef(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfundef");
	char *main_name = "main";
	if(STReq(FUNDEF_NAME(arg_node), main_name)){
		fputs("main:\n", INFO_CODE(arg_info));
		fputs("esr 2\n", INFO_CODE(arg_info));
		FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
	}
	DBUG_RETURN(arg_node);
}

node *GBCvardec( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvardec");
	DBUG_RETURN(arg_node);
}

node *GBCassign( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCassign");
	ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
	ASSIGN_LET(arg_node) = TRAVdo(ASSIGN_LET(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCbinop( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCbinop");

	DBUG_RETURN(arg_node);
}

node *GBCvar( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvar");

	DBUG_RETURN(arg_node);
}

node *GBCvarlet( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvarlet");
	/*if(SYMBOL_STATE(VARLET_DECL(arg_node)) == -1){
		SYMBOL_STATE(VARLET_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
		INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
	}*/
	int place = SYMBOL_STATE(VARLET_DECL(arg_node));
	
	char buffer[1];
	sprintf(buffer, "%d", 0);
	char *command = STRcatn(3, "istore ", buffer, "\n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}
node *GBCnum( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCnum");
	if(NUM_VALUE(arg_node) == 0){
		fputs("iloadc_0\n", INFO_CODE(arg_info));
	}
	else if (NUM_VALUE(arg_node) == 1){
		fputs("iloadc_1\n", INFO_CODE(arg_info));
	}
	else if (NUM_VALUE(arg_node) == -1){
		fputs("iload_m1\n", INFO_CODE(arg_info));
	}
	else {
		if(INFO_CONSTCOUNT(arg_info) == 0){
			fputs("iload_0\n", INFO_CODE(arg_info));
		}
		else{
			char buffer[1];
			sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));
			char *command  = STRcatn(3,"iload ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
	}
	DBUG_RETURN(arg_node);
}
/*
 * Traversal start function
 */

node *GBCdoGenByteCode( node *syntaxtree)
{
  

  info *arg_info;
  DBUG_ENTER("GBCdoGenByteCode");
  arg_info = MakeInfo();

  TRAVpush( TR_gbc);   // Push traversal "cbg" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);

}

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
	node *consts [50];
};

#define INFO_CODE(n) ((n)->code)
#define INFO_SUBROUTINE(n) ((n)->subroutine)
#define INFO_VARCOUNT(n) ((n)->varcount)
#define INFO_CONSTCOUNT(n) ((n)->constantcount)
#define INFO_CONSTS(n) ((n)->consts)

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

	//check if it is main
	if(STReq(FUNDEF_NAME(arg_node), main_name)){
		fputs("main:\n", INFO_CODE(arg_info));
		fputs("esr 2\n", INFO_CODE(arg_info));
		FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
		fputs("\n", INFO_CODE(arg_info));

		//write constants
		for(int i = 0; i<INFO_CONSTCOUNT(arg_info); i++){
			if(NODE_TYPE(INFO_CONSTS(arg_info)[i]) == 30){
				char buffer[20];
				sprintf(buffer, "%d", NUM_VALUE(INFO_CONSTS(arg_info)[i]));
				char *command = STRcatn(3, ".const int  ", buffer, "\n");
				fputs(command, INFO_CODE(arg_info));
			}
			else if(NODE_TYPE(INFO_CONSTS(arg_info)[i]) == 31){
				char buffer[20];
				sprintf(buffer, "%f", FLOAT_VALUE(INFO_CONSTS(arg_info)[i]));
				char *command = STRcatn(3, ".const float  ", buffer, "\n");
				fputs(command, INFO_CODE(arg_info));
			}
		}
	}
	DBUG_RETURN(arg_node);
}

//check vardec
node *GBCvardec( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvardec");
	DBUG_RETURN(arg_node);
}

//traverse over assign
node *GBCassign( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCassign");
	ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
	ASSIGN_LET(arg_node) = TRAVdo(ASSIGN_LET(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

//write binop code
node *GBCbinop( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCbinop");
	//traverse first to put operands on stack
	BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
	BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);

	//check which operand you have to write down
	if(BINOP_OP(arg_node) == BO_add){
		if(BINOP_OPTYPE(arg_node) == T_int){
			fputs("iadd\n", INFO_CODE(arg_info));
		}
		else if(BINOP_OPTYPE(arg_node) == T_float){
			fputs("fadd\n", INFO_CODE(arg_info));
		}
	}
	else if(BINOP_OP(arg_node) == BO_mul){
		if(BINOP_OPTYPE(arg_node) == T_int){
			fputs("imul\n", INFO_CODE(arg_info));
		}
		else if(BINOP_OPTYPE(arg_node) == T_float){
			fputs("fmul\n", INFO_CODE(arg_info));
		}
	}
	else if(BINOP_OP(arg_node) == BO_sub){
		if(BINOP_OPTYPE(arg_node) == T_int){
			fputs("isub\n", INFO_CODE(arg_info));
		}
		else if(BINOP_OPTYPE(arg_node) == T_float){
			fputs("fsub\n", INFO_CODE(arg_info));
		}
	}
	else if(BINOP_OP(arg_node) == BO_div){
		if(BINOP_OPTYPE(arg_node) == T_int){
			fputs("idiv\n", INFO_CODE(arg_info));
		}
		else if(BINOP_OPTYPE(arg_node) == T_float){
			fputs("fdiv\n", INFO_CODE(arg_info));
		}
	}
	else if(BINOP_OP(arg_node) == BO_mod){
		fputs("irem\n", INFO_CODE(arg_info));
	}
	DBUG_RETURN(arg_node);
}

//write code var
node *GBCvar( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvar");
	int place = -1;

	printf("CHECKvar\n");
	
	if(VAR_DECL(arg_node) != NULL){
		if(SYMBOL_STATE(VAR_DECL(arg_node)) == -1){
			SYMBOL_STATE(VAR_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
			INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
		}
		place = SYMBOL_STATE(VAR_DECL(arg_node));
		if(SYMBOL_STATE(VAR_DECL(arg_node)) == 0){
			fputs("iload_0\n", INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 1){
			fputs("iload_1\n", INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 2){
			fputs("iload_2\n", INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 3){
			fputs("iload_3\n", INFO_CODE(arg_info));
		}
		else{
			char buffer[1];
			sprintf(buffer, "%d", place);
			char *command = STRcatn(3, "iload ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
	}
	
	
	
	DBUG_RETURN(arg_node);
}

//write code varlet
node *GBCvarlet( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvarlet");
	int place = -1;

	printf("CHECK\n");
	
	if(VARLET_DECL(arg_node) != NULL){
		printf("CHECK NULL\n");
		if(SYMBOL_STATE(VARLET_DECL(arg_node)) == -1){
			SYMBOL_STATE(VARLET_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
			INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
		}
		place = SYMBOL_STATE(VARLET_DECL(arg_node));
	}
	
	
	char buffer[1];
	sprintf(buffer, "%d", place);
	char *command = STRcatn(3, "istore ", buffer, "\n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

//write code return
node *GBCreturn( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCreturn");
	//no time left to make this depend on type...
	fputs("ireturn\n", INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

//write load for constant
node *GBCnum( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCnum");
	if(NUM_VALUE(arg_node) == 0){
		fputs("iloadc_0\n", INFO_CODE(arg_info));
	}
	else if (NUM_VALUE(arg_node) == 1){
		fputs("iloadc_1\n", INFO_CODE(arg_info));
	}
	else if (NUM_VALUE(arg_node) == -1){
		fputs("iloadc_m1\n", INFO_CODE(arg_info));
	}
	else {
		if(INFO_CONSTCOUNT(arg_info) == 0){
			fputs("iloadc 0\n", INFO_CODE(arg_info));
			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
		}
		else{
			char buffer[1];
			sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));
			char *command  = STRcatn(3,"iloadc ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
		}
	}
	DBUG_RETURN(arg_node);
}

//write assembly float constant
node *GBCfloat( node *arg_node, info *arg_info){
	DBUG_ENTER("CBGfloat");
	if(FLOAT_VALUE(arg_node) == 0.0){
		fputs("floadc_0\n", INFO_CODE(arg_info));
	}
	else if (FLOAT_VALUE(arg_node) == 1.0){
		fputs("floadc_1\n", INFO_CODE(arg_info));
	}
	else {
		if(INFO_CONSTCOUNT(arg_info) == 0){
			fputs("floadc 0\n", INFO_CODE(arg_info));
			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
		}
		else{
			char buffer[1];
			sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));
			char *command  = STRcatn(3,"floadc ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
		}
	}
	DBUG_RETURN(arg_node);
}

//write assembly bool constant
node *GBCbool( node *arg_node, info *arg_info){
	DBUG_ENTER("DBGbool");
	if(BOOL_VALUE(arg_node) == 0){
		fputs("bloadc_f\n", INFO_CODE(arg_info));
	}
	else {
		fputs("bloadc_t\n", INFO_CODE(arg_info));
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

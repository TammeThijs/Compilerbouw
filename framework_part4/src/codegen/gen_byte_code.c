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
	int branchcount;
	int varcount;
	int constantcount;
	node *consts [50];
};

#define INFO_CODE(n) ((n)->code)
#define INFO_BRANCHCOUNT(n) ((n)->branchcount)
#define INFO_VARCOUNT(n) ((n)->varcount)
#define INFO_CONSTCOUNT(n) ((n)->constantcount)
#define INFO_CONSTS(n) ((n)->consts)

static info *MakeInfo(void)
{
	info *result;

	DBUG_ENTER( "MakeInfo");

	result = (info *)MEMmalloc(sizeof(info));
	INFO_CODE(result) = fopen("program.out", "w+");
	INFO_BRANCHCOUNT(result) = 0;
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

node *GBCprogram(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCprogram");
	PROGRAM_DECLARATIONS(arg_node) = TRAVdo(PROGRAM_DECLARATIONS(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCsymbol(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCsymbol");
	DBUG_RETURN(arg_node);
}

node *GBCfsymbol(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfsymbol");
	DBUG_RETURN(arg_node);
}

node *GBCdeclarations(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCdeclarations");
	DECLARATIONS_DECL(arg_node) = TRAVdo(DECLARATIONS_DECL(arg_node), arg_info);
	DECLARATIONS_NEXT(arg_node) = TRAVopt(DECLARATIONS_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCfundefs(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfundefs");
	FUNDEFS_FUNDEF(arg_node) = TRAVdo(FUNDEFS_FUNDEF(arg_node), arg_info);
	FUNDEFS_NEXT(arg_node) = TRAVopt(FUNDEFS_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

//check if function name = main, if so then traverse
node *GBCfundef(node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfundef");
	char *main_name = "main";
	int locals  = 0;
	if(FUNDEF_SYMBOLTABLE(arg_node)!= NULL){
		locals = 1;
		node * symbol = FUNDEF_SYMBOLTABLE(arg_node);
		while(SYMBOL_NEXT(symbol) != NULL){
			locals = locals + 1;
			symbol = SYMBOL_NEXT(symbol);
		}
	}
	//check if it is main
	if(STReq(FUNDEF_NAME(arg_node), main_name)){
		fputs("main:\n", INFO_CODE(arg_info));
		char buffer[20];
		sprintf(buffer, "%d", locals);
		char *command = STRcatn(3, "esr ", buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
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

node *GBCglobaldef( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCglobaldef");
	GLOBALDEF_DIMS(arg_node) = TRAVopt(GLOBALDEF_DIMS(arg_node), arg_info);
	GLOBALDEF_INIT(arg_node) = TRAVopt(GLOBALDEF_INIT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCglobaldec( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCglobaldec");
	GLOBALDEC_DIMS(arg_node) = TRAVopt(GLOBALDEC_DIMS(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCids( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCids");
	IDS_NEXT(arg_node) = TRAVopt(IDS_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCfunbody( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfunbody");
	FUNBODY_VARDEC(arg_node) = TRAVopt(FUNBODY_VARDEC(arg_node), arg_info);
	FUNBODY_LOCALFUNDEFS(arg_node) = TRAVopt(FUNBODY_LOCALFUNDEFS(arg_node), arg_info);
	FUNBODY_STATEMENT(arg_node) = TRAVopt(FUNBODY_STATEMENT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCparam( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCparam");
	PARAM_DIMS(arg_node) = TRAVdo( PARAM_DIMS(arg_node), arg_info);
	PARAM_NEXT(arg_node) = TRAVopt(PARAM_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCcast( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCcast");
	DBUG_RETURN(arg_node);
}

node *GBCexprs( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCexprs");
	EXPRS_EXPRS(arg_node) = TRAVdo( EXPRS_EXPRS(arg_node), arg_info);
	EXPRS_NEXT(arg_node) = TRAVopt(EXPRS_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCstmts( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCstmts");
	STMTS_STMT(arg_node) = TRAVdo( STMTS_STMT(arg_node), arg_info);
	STMTS_NEXT(arg_node) = TRAVopt(STMTS_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

//check vardec
node *GBCvardec( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvardec");
	VARDEC_INIT(arg_node) = TRAVopt(VARDEC_INIT(arg_node), arg_info);
	VARDEC_NEXT(arg_node) = TRAVopt(VARDEC_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

//traverse over assign
node *GBCassign( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCassign");
	ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
	ASSIGN_LET(arg_node) = TRAVdo(ASSIGN_LET(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCarrexpr( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCexprs");
	ARREXPR_EXPRS(arg_node) = TRAVdo( ARREXPR_EXPRS(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCfuncall( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfuncall");
	FUNCALL_ARGS(arg_node) = TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

//write binop code
node *GBCbinop( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCbinop");
	//traverse first to put operands on stack
	BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
	BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
	char *type;
	if(BINOP_OPTYPE(arg_node) == T_int){
		type = "i";
	}
	else if (BINOP_OPTYPE(arg_node) == T_float){
		type = "f";
	}
	else{
		type = "b";
	}
	//check which operand you have to write down
	if(BINOP_OP(arg_node) == BO_add){
		char *ass = STRcat(type, "add\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_mul){
		char *ass = STRcat(type, "mul\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_sub){
		char *ass = STRcat(type, "sub\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_div){
		char *ass = STRcat(type, "div\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_mod){
		fputs("irem\n", INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_lt){
		char *ass = STRcat(type, "lt\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_le){
		char *ass = STRcat(type, "le\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_gt){
		char *ass = STRcat(type, "gt\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_ge){
		char *ass = STRcat(type, "ge\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_eq){
		char *ass = STRcat(type, "eq\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_ne){
		char *ass = STRcat(type, "ne\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	DBUG_RETURN(arg_node);
}

//write assembly for monop
node *GBCmonop( node *arg_node, info *arg_info){
	DBUG_ENTER("CBGmonop");
	MONOP_OPERAND(arg_node) = TRAVdo(MONOP_OPERAND(arg_node), arg_info);
	if(MONOP_OP(arg_node) == MO_not){
		fputs("bnot\n", INFO_CODE(arg_info));
	}
	else{
		if(MONOP_OPTYPE(arg_node) == T_int){
			fputs("ineg\n", INFO_CODE(arg_info));
		}
		else{
			fputs("fneg\n", INFO_CODE(arg_info));
		}
	}
	DBUG_RETURN(arg_node);
}
//write code var
node *GBCvar( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvar");
	int place = -1;
	char *type;
	if(VAR_DECL(arg_node) != NULL){
		if(SYMBOL_STATE(VAR_DECL(arg_node)) == place){
			SYMBOL_STATE(VAR_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
			INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
		}
		place = SYMBOL_STATE(VAR_DECL(arg_node));
		if (SYMBOL_TYPE(VAR_DECL(arg_node)) == T_int){
			type = "i";
		}
		else if(SYMBOL_TYPE(VAR_DECL(arg_node)) == T_float){
			type = "f";
		}
		else{
			type = "b";
		}
		if(SYMBOL_STATE(VAR_DECL(arg_node)) == 0){
			char *string = STRcat(type,"load_0\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 1){
			char *string = STRcat(type,"load_1\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 2){
			char *string = STRcat(type,"load_2\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 3){
			char *string = STRcat(type,"load_3\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else{
			char buffer[1];
			sprintf(buffer, "%d", place);
			char *string = STRcat(type,"load ");
			char *command = STRcatn(3, string, buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
	}
	
	
	
	DBUG_RETURN(arg_node);
}

//write code varlet
node *GBCvarlet( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvarlet");
	int place = -1;
	char *type;
	if(VARLET_DECL(arg_node) != NULL){
		if(SYMBOL_STATE(VARLET_DECL(arg_node)) == place){
			SYMBOL_STATE(VARLET_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
			INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
		}
		place = SYMBOL_STATE(VARLET_DECL(arg_node));
		if(SYMBOL_TYPE(VARLET_DECL(arg_node)) == T_int){
			type = "i";
		}
		else if(SYMBOL_TYPE(VARLET_DECL(arg_node)) == T_float){
			type = "f";
		}
		else{
			type = "b";
		}
	}
	
	
	char buffer[1];
	sprintf(buffer, "%d", place);
	char *string = STRcat(type, "store ");
	char *command = STRcatn(3, string, buffer, "\n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

//write code return
node *GBCreturn( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCreturn");
	printf("in de return");
	if(RETURN_TYPE(arg_node) == T_int){
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		fputs("ireturn\n", INFO_CODE(arg_info));
	}
	else if(RETURN_TYPE(arg_node) == T_float){
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		fputs("freturn\n", INFO_CODE(arg_info));
	}
	else if(RETURN_TYPE(arg_node) == T_boolean){
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		fputs("breturn\n", INFO_CODE(arg_info));
	}
	else{
		fputs("return\n", INFO_CODE(arg_info));
	}
	DBUG_RETURN(arg_node);
}

node *GBCconditionexpr( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCconditionexpr");
	CONDITIONEXPR_IF(arg_node) = TRAVdo(CONDITIONEXPR_IF(arg_node), arg_info);
	char buffer[20];
	char *command;
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	command = STRcatn(3,"branch_f ", buffer, "_false_expr\n");
	fputs(command, INFO_CODE(arg_info));
	CONDITIONEXPR_ELSE(arg_node) = TRAVdo(CONDITIONEXPR_ELSE(arg_node), arg_info);
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	command = STRcatn(3,"jump ", buffer, "_end\n");
	fputs(command, INFO_CODE(arg_info));
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info)-1);
	command = STRcat(buffer, "_false_expr:\n");
	fputs(command, INFO_CODE(arg_info));
	CONDITIONEXPR_THEN(arg_node) = TRAVdo(CONDITIONEXPR_THEN(arg_node), arg_info);
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	command = STRcat(buffer, "_end:\n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

node *GBCexprstmt( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCexprstmt");
	EXPRSTMT_EXPR(arg_node) = TRAVdo(EXPRSTMT_EXPR(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *GBCif( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCif");
	IF_CONDITION(arg_node) = TRAVdo(IF_CONDITION(arg_node), arg_info);
	char buffer[20];
	char *command;
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	if(IF_ELSEBLOCK(arg_node) != NULL){
		sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
		command = STRcatn(3,"branch_f ", buffer, "_else\n");
		fputs(command, INFO_CODE(arg_info));
		IF_IFBLOCK(arg_node) = TRAVdo(IF_IFBLOCK(arg_node), arg_info);
		INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
		sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
		command = STRcatn(3,"jump ", buffer, "_end\n");
		fputs(command, INFO_CODE(arg_info));
		command = STRcat(buffer, "_else:\n");
		fputs(command, INFO_CODE(arg_info));
		IF_ELSEBLOCK(arg_node) = TRAVdo(IF_ELSEBLOCK(arg_node), arg_info);
		
	}
	
	command = STRcat(buffer, "_end:\n");
	fputs(command, INFO_CODE(arg_info));
	
	DBUG_RETURN(arg_node);
}

node *GBCwhile( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCwhile");
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	char buffer[20];
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	char *commandwhile = STRcat(buffer, "_while");
	char *command = STRcat(commandwhile, ":\n");
	fputs(command, INFO_CODE(arg_info));
	WHILE_CONDITION(arg_node) = TRAVdo(WHILE_CONDITION(arg_node), arg_info);
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	command = STRcatn(3, "branch_f ", buffer, "_end\n");
	fputs(command, INFO_CODE(arg_info));
	WHILE_BLOCK(arg_node) = TRAVdo(WHILE_BLOCK(arg_node), arg_info);
	command = STRcatn(3,"jump ", commandwhile, "\n");
	fputs(command, INFO_CODE(arg_info));
	command = STRcat(buffer, "_end: \n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

node *GBCdowhile( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCdowhile");
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	char buffer[20];
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	char *commandwhile = STRcat(buffer, "_dowhile");
	char *command = STRcat(commandwhile, ":\n");
	fputs(command, INFO_CODE(arg_info));
	DOWHILE_BLOCK(arg_node) = TRAVdo(DOWHILE_BLOCK(arg_node), arg_info);
	DOWHILE_CONDITION(arg_node) = TRAVdo(DOWHILE_CONDITION(arg_node), arg_info);
	command = STRcatn(3, "branch_t ", commandwhile, "\n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

node *GBCfor( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfor");
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

node *GBCerror( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCerror");
	DBUG_RETURN(arg_node);
}
/*
 * Traversal start function
 */

node *GBCdoGenByteCode( node *syntaxtree)
{
  

  info *arg_info;
  DBUG_ENTER("GBCdoGenByteCode");
  printf("bytecode maken\n");
  arg_info = MakeInfo();

  TRAVpush( TR_gbc);   // Push traversal "cbg" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);

}

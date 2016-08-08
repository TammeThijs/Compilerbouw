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
	int exportfuncount;
	int importfuncount;
	node *consts [50];
	node *exportfun [50];
	node *importfun [50];
	int scope;
};

#define INFO_CODE(n) ((n)->code)
#define INFO_BRANCHCOUNT(n) ((n)->branchcount)
#define INFO_VARCOUNT(n) ((n)->varcount)
#define INFO_CONSTCOUNT(n) ((n)->constantcount)
#define INFO_EXPORTFUNCOUNT(n) ((n)->exportfuncount)
#define INFO_IMPORTFUNCOUNT(n) ((n)->importfuncount)
#define INFO_CONSTS(n) ((n)->consts)
#define INFO_EXPORTFUN(n) ((n)->exportfun)
#define INFO_IMPORTFUN(n) ((n)->importfun)
#define INFO_SCOPE(n) ((n)->scope)

static info *MakeInfo(void)
{
	info *result;

	DBUG_ENTER( "MakeInfo");

	result = (info *)MEMmalloc(sizeof(info));
	INFO_CODE(result) = fopen("program.out", "w+");
	INFO_BRANCHCOUNT(result) = 0;
	INFO_VARCOUNT(result) = 0;
	INFO_CONSTCOUNT(result) = 0;
	INFO_EXPORTFUNCOUNT(result) = 0;
	INFO_IMPORTFUNCOUNT(result) = 0;
	INFO_SCOPE(result) = -1;
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
	char buffer[20];
	char *command;
	//write constants
	for(int i = 0; i<INFO_CONSTCOUNT(arg_info); i++){
		if(NODE_TYPE(INFO_CONSTS(arg_info)[i]) == 30){
			sprintf(buffer, "%d", NUM_VALUE(INFO_CONSTS(arg_info)[i]));
			command = STRcatn(3, ".const int  ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
		else if(NODE_TYPE(INFO_CONSTS(arg_info)[i]) == 31){
			sprintf(buffer, "%f", FLOAT_VALUE(INFO_CONSTS(arg_info)[i]));
			command = STRcatn(3, ".const float  ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
	}
	for(int i = 0; i<INFO_EXPORTFUNCOUNT(arg_info); i++){
		node *fun = INFO_EXPORTFUN(arg_info)[i];
		command = STRcatn(4, ".exportfun ", "\"", FUNDEF_NAME(fun), "\" ");
		if(FUNDEF_TYPE(fun) == T_int){
			command = STRcat(command, "int ");
		}
		else if(FUNDEF_TYPE(fun) == T_float){
			command = STRcat(command, "float ");
		}
		else if(FUNDEF_TYPE(fun) == T_boolean){
			command = STRcat(command, "bool ");
		}
		else{
			command = STRcat(command, "void ");
		}
		if(FUNDEF_PARAMS(fun)!= NULL){
			node *param = FUNDEF_PARAMS(fun);
			do{
				if(PARAM_TYPE(param) == T_int){
					command = STRcat(command, "int ");
				}
				else if(PARAM_TYPE(param) == T_float){
					command = STRcat(command, "float ");
				}
				else{
					command = STRcat(command, "bool ");
				}
				param = PARAM_NEXT(param);
				
			}while(param != NULL);
		}
		command = STRcatn(3, command, FUNDEF_NAME(fun), "\n");
		fputs(command, INFO_CODE(arg_info));
	}

	for(int i = 0; i<INFO_IMPORTFUNCOUNT(arg_info); i++){
		printf("assembly code import table maken");
		node *fun = INFO_IMPORTFUN(arg_info)[i];
		command = STRcatn(4, ".importfun ", "\"", FUNDEF_NAME(fun), "\" ");
		if(FUNDEF_TYPE(fun) == T_int){
			command = STRcat(command, "int ");
		}
		else if(FUNDEF_TYPE(fun) == T_float){
			command = STRcat(command, "float ");
		}
		else if(FUNDEF_TYPE(fun) == T_boolean){
			command = STRcat(command, "bool ");
		}
		else{
			command = STRcat(command, "void ");
		}
		if(FUNDEF_PARAMS(fun)!= NULL){
			node *param = FUNDEF_PARAMS(fun);
			do{
				if(PARAM_TYPE(param) == T_int){
					command = STRcat(command, "int ");
				}
				else if(PARAM_TYPE(param) == T_float){
					command = STRcat(command, "float ");
				}
				else{
					command = STRcat(command, "bool ");
				}
				param = PARAM_NEXT(param);
				
			}while(param != NULL);
		}
		command = STRcat(command, "\n");
		fputs(command, INFO_CODE(arg_info));
	}

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
	char *init_name = "__init";
	char buffer[20];
	int locals  = 0;
	int params = 0;
	INFO_VARCOUNT(arg_info) = 0;
	if(FUNDEF_SYMBOLTABLE(arg_node)!= NULL){
		locals = 1;
		node *symbol = FUNDEF_SYMBOLTABLE(arg_node);
		while(SYMBOL_NEXT(symbol) != NULL){
			locals = locals + 1;
			symbol = SYMBOL_NEXT(symbol);
		}
	}
	if(FUNDEF_PARAMS(arg_node) != NULL){
		params = 1;
		node *param = FUNDEF_PARAMS(arg_node);
		while(PARAM_NEXT(param) != NULL){
			params = params + 1;
			param = PARAM_NEXT(param);
		}
	}
	locals = locals - params;
	if(FUNDEF_FSYMBOLTABLE(arg_node) != NULL){
		node *fsymbol = FUNDEF_FSYMBOLTABLE(arg_node);
		char *newname = STRcatn(4, "_", FUNDEF_NAME(arg_node), "_", FSYMBOL_NAME(fsymbol));
		FSYMBOL_NAME(fsymbol) = newname;
		FUNDEF_NAME(FSYMBOL_FUNCTION(fsymbol)) = newname;
		while(FSYMBOL_NEXT(fsymbol) != NULL){
			fsymbol = FSYMBOL_NEXT(fsymbol);
			newname = STRcatn(4, "_", FUNDEF_NAME(arg_node), "_", FSYMBOL_NAME(fsymbol));
			FSYMBOL_NAME(fsymbol) = newname;
			FUNDEF_NAME(FSYMBOL_FUNCTION(fsymbol)) = newname;
		}
	}
	//check if it is main
	if(STReq(FUNDEF_NAME(arg_node), main_name)){
		fputs("main:\n", INFO_CODE(arg_info));
		if(locals > 0){
			sprintf(buffer, "%d", locals);
			char *command = STRcatn(3, "   esr ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
		
		INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) + 1;
		FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
		INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) - 1;

		
	}
	//if it is not main: also make code.
	else if(! STReq(FUNDEF_NAME(arg_node), init_name) && FUNDEF_EXTERN(arg_node) == FALSE) {
		char *command = STRcat(FUNDEF_NAME(arg_node), ":\n");
		fputs(command, INFO_CODE(arg_info));
		if(locals > 0){
			sprintf(buffer, "%d", locals);
			char *command = STRcatn(3, "   esr ", buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
		INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) + 1;
		FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
		INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) - 1;
	}

	if(FUNDEF_EXPORT(arg_node) == TRUE){
		INFO_EXPORTFUN(arg_info)[INFO_EXPORTFUNCOUNT(arg_info)] = arg_node;
		INFO_EXPORTFUNCOUNT(arg_info) = INFO_EXPORTFUNCOUNT(arg_info) + 1;
	}
	if(FUNDEF_EXTERN(arg_node) == TRUE){
		printf("function in de extern table stopppen");
		INFO_IMPORTFUN(arg_info)[INFO_IMPORTFUNCOUNT(arg_info)] = arg_node;
		INFO_IMPORTFUNCOUNT(arg_info) = INFO_IMPORTFUNCOUNT(arg_info) + 1;
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
	FUNBODY_STATEMENT(arg_node) = TRAVopt(FUNBODY_STATEMENT(arg_node), arg_info);
	INFO_VARCOUNT(arg_info) = 0;
	fputs("\n", INFO_CODE(arg_info));
	FUNBODY_LOCALFUNDEFS(arg_node) = TRAVopt(FUNBODY_LOCALFUNDEFS(arg_node), arg_info);
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
	int scopefuncall = FSYMBOL_SCOPE(FUNCALL_DECL(arg_node));
	char buffer[20];
	char *command;
	if(scopefuncall == 0){
		fputs("   isrg\n", INFO_CODE(arg_info));
	}
	else if(scopefuncall== INFO_SCOPE(arg_info) + 1){
		fputs("   isrl\n", INFO_CODE(arg_info));
	}
	else if(scopefuncall == INFO_SCOPE(arg_info)){
		fputs("   isr\n", INFO_CODE(arg_info));
	}
	else{
		sprintf(buffer, "%d", scopefuncall);
		command = STRcatn(3,"   isrn ", buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
	}
	if(FSYMBOL_EXTERN(FUNCALL_DECL(arg_node)) == TRUE){
		int place = 0;
		for(int i = 0; i < INFO_IMPORTFUNCOUNT(arg_info); i++){
			if(FUNDEF_NAME(INFO_IMPORTFUN(arg_info)[i]) == FUNCALL_NAME(arg_node)){
				place = i;
			}
		}
		sprintf(buffer, "%d\n", place);
		command = STRcat("   jsre ", buffer);
	}
	else{
		FUNCALL_ARGS(arg_node) = TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
	int amountargs = 0;
	node * arg;
	if(FUNCALL_ARGS(arg_node)!= NULL){
		amountargs = 1;
		arg = FUNCALL_ARGS(arg_node);
		while(EXPRS_NEXT(arg) != NULL){
			arg = EXPRS_NEXT(arg);
			amountargs ++;
		}
	}
	
	sprintf(buffer, "%d", amountargs);

	command = STRcatn(5, "   jsr ", buffer, " ", FSYMBOL_NAME(FUNCALL_DECL(arg_node)), "\n");
	}
	

	fputs(command, INFO_CODE(arg_info));
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
		char *ass = STRcatn(3, "   ", type, "add\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_mul){
		char *ass = STRcatn(3, "   ", type, "mul\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_sub){
		char *ass = STRcatn(3, "   ", type, "sub\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_div){
		char *ass = STRcatn(3, "   ", type, "div\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_mod){
		fputs("   irem\n", INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_lt){
		char *ass = STRcatn(3, "   ", type, "lt\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_le){
		char *ass = STRcatn(3, "   ", type, "le\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_gt){
		char *ass = STRcatn(3, "   ", type, "gt\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_ge){
		char *ass = STRcatn(3, "   ", type, "ge\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_eq){
		char *ass = STRcatn(3, "   ", type, "eq\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	else if(BINOP_OP(arg_node) == BO_ne){
		char *ass = STRcatn(3, "   ", type, "ne\n");
		fputs(ass, INFO_CODE(arg_info));
	}
	DBUG_RETURN(arg_node);
}

//write assembly for monop
node *GBCmonop( node *arg_node, info *arg_info){
	DBUG_ENTER("CBGmonop");
	MONOP_OPERAND(arg_node) = TRAVdo(MONOP_OPERAND(arg_node), arg_info);
	if(MONOP_OP(arg_node) == MO_not){
		fputs("   bnot\n", INFO_CODE(arg_info));
	}
	else{
		if(MONOP_OPTYPE(arg_node) == T_int){
			fputs("   ineg\n", INFO_CODE(arg_info));
		}
		else{
			fputs("   fneg\n", INFO_CODE(arg_info));
		}
	}
	DBUG_RETURN(arg_node);
}
//write code var
node *GBCvar( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvar");
	printf("in de var\n");
	int place = -1;
	char buffer[5];
	char buffer2 [5];
	char *type;
	printf("voor de type");
	if (SYMBOL_TYPE(VAR_DECL(arg_node)) == T_int){
		type = "i";
	}
	else if(SYMBOL_TYPE(VAR_DECL(arg_node)) == T_float){
		type = "f";
	}
	else{
		type = "b";
	}
	printf("na de type");
	if(SYMBOL_STATE(VAR_DECL(arg_node)) == place && SYMBOL_SCOPE(VAR_DECL(arg_node)) == (INFO_SCOPE(arg_info) + 1)){
		SYMBOL_STATE(VAR_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
		INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
	}
	place = SYMBOL_STATE(VAR_DECL(arg_node));
	printf("na de place");
	if(SYMBOL_SCOPE(VAR_DECL(arg_node)) == INFO_SCOPE(arg_info) + 1){
		printf("in de local if");

		if(SYMBOL_STATE(VAR_DECL(arg_node)) == 0){
			char *string = STRcatn(3, "   ", type,"load_0\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 1){
			char *string = STRcatn(3, "   ", type,"load_1\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 2){
			char *string = STRcatn(3, "   ", type,"load_2\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else if (SYMBOL_STATE(VAR_DECL(arg_node)) == 3){
			char *string = STRcatn(3, "   ", type,"load_3\n");
			fputs(string, INFO_CODE(arg_info));
		}
		else{
			sprintf(buffer, "%d", place);
			char *string = STRcatn(3, "   ", type,"load ");
			char *command = STRcatn(3, string, buffer, "\n");
			fputs(command, INFO_CODE(arg_info));
		}
	}
	else if(SYMBOL_SCOPE(VAR_DECL(arg_node)) == 0){
		printf("in de global if");
		sprintf(buffer, "%d", place);
		char *string = STRcatn(3, "   ", type,"loadg ");
		char *command = STRcatn(3, string, buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
	}
	else{
		printf("in de n if");
		sprintf(buffer, "%d", place);
		sprintf(buffer2, "%d ", SYMBOL_SCOPE(VAR_DECL(arg_node)));
		char *string = STRcatn(3, "   ", type,"loadn ");
		char *command = STRcatn(4, string, buffer2, buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
	}

	
	
	
	DBUG_RETURN(arg_node);
}

//write code varlet
node *GBCvarlet( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCvarlet");
	printf("in de varlet");
	int place = -1;
	char buffer[5];
	char buffer2 [5];
	char *type;
	printf("SYMBOL SCOPE: %d, INFO SCOPE: %d\n", SYMBOL_SCOPE(VARLET_DECL(arg_node)), INFO_SCOPE(arg_info));
	if(SYMBOL_TYPE(VARLET_DECL(arg_node)) == T_int){
		type = "i";
	}
	else if(SYMBOL_TYPE(VARLET_DECL(arg_node)) == T_float){
		type = "f";
	}
	else{
		type = "b";
	}
	if(SYMBOL_STATE(VARLET_DECL(arg_node)) == place && SYMBOL_SCOPE(VARLET_DECL(arg_node)) == (INFO_SCOPE(arg_info) + 1)){
		SYMBOL_STATE(VARLET_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
		INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
	}
	place = SYMBOL_STATE(VARLET_DECL(arg_node));
	if(SYMBOL_SCOPE(VARLET_DECL(arg_node)) == INFO_SCOPE(arg_info) + 1){
		sprintf(buffer, "%d", place);
		char *string = STRcatn(3, "   ", type, "store ");
		char *command = STRcatn(3, string, buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
	}
	else if( SYMBOL_SCOPE(VARLET_DECL(arg_node)) == 0){
		sprintf(buffer, "%d", place);
		char *string = STRcatn(3, "   ", type, "storeg ");
		char *command = STRcatn(3, string, buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
	}
	else{
		sprintf(buffer, "%d", place);
		sprintf(buffer2, "%d ", INFO_SCOPE(arg_info) - SYMBOL_SCOPE(VARLET_DECL(arg_node)));
		char *string = STRcatn(3, "   ", type, "storen ");
		char *command = STRcatn(4, string, buffer2, buffer, "\n");
		fputs(command, INFO_CODE(arg_info));
	}
	
	DBUG_RETURN(arg_node);
}

//write code return
node *GBCreturn( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCreturn");
	if(RETURN_TYPE(arg_node) == T_int){
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		fputs("   ireturn\n", INFO_CODE(arg_info));
	}
	else if(RETURN_TYPE(arg_node) == T_float){
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		fputs("   freturn\n", INFO_CODE(arg_info));
	}
	else if(RETURN_TYPE(arg_node) == T_boolean){
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		fputs("   breturn\n", INFO_CODE(arg_info));
	}
	else{
		fputs("   return\n", INFO_CODE(arg_info));
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
	command = STRcatn(3,"   branch_f ", buffer, "_false_expr\n");
	fputs(command, INFO_CODE(arg_info));
	CONDITIONEXPR_ELSE(arg_node) = TRAVdo(CONDITIONEXPR_ELSE(arg_node), arg_info);
	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
	command = STRcatn(3,"   jump ", buffer, "_end\n");
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
		command = STRcatn(3,"   branch_f ", buffer, "_else\n");
		fputs(command, INFO_CODE(arg_info));
		IF_IFBLOCK(arg_node) = TRAVdo(IF_IFBLOCK(arg_node), arg_info);
		INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
		sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
		command = STRcatn(3,"   jump ", buffer, "_end\n");
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
	command = STRcatn(3, "   branch_f ", buffer, "_end\n");
	fputs(command, INFO_CODE(arg_info));
	WHILE_BLOCK(arg_node) = TRAVdo(WHILE_BLOCK(arg_node), arg_info);
	command = STRcatn(3,"   jump ", commandwhile, "\n");
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
	command = STRcatn(3, "   branch_t ", commandwhile, "\n");
	fputs(command, INFO_CODE(arg_info));
	DBUG_RETURN(arg_node);
}

node *GBCfor( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCfor");
	int start = 0;
	int stop = 1;
	int step = 1;
	if(NODE_TYPE(VARDEC_INIT(FOR_START(arg_node))) == 30){
		start = NUM_VALUE(VARDEC_INIT(FOR_START(arg_node)));
	}
	if(NODE_TYPE(FOR_STOP(arg_node)) == 30){
		stop = NUM_VALUE(FOR_STOP(arg_node));
	}
	if(FOR_STEP(arg_node) != NULL && NODE_TYPE(FOR_STEP(arg_node)) == 30){
		step = NUM_VALUE(FOR_STEP(arg_node));
	}
	for(int i = start; i< stop; i = i + step){
		FOR_BLOCK(arg_node) = TRAVopt(FOR_BLOCK(arg_node), arg_info);
		FOR_BLOCK(arg_node) = TRAVopt(FOR_BLOCKSINGLE(arg_node), arg_info);
	}

	
	DBUG_RETURN(arg_node);
}
//write load for constant
node *GBCnum( node *arg_node, info *arg_info){
	DBUG_ENTER("GBCnum");
	if(NUM_VALUE(arg_node) == 0){
		fputs("   iloadc_0\n", INFO_CODE(arg_info));
	}
	else if (NUM_VALUE(arg_node) == 1){
		fputs("   iloadc_1\n", INFO_CODE(arg_info));
	}
	else if (NUM_VALUE(arg_node) == -1){
		fputs("   iloadc_m1\n", INFO_CODE(arg_info));
	}
	else {
		if(INFO_CONSTCOUNT(arg_info) == 0){
			fputs("   iloadc 0\n", INFO_CODE(arg_info));
			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
		}
		else{
			int value = NUM_VALUE(arg_node);
			int plek = 0;
			int gevonden = 0;
			char buffer[5];
			while(plek < INFO_CONSTCOUNT(arg_info) && !gevonden){
				if(NUM_VALUE(INFO_CONSTS(arg_info)[plek]) == value){
					gevonden = 1;
					sprintf(buffer, "%d", plek);
				}
				else{
					plek++;
				}
			}
			
			if(gevonden == 0){
				sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));
			}
			char *command  = STRcatn(3,"   iloadc ", buffer, "\n");
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
		fputs("   floadc_0\n", INFO_CODE(arg_info));
	}
	else if (FLOAT_VALUE(arg_node) == 1.0){
		fputs("   floadc_1\n", INFO_CODE(arg_info));
	}
	else {
		if(INFO_CONSTCOUNT(arg_info) == 0){
			fputs("   floadc 0\n", INFO_CODE(arg_info));
			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
		}
		else{
			char buffer[1];
			sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));
			char *command  = STRcatn(3,"   floadc ", buffer, "\n");
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
		fputs("   bloadc_f\n", INFO_CODE(arg_info));
	}
	else {
		fputs("   bloadc_t\n", INFO_CODE(arg_info));
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

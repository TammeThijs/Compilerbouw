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
#include "globals.h"

 struct INFO {
 	FILE *code;
 	int branchcount;
 	int varcount;
 	int constantcount;
 	int exportfuncount;
 	int importfuncount;
 	int importvarcount;
 	int exportvarcount;
 	int globalvarcount;
 	int globalvarletcount;
 	int globalsymbolcount;
 	type fundeftype;
 	node *consts [50];
 	node *exportfun [50];
 	node *importfun [50];
 	node *importvar [50];
 	node *exportvar [50];
 	node *globalvar [50];
 	int scope;
 	bool inFor;
 };

#define INFO_CODE(n) ((n)->code)
#define INFO_BRANCHCOUNT(n) ((n)->branchcount)
#define INFO_VARCOUNT(n) ((n)->varcount)
#define INFO_CONSTCOUNT(n) ((n)->constantcount)
#define INFO_EXPORTFUNCOUNT(n) ((n)->exportfuncount)
#define INFO_IMPORTFUNCOUNT(n) ((n)->importfuncount)
#define INFO_IMPORTVARCOUNT(n) ((n)->importvarcount)
#define INFO_EXPORTVARCOUNT(n) ((n)->exportvarcount)
#define INFO_GLOBALVARCOUNT(n) ((n)->globalvarcount)
#define INFO_GLOBALVARLETCOUNT(n) ((n)->globalvarletcount)
#define INFO_GLOBALSYMBOLCOUNT(n) ((n)->globalsymbolcount)
#define INFO_FUNDEFTYPE(n) ((n)->fundeftype)
#define INFO_CONSTS(n) ((n)->consts)
#define INFO_EXPORTFUN(n) ((n)->exportfun)
#define INFO_IMPORTFUN(n) ((n)->importfun)
#define INFO_IMPORTVAR(n) ((n)->importvar)
#define INFO_EXPORTVAR(n) ((n)->exportvar)
#define INFO_GLOBALVAR(n) ((n)->globalvar)
#define INFO_SCOPE(n) ((n)->scope)
#define INFO_INFOR(n) ((n)->inFor)

 static info *MakeInfo(void)
 {
 	info *result;

 	DBUG_ENTER( "MakeInfo");

 	result = (info *)MEMmalloc(sizeof(info));
 	INFO_CODE(result) = fopen(global.outfile, "w+");
 	INFO_BRANCHCOUNT(result) = 0;
 	INFO_VARCOUNT(result) = 0;
 	INFO_CONSTCOUNT(result) = 0;
 	INFO_EXPORTFUNCOUNT(result) = 0;
 	INFO_IMPORTFUNCOUNT(result) = 0;
 	INFO_IMPORTVARCOUNT(result) = 0;
 	INFO_EXPORTVARCOUNT(result) = 0;
 	INFO_GLOBALVARCOUNT(result) = 0;
 	INFO_GLOBALSYMBOLCOUNT( result) = 0;
 	INFO_GLOBALVARLETCOUNT( result) = 0;
 	INFO_SCOPE(result) = -1;
 	INFO_FUNDEFTYPE( result) = T_int;
 	INFO_INFOR( result) = FALSE;
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
 	if(PROGRAM_SYMBOLTABLE(arg_node) != NULL){
 		node *symbol = PROGRAM_SYMBOLTABLE(arg_node);
 		if(!SYMBOL_EXTERN(symbol)){
 			INFO_GLOBALSYMBOLCOUNT(arg_info) = INFO_GLOBALSYMBOLCOUNT(arg_info) + 1;
 		}
 		while(SYMBOL_NEXT(symbol) != NULL){
 			symbol = SYMBOL_NEXT(symbol);
 			if(!SYMBOL_EXTERN(symbol)){
 				INFO_GLOBALSYMBOLCOUNT(arg_info) = INFO_GLOBALSYMBOLCOUNT(arg_info) + 1;
 			}
 		}
 	}
 	PROGRAM_DECLARATIONS(arg_node) = TRAVdo(PROGRAM_DECLARATIONS(arg_node), arg_info);
 	char buffer[20];
 	char *command;
	//write constants
 	for(int i = 0; i<INFO_CONSTCOUNT(arg_info); i++){
 		if(NODE_TYPE(INFO_CONSTS(arg_info)[i]) == N_num){
 			sprintf(buffer, "%d", NUM_VALUE(INFO_CONSTS(arg_info)[i]));
 			command = STRcatn(3, ".const int  ", buffer, "\n");
 			fputs(command, INFO_CODE(arg_info));
 		}
 		else if(NODE_TYPE(INFO_CONSTS(arg_info)[i]) == N_float){
 			sprintf(buffer, "%f", FLOAT_VALUE(INFO_CONSTS(arg_info)[i]));
 			command = STRcatn(3, ".const float  ", buffer, "\n");
 			fputs(command, INFO_CODE(arg_info));
 		}
 	}
 	for(int i = 0; i<INFO_EXPORTFUNCOUNT(arg_info); i++){
 		if(!(STReq(FUNDEF_NAME(INFO_EXPORTFUN(arg_info)[i]), "__init") && INFO_GLOBALSYMBOLCOUNT(arg_info) == 0)){
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
 	}
 	

 	for(int i = 0; i<INFO_IMPORTFUNCOUNT(arg_info); i++){
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

 	for(int i = 0; i < INFO_IMPORTVARCOUNT(arg_info); i++){
 		node *var = INFO_IMPORTVAR(arg_info)[i];
 		command = STRcatn(4, ".importvar ", "\"", GLOBALDEC_NAME(var), "\" ");
 		if(GLOBALDEC_TYPE(var) == T_int){
 			command = STRcat(command, "int\n");
 		}
 		else if(GLOBALDEC_TYPE(var) == T_float){
 			command = STRcat(command, "float\n");
 		}
 		else{
 			command = STRcat(command, "bool\n");
 		}
 		fputs(command, INFO_CODE(arg_info));
 	}

 	for(int i = 0; i < INFO_EXPORTVARCOUNT(arg_info); i++){
 		node *var = INFO_EXPORTVAR(arg_info)[i];
 		int place = i;
 		bool gevonden = FALSE;
 		while(!gevonden && place < INFO_GLOBALVARCOUNT(arg_info)){
 			node *globalvar = INFO_GLOBALVAR(arg_info)[place];
 			if(GLOBALDEF_NAME(globalvar) == GLOBALDEF_NAME(var)){
 				gevonden = TRUE;
 			}
 			else{
 				place ++;
 			}
 			
 		}
 		sprintf(buffer, "%d\n", place);
 		command = STRcatn(5, ".exportvar ", "\"", GLOBALDEF_NAME(var), "\" ", buffer);
 		fputs(command, INFO_CODE(arg_info));
 	}

 	for(int i = 0; i < INFO_GLOBALVARCOUNT(arg_info); i++){
 		node *var = INFO_GLOBALVAR(arg_info)[i];
 		if(GLOBALDEF_TYPE(var) == T_int){
 			command = ".global int\n";
 		}
 		else if(GLOBALDEF_TYPE(var) == T_float){
 			command = ".global float\n";
 		}
 		else{
 			command = ".global bool\n";
 		}
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

 	INFO_FUNDEFTYPE(arg_info) = FUNDEF_TYPE(arg_node);
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
 	else if(STReq(FUNDEF_NAME(arg_node), init_name) && INFO_GLOBALSYMBOLCOUNT(arg_info) > 0){
 		fputs("__init:\n", INFO_CODE(arg_info));
 		FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
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
 		if(FUNDEF_FUNBODY(arg_node)!=NULL){
 			FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
 		}
 		else{
 			fputs("   return\n", INFO_CODE(arg_info));
 		}
 		
 		INFO_SCOPE(arg_info) = INFO_SCOPE(arg_info) - 1;
 	}

 	if(FUNDEF_EXPORT(arg_node) == TRUE){
 		INFO_EXPORTFUN(arg_info)[INFO_EXPORTFUNCOUNT(arg_info)] = arg_node;
 		INFO_EXPORTFUNCOUNT(arg_info) = INFO_EXPORTFUNCOUNT(arg_info) + 1;
 	}
 	if(FUNDEF_EXTERN(arg_node) == TRUE){
 		INFO_IMPORTFUN(arg_info)[INFO_IMPORTFUNCOUNT(arg_info)] = arg_node;
 		INFO_IMPORTFUNCOUNT(arg_info) = INFO_IMPORTFUNCOUNT(arg_info) + 1;
 	}
 	DBUG_RETURN(arg_node);
 }

 node *GBCglobaldef( node *arg_node, info *arg_info){
 	DBUG_ENTER("GBCglobaldef");
 	GLOBALDEF_DIMS(arg_node) = TRAVopt(GLOBALDEF_DIMS(arg_node), arg_info);
 	
 	INFO_GLOBALVAR(arg_info)[INFO_GLOBALVARCOUNT(arg_info)] = arg_node;
 	INFO_GLOBALVARCOUNT(arg_info) = INFO_GLOBALVARCOUNT(arg_info) + 1;
 	
 	if(GLOBALDEF_EXPORT(arg_node) == TRUE){
 		INFO_EXPORTVAR(arg_info)[INFO_EXPORTVARCOUNT(arg_info)] = arg_node;
 		INFO_EXPORTVARCOUNT(arg_info) = INFO_EXPORTVARCOUNT(arg_info) + 1;
 	}
 	GLOBALDEF_INIT(arg_node) = TRAVopt(GLOBALDEF_INIT(arg_node), arg_info);
 	DBUG_RETURN(arg_node);
 }

 node *GBCglobaldec( node *arg_node, info *arg_info){
 	DBUG_ENTER("GBCglobaldec");
 	
 	GLOBALDEC_DIMS(arg_node) = TRAVopt(GLOBALDEC_DIMS(arg_node), arg_info);
 	INFO_IMPORTVAR(arg_info)[INFO_IMPORTVARCOUNT(arg_info)] = arg_node;
 	INFO_IMPORTVARCOUNT(arg_info) = INFO_IMPORTVARCOUNT(arg_info) + 1;
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
 	if(INFO_FUNDEFTYPE(arg_info) == T_unknown){
 		fputs("   return\n", INFO_CODE(arg_info));
 	}
 	else{
 		fputs("\n", INFO_CODE(arg_info));
 	}
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
 	CAST_EXPRESSION(arg_node) = TRAVdo(CAST_EXPRESSION(arg_node), arg_info);
 	if(CAST_TYPE(arg_node) == T_int){
 		fputs("   f2i\n", INFO_CODE(arg_info));
 	}
 	else{
 		fputs("   i2f\n", INFO_CODE(arg_info));
 	}
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
 	if(NODE_TYPE(STMTS_STMT(arg_node)) == N_return){
 		STMTS_STMT(arg_node) = TRAVdo(STMTS_STMT(arg_node), arg_info);
 	}
 	else{
 		STMTS_STMT(arg_node) = TRAVdo( STMTS_STMT(arg_node), arg_info);
 		STMTS_NEXT(arg_node) = TRAVopt(STMTS_NEXT(arg_node), arg_info);
 	}
 	
 	DBUG_RETURN(arg_node);
 }

//check vardec
 node *GBCvardec( node *arg_node, info *arg_info){
 	DBUG_ENTER("GBCvardec");
 	if(VARDEC_INIT(arg_node)!= NULL){
 		VARDEC_INIT(arg_node) = TRAVdo(VARDEC_INIT(arg_node), arg_info);
 	}
 	
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
 	if(FSYMBOL_EXTERN(FUNCALL_DECL(arg_node)) == TRUE){
 		int place = 0;
 		for(int i = 0; i < INFO_IMPORTFUNCOUNT(arg_info); i++){
 			if(STReq(FUNDEF_NAME(INFO_IMPORTFUN(arg_info)[i]), FUNCALL_NAME(arg_node))){
 				place = i;
 			}
 		}
 		sprintf(buffer, "%d\n", place);
 		command = STRcat("   jsre ", buffer);
 	}
 	else{
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
 	char *ass;
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
 		ass = STRcatn(3, "   ", type, "add\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_mul){
 		ass = STRcatn(3, "   ", type, "mul\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_sub){
 		ass = STRcatn(3, "   ", type, "sub\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_div){
 		ass = STRcatn(3, "   ", type, "div\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_mod){
 		ass = "   irem\n";
 	}
 	else if(BINOP_OP(arg_node) == BO_lt){
 		ass = STRcatn(3, "   ", type, "lt\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_le){
 		ass = STRcatn(3, "   ", type, "le\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_gt){
 		ass = STRcatn(3, "   ", type, "gt\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_ge){
 		ass = STRcatn(3, "   ", type, "ge\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_eq){
 		ass = STRcatn(3, "   ", type, "eq\n");
 	}
 	else if(BINOP_OP(arg_node) == BO_ne){
 		ass = STRcatn(3, "   ", type, "ne\n");
 	}
 	fputs(ass, INFO_CODE(arg_info));
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
 	int place = -1;
 	char buffer[5];
 	char buffer2 [5];
 	char *type;
 	if (SYMBOL_TYPE(VAR_DECL(arg_node)) == T_int){
 		type = "i";
 	}
 	else if(SYMBOL_TYPE(VAR_DECL(arg_node)) == T_float){
 		type = "f";
 	}
 	else{
 		type = "b";
 	}
 	if(SYMBOL_STATE(VAR_DECL(arg_node)) == place && SYMBOL_SCOPE(VAR_DECL(arg_node)) == 0 && !SYMBOL_EXTERN(VAR_DECL(arg_node))){
 		place = 0;
 		bool gevonden = FALSE;
 		while(!gevonden && place < INFO_GLOBALVARCOUNT(arg_info)){
 			node *globalvar = INFO_GLOBALVAR(arg_info)[place];
 			if(GLOBALDEF_NAME(globalvar) == VAR_NAME(arg_node)){
 				gevonden = TRUE;
 			}
 			else{
 				place ++;
 			}
 			
 		}
 		SYMBOL_STATE(VAR_DECL(arg_node)) = place;
 	}
 	else if(SYMBOL_STATE(VAR_DECL(arg_node)) == place && SYMBOL_EXTERN(VAR_DECL(arg_node))){
 		place = 0;
 		bool gevonden = FALSE;
 		while(!gevonden && place < INFO_IMPORTVARCOUNT(arg_info)){
 			node *importvar = INFO_IMPORTVAR(arg_info)[place];
 			if(GLOBALDEC_NAME(importvar) == VAR_NAME(arg_node)){
 				gevonden = TRUE;
 			}
 			else{
 				place ++;
 			}
 			
 		}
 		SYMBOL_STATE(VAR_DECL(arg_node)) = place;
 	}
 	else if(SYMBOL_STATE(VAR_DECL(arg_node)) == place && SYMBOL_SCOPE(VAR_DECL(arg_node)) == (INFO_SCOPE(arg_info) + 1)){
 		SYMBOL_STATE(VAR_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
 		INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
 	}

 	place = SYMBOL_STATE(VAR_DECL(arg_node));
 	if(SYMBOL_EXTERN(VAR_DECL(arg_node)) == TRUE){
 		sprintf(buffer, "%d", place);
 		char *string = STRcatn(3, "   ", type,"loade ");
 		char *command = STRcatn(3, string, buffer, "\n");
 		fputs(command, INFO_CODE(arg_info));
 	}
 	else if(SYMBOL_SCOPE(VAR_DECL(arg_node)) == 0){
 		sprintf(buffer, "%d", place);
 		char *string = STRcatn(3, "   ", type,"loadg ");
 		char *command = STRcatn(3, string, buffer, "\n");
 		fputs(command, INFO_CODE(arg_info));
 	}
 	else if(SYMBOL_SCOPE(VAR_DECL(arg_node)) == INFO_SCOPE(arg_info) + 1){

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
 	else{
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
 	int place = -1;
 	char buffer[5];
 	char buffer2 [5];
 	char *type;
 	if(SYMBOL_TYPE(VARLET_DECL(arg_node)) == T_int){
 		type = "i";
 	}
 	else if(SYMBOL_TYPE(VARLET_DECL(arg_node)) == T_float){
 		type = "f";
 	}
 	else{
 		type = "b";
 	}

 	if(SYMBOL_STATE(VARLET_DECL(arg_node)) == place && SYMBOL_SCOPE(VARLET_DECL(arg_node)) == 0){
 		
 		SYMBOL_STATE(VARLET_DECL(arg_node)) = INFO_GLOBALVARLETCOUNT(arg_info);
 		INFO_GLOBALVARLETCOUNT(arg_info) = INFO_GLOBALVARLETCOUNT(arg_info) + 1;
 	}
 	else if(SYMBOL_STATE(VARLET_DECL(arg_node)) == place && SYMBOL_SCOPE(VARLET_DECL(arg_node)) == (INFO_SCOPE(arg_info) + 1)){
 		SYMBOL_STATE(VARLET_DECL(arg_node)) = INFO_VARCOUNT(arg_info);
 		INFO_VARCOUNT(arg_info) = INFO_VARCOUNT(arg_info) + 1;
 	}
 	place = SYMBOL_STATE(VARLET_DECL(arg_node));
 	
 	if( SYMBOL_SCOPE(VARLET_DECL(arg_node)) == 0){
 		sprintf(buffer, "%d", place);
 		char *string = STRcatn(3, "   ", type, "storeg ");
 		char *command = STRcatn(3, string, buffer, "\n");
 		fputs(command, INFO_CODE(arg_info));
 	}
 	else if(SYMBOL_SCOPE(VARLET_DECL(arg_node)) == INFO_SCOPE(arg_info) + 1){
 		sprintf(buffer, "%d", place);
 		char *string = STRcatn(3, "   ", type, "store ");
 		char *command = STRcatn(3, string, buffer, "\n");
 		fputs(command, INFO_CODE(arg_info));
 	}
 	else{
 		sprintf(buffer, "%d", place);
 		sprintf(buffer2, "%d ", SYMBOL_SCOPE(VARLET_DECL(arg_node)));
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
 	if(FUNDEF_TYPE(FSYMBOL_FUNCTION(FUNCALL_DECL(EXPRSTMT_EXPR(arg_node)))) == T_int){
 		fputs("   ipop\n", INFO_CODE(arg_info));
 	}
 	else if(FUNDEF_TYPE(FSYMBOL_FUNCTION(FUNCALL_DECL(EXPRSTMT_EXPR(arg_node)))) == T_float){
 		fputs("   fpop\n", INFO_CODE(arg_info));
 	}
 	else if(FUNDEF_TYPE(FSYMBOL_FUNCTION(FUNCALL_DECL(EXPRSTMT_EXPR(arg_node)))) == T_boolean){
 		fputs("   bpop\n", INFO_CODE(arg_info));
 	}
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
 		sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info)-1);
 		command = STRcat(buffer, "_else:\n");
 		fputs(command, INFO_CODE(arg_info));
 		IF_ELSEBLOCK(arg_node) = TRAVdo(IF_ELSEBLOCK(arg_node), arg_info);
 		
 	}
 	else{
 		sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
 		command = STRcatn(3, "   branch_f ", buffer, "_end\n");
 		fputs(command, INFO_CODE(arg_info));
 		IF_IFBLOCK(arg_node) = TRAVdo(IF_IFBLOCK(arg_node), arg_info);
 	}
 	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
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
 	int step = 1;
 	char buffer2[20];
 	char buffer[20];
 	char *command;
 	bool neg = FALSE;
 	int plekEnd;
 	int plekStart;
 	node *stepnum;
 	if(FOR_STEP(arg_node) != NULL && NODE_TYPE(FOR_STEP(arg_node)) == N_num){
 		step = NUM_VALUE(FOR_STEP(arg_node));
 		stepnum = FOR_STEP(arg_node);
 	}
 	else if (FOR_STEP(arg_node) != NULL && NODE_TYPE(FOR_STEP(arg_node)) == N_monop){
 		if(MONOP_OP(FOR_STEP(arg_node)) == MO_neg && NODE_TYPE(MONOP_OPERAND(FOR_STEP(arg_node))) == N_num){
 			step = -NUM_VALUE(MONOP_OPERAND(FOR_STEP(arg_node)));
 			stepnum = MONOP_OPERAND(FOR_STEP(arg_node));
 			neg = TRUE;
 		}
 	}
 	
 	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
 	sprintf(buffer, "%d", INFO_BRANCHCOUNT(arg_info));
 	char *commandfor = STRcat(buffer, "_for");
 	if(!INFO_INFOR(arg_info)){
 		command = STRcatn(3, "   jump ", commandfor, "\n");
 		fputs(command, INFO_CODE(arg_info));
 	}
 	command = STRcat(commandfor, ":\n");
 	fputs(command, INFO_CODE(arg_info));
 	FOR_START(arg_node) = TRAVdo(FOR_START(arg_node), arg_info);
 	plekStart = SYMBOL_STATE(VAR_DECL(FOR_START(arg_node)));
 	FOR_STOP(arg_node) = TRAVdo(FOR_STOP(arg_node), arg_info);
 	if(neg){
 		fputs("   igt\n", INFO_CODE(arg_info));
 	}
 	else{
 		fputs("   ilt\n", INFO_CODE(arg_info));
 	}
 	
 	INFO_BRANCHCOUNT(arg_info) = INFO_BRANCHCOUNT(arg_info) + 1;
 	plekEnd = INFO_BRANCHCOUNT(arg_info);
 	sprintf(buffer, "%d", plekEnd);
 	command = STRcatn(3, "   branch_f ", buffer, "_end\n");
 	fputs(command, INFO_CODE(arg_info));
 	if(FOR_BLOCK(arg_node) != NULL && NODE_TYPE(STMTS_STMT(FOR_BLOCK(arg_node))) == N_for){
 		sprintf(buffer, "%d_for\n", INFO_BRANCHCOUNT(arg_info) + 1);
 		command = STRcat("   jump ", buffer);
 		fputs(command, INFO_CODE(arg_info));
 	}
 	INFO_INFOR(arg_info) = TRUE;
 	FOR_BLOCK(arg_node) = TRAVopt(FOR_BLOCK(arg_node), arg_info);
 	FOR_BLOCKSINGLE(arg_node) = TRAVopt(FOR_BLOCKSINGLE(arg_node), arg_info);
 	INFO_INFOR(arg_info) = FALSE;
 	if(step == 1){
 		sprintf(buffer, "%d\n", plekStart);
 		command = STRcat("   iinc_1 ", buffer);
 	}
 	else if( step == -1){
 		sprintf(buffer, "%d\n", plekStart);
 		command = STRcat("   idec_1 ", buffer);
 	}
 	else if(step > 1 || step < -1){
 		
 		if(INFO_CONSTCOUNT(arg_info) == 0){
 			sprintf(buffer, "%d ", plekStart);
 			if(step < -1){
 				command = STRcatn(3, "   idec ", buffer, "0\n");
 			}
 			else{
 				command = STRcatn(3, "   iinc ", buffer, "0\n");
 			}
 			INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = TBmakeNum(step);
 			INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
 		}
 		else{
 			sprintf(buffer, "%d ", plekStart);
 			int value;
 			if(step < -1){
 				value = step * -1;
 			}
 			else{
 				value = step;
 			}
 			int plek = 0;
 			bool gevonden = FALSE;
 			while(plek < INFO_CONSTCOUNT(arg_info) && !gevonden){
 				if(NODE_TYPE(INFO_CONSTS(arg_info)[plek]) == N_num){
 					if(NUM_VALUE(INFO_CONSTS(arg_info)[plek]) == value){
 						gevonden = TRUE;
 						sprintf(buffer2, " %d\n", plek);
 					}
 					else{
 						plek++;
 					}
 				}
 				else{
 					plek++;
 				}
 				
 			}
 			
 			if(!gevonden){
 				sprintf(buffer2, " %d\n", INFO_CONSTCOUNT(arg_info));
 				INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = stepnum;
 				INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
 			}

 			if(step < 0){
 				command  = STRcatn(3,"   idec ", buffer, buffer2);
 			}
 			else{
 				command  = STRcatn(3,"   iinc ", buffer, buffer2);
 			}
 			
 			
 		}
 		
 	}
 	fputs(command, INFO_CODE(arg_info));
 	command = STRcatn(3,"   jump ", commandfor, "\n");
 	fputs(command, INFO_CODE(arg_info));
 	sprintf(buffer, "%d", plekEnd);
 	command = STRcat(buffer, "_end: \n");
 	fputs(command, INFO_CODE(arg_info));
 	

 	
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
 			bool gevonden = FALSE;
 			char buffer[5];
 			while(plek < INFO_CONSTCOUNT(arg_info) && !gevonden){
 				if(NODE_TYPE(INFO_CONSTS(arg_info)[plek]) == N_num){
 					if(NUM_VALUE(INFO_CONSTS(arg_info)[plek]) == value){
 						gevonden = TRUE;
 						sprintf(buffer, "%d", plek);
 					}
 					else{
 						plek++;
 					}
 				}
 				else{
 					plek++;
 				}
 				
 			}
 			
 			if(!gevonden){
 				sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));

 				INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
 				INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
 			}
 			char *command  = STRcatn(3,"   iloadc ", buffer, "\n");
 			fputs(command, INFO_CODE(arg_info));
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
 			float value = FLOAT_VALUE(arg_node);
 			int plek = 0;
 			bool gevonden = FALSE;
 			char buffer[10];
 			while(plek < INFO_CONSTCOUNT(arg_info) && !gevonden){
 				if(NODE_TYPE(INFO_CONSTS(arg_info)[plek]) == N_float){
 					if(FLOAT_VALUE(INFO_CONSTS(arg_info)[plek]) == value){
 						gevonden = TRUE;
 						sprintf(buffer, "%d", plek);
 					}
 					else{
 						plek++;
 					}
 				}
 				else{
 					plek++;
 				}
 				
 			}
 			
 			if(!gevonden){
 				sprintf(buffer, "%d", INFO_CONSTCOUNT(arg_info));
 				INFO_CONSTS(arg_info)[INFO_CONSTCOUNT(arg_info)] = arg_node;
 				INFO_CONSTCOUNT(arg_info) = INFO_CONSTCOUNT(arg_info) + 1;
 			}
 			char *command  = STRcatn(3,"   floadc ", buffer, "\n");
 			fputs(command, INFO_CODE(arg_info));
 			
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
 	arg_info = MakeInfo();

  TRAVpush( TR_gbc);   // Push traversal "cbg" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  arg_info = FreeInfo(arg_info);

  DBUG_RETURN( syntaxtree);

}

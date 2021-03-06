/*
	Typechecker traversal for checking types and rewriting binop and cast(milestone 7,9 and 10)
	@author Carly Hill 10523162
*/

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
		int lastType;
		int funReturnType;
		int hasReturn;
	};

#define INFO_TYPE(n)((n)->lastType)
#define INFO_FUNTYPE(n)((n)->funReturnType)
#define INFO_HASRETURN(n)((n)->hasReturn)

	static info *MakeInfo(void)
	{
		info *result;

		DBUG_ENTER( "MakeInfo");

		result = (info *)MEMmalloc(sizeof(info));

		INFO_TYPE( result) = 0;
		INFO_FUNTYPE( result) =0;
		INFO_HASRETURN( result) =0;


		DBUG_RETURN( result);
	}

	static info *FreeInfo( info *info)
	{
		DBUG_ENTER ("FreeInfo");

		info = MEMfree( info);

		DBUG_RETURN( info);
	}

//traverse over the declarations of the program
	node *CTprogram(node *arg_node, info *arg_info){
		DBUG_ENTER("CTprogram");
		PROGRAM_DECLARATIONS(arg_node) =  TRAVdo(PROGRAM_DECLARATIONS( arg_node), arg_info);
		DBUG_RETURN(arg_node);
	}

//check parametertypes of funcall and give type of function to info_type
	node *CTfuncall(node *arg_node, info *arg_info){
		DBUG_ENTER("CTfuncall");

	//check parameter types, if there are any
		if(FUNCALL_ARGS(arg_node)!=NULL){
			node *args = FUNCALL_ARGS(arg_node);
		//check param type against expression type
			node * param = FUNDEF_PARAMS(FSYMBOL_FUNCTION(FUNCALL_DECL(arg_node)));
			EXPRS_EXPRS(args) = TRAVdo(EXPRS_EXPRS(args), arg_info);
			type exprtype = INFO_TYPE(arg_info);
			type paramtype = PARAM_TYPE(param);
			if(exprtype != paramtype){
				CTIerrorLine(NODE_LINE(arg_node), "argument type does not match function definition");
			}

		//keep checking till there are no parameters left
			while(EXPRS_NEXT(args)!=NULL){
				args = EXPRS_NEXT(args);
				param = PARAM_NEXT(param);
				EXPRS_EXPRS(args) = TRAVdo(EXPRS_EXPRS(args), arg_info);
				exprtype = INFO_TYPE(arg_info);
				paramtype = PARAM_TYPE(param);
				if(exprtype != paramtype){
					CTIerrorLine(NODE_LINE(arg_node), "argument type does not match function definition");
				}
			}
		}

	//set info_type to return type of the function
		INFO_TYPE(arg_info) = FUNDEF_TYPE(FSYMBOL_FUNCTION(FUNCALL_DECL(arg_node)));

		DBUG_RETURN(arg_node);
	}

	//check type of return of function against function type
	node *CTfundef(node *arg_node, info *arg_info){
		DBUG_ENTER("CTfundef");
		INFO_HASRETURN(arg_info) = 0;
		INFO_FUNTYPE(arg_info) = 999;

		FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);

		if(INFO_HASRETURN(arg_info) == 0){
			INFO_FUNTYPE(arg_info) = T_unknown;
		}
		if(FUNDEF_TYPE(arg_node) != INFO_FUNTYPE(arg_info) && FUNDEF_EXTERN(arg_node) == FALSE){
			CTIerrorLine(NODE_LINE(arg_node), "Return type does not match function type fun: %d ret:  %d", FUNDEF_TYPE(arg_node), INFO_TYPE(arg_info));
		}
		DBUG_RETURN(arg_node);
	}

	node *CTfunbody(node *arg_node, info *arg_info){
		DBUG_ENTER("CTfunbody");
		FUNBODY_VARDEC(arg_node) = TRAVopt(FUNBODY_VARDEC(arg_node), arg_info);
		FUNBODY_LOCALFUNDEFS(arg_node) = TRAVopt(FUNBODY_LOCALFUNDEFS(arg_node), arg_info);
		FUNBODY_STATEMENT(arg_node) = TRAVopt(FUNBODY_STATEMENT(arg_node), arg_info);
		DBUG_RETURN(arg_node);
	}

	node *CTfor(node *arg_node, info *arg_info){
		DBUG_ENTER("CTfor");

		FOR_START(arg_node) = TRAVdo(FOR_START(arg_node), arg_info);
		if (INFO_TYPE(arg_info) != T_int){
			CTIerrorLine(NODE_LINE(arg_node), "Start type does not match int");
		}
		FOR_STOP(arg_node) = TRAVdo(FOR_STOP(arg_node), arg_info);
		if(INFO_TYPE(arg_info) != T_int){
			CTIerrorLine(NODE_LINE(arg_node), "Stop type does not match int");
		}
		if(FOR_STEP(arg_node) != NULL){
			FOR_STEP(arg_node) = TRAVdo(FOR_STEP(arg_node), arg_info);
			if(INFO_TYPE(arg_info) != T_int){
				CTIerrorLine(NODE_LINE(arg_node), "Step type does not match int");
			}
		}

		if(FOR_BLOCK(arg_node) != NULL){
			FOR_BLOCK(arg_node) = TRAVdo(FOR_BLOCK(arg_node), arg_info);
		} else if (FOR_BLOCKSINGLE(arg_node) != NULL){
			FOR_BLOCKSINGLE(arg_node) = TRAVdo(FOR_BLOCKSINGLE(arg_node), arg_info);
		}

		DBUG_RETURN(arg_node);

	}

//set info_type to type of varlet
	node *CTvarlet(node *arg_node, info *arg_info){
		DBUG_ENTER("CTvarlet");
		
		INFO_TYPE(arg_info) = SYMBOL_TYPE(VARLET_DECL(arg_node));

		DBUG_RETURN(arg_node);
	}

//check vardec type with initialisation
	node *CTvardec(node *arg_node, info *arg_info){
		DBUG_ENTER("CTvardec");

	//only check if there is a initialisation
		if(VARDEC_INIT(arg_node)!= NULL){
			VARDEC_INIT(arg_node) = TRAVdo(VARDEC_INIT(arg_node), arg_info);
			type vartype = INFO_TYPE(arg_info);
			if(vartype != VARDEC_TYPE(arg_node)){
				CTIerrorLine(NODE_LINE(arg_node), "Initialisation value does not match the type of the declared variable");
			}
		}
	//ga verder met traversal
		VARDEC_NEXT(arg_node) = TRAVopt(VARDEC_NEXT(arg_node), arg_info);

		DBUG_RETURN(arg_node);
	}

//check type assign
	node *CTassign(node *arg_node, info *arg_info){
		DBUG_ENTER("CTassign");

	//compare varlet type with assignent expression type
		ASSIGN_LET(arg_node) = TRAVdo(ASSIGN_LET(arg_node), arg_info);
		type vartype = INFO_TYPE(arg_info);
		ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
		type exprtype = INFO_TYPE(arg_info);
		if(vartype != exprtype){
			CTIerrorLine(NODE_LINE(arg_node), "The expression type of the assign does not match the variable type");
		}

		DBUG_RETURN(arg_node);
	}

//set info_type to var type
	node *CTvar(node *arg_node, info *arg_info){
		DBUG_ENTER("CTvar");

		INFO_TYPE(arg_info) = SYMBOL_TYPE(VAR_DECL(arg_node));

		DBUG_RETURN(arg_node);
	}

//rewrite cast and set info_type to cast type
	node *CTcast(node *arg_node, info *arg_info){
		DBUG_ENTER("CTcast");
		extern node *CTbinop( node *arg_node, info *arg_info);
		extern node *CTfunbody( node *arg_node, info *arg_info);

		CAST_EXPRESSION(arg_node) = TRAVdo(CAST_EXPRESSION(arg_node), arg_info);
		type exprType = INFO_TYPE(arg_info);
		type castType = CAST_TYPE(arg_node);

	//set info type to cast type
		INFO_TYPE(arg_info) = CAST_TYPE(arg_node);

	//rewrite cast
		if(exprType == T_boolean && castType == T_int){
			node *expr = CAST_EXPRESSION(arg_node);
			node *then = TBmakeNum(1);
			node *other = TBmakeNum(0);
			node *condexpr = TBmakeConditionexpr(expr, other, then);
			arg_node = condexpr;
		}
		else if(exprType == T_boolean && castType == T_float){
			node *expr = CAST_EXPRESSION(arg_node);
			node *then = TBmakeFloat(1.0);
			node *other = TBmakeFloat(0.0);
			node *condexpr = TBmakeConditionexpr(expr, then, other);
			arg_node = condexpr;
		}
		else if(exprType == T_int && castType == T_boolean){
			node *expr = TBmakeBinop(BO_gt, CAST_EXPRESSION(arg_node), TBmakeNum(0));
			BINOP_OPTYPE(expr) = T_int;
			node *then = TBmakeBool(true);
			node *other = TBmakeBool(false);
			node *condexpr = TBmakeConditionexpr(expr, other, then);
			arg_node = condexpr;
		}
		else if(exprType == T_float && castType == T_boolean){
			node *expr = TBmakeBinop(BO_gt, CAST_EXPRESSION(arg_node), TBmakeFloat(0.0));
			BINOP_OPTYPE(expr) = T_float;
			node *then = TBmakeBool(true);
			node *other = TBmakeBool(false);
			node *condexpr = TBmakeConditionexpr(expr, other, then);
			arg_node = condexpr;
		}

		DBUG_RETURN(arg_node);
	}

//check types of operands of binop and rewrite binop if neccessary
	node * CTbinop(node *arg_node, info *arg_info){
		DBUG_ENTER("CTbinop");
		node *leftexpr = BINOP_LEFT(arg_node);
		node *rightexpr = BINOP_RIGHT(arg_node);
		
	//compare types of operands
		BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
		type typeleft = INFO_TYPE(arg_info);
		BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
		type typeright = INFO_TYPE(arg_info);
		if(typeleft != typeright){
			CTIerrorLine(NODE_LINE(arg_node), "Types of left and right expressions of the binop do not match");
		}

	//check if the right type of operands are used with the right operators
		if((BINOP_OP(arg_node) == BO_and || BINOP_OP(arg_node) == BO_or)&&INFO_TYPE(arg_info)!=T_boolean){
			CTIerrorLine(NODE_LINE(arg_node), "The used &&(and) or ||(or) operator can only compare two booleans");
		}
		if((BINOP_OP(arg_node) == BO_lt || BINOP_OP(arg_node) == BO_le ||BINOP_OP(arg_node) == BO_gt || BINOP_OP(arg_node) == BO_ge) 
			&& INFO_TYPE(arg_info) == T_boolean){
			CTIerrorLine(NODE_LINE(arg_node), "The used operator can only compare two integers or floats");
	}
	if(BINOP_OP(arg_node) == BO_add ||BINOP_OP(arg_node) == BO_mul ||BINOP_OP(arg_node) == BO_sub ||BINOP_OP(arg_node) == BO_div ||
		BINOP_OP(arg_node) == BO_mod ){
		BINOP_OPTYPE(arg_node) = typeleft;
}

	//set info_type to boolean
if(BINOP_OP(arg_node) == BO_lt || BINOP_OP(arg_node) == BO_le ||BINOP_OP(arg_node) == BO_gt || BINOP_OP(arg_node) == BO_ge ||
	BINOP_OP(arg_node) == BO_eq || BINOP_OP(arg_node) == BO_ne || BINOP_OP(arg_node) == BO_and || BINOP_OP(arg_node) == BO_or){
	INFO_TYPE(arg_info) = T_boolean;
BINOP_OPTYPE(arg_node) = typeleft;
}
else{
	BINOP_OPTYPE(arg_node) = typeleft;
}

	//rewrite and
if(BINOP_OP(arg_node)==BO_and){

	node *then = TBmakeBool(0);
	arg_node = TBmakeConditionexpr(leftexpr, then, rightexpr);
}

  	//rewrite or
else if(BINOP_OP(arg_node) == BO_or){
	node *orthen = TBmakeBool(1);
	arg_node = TBmakeConditionexpr(leftexpr, rightexpr, orthen);
}
DBUG_RETURN(arg_node);
}

//check type of monop with operand
node *CTmonop(node *arg_node, info *arg_info){
	DBUG_ENTER("CTmonop");

	//get type of operand in info_type
	MONOP_OPERAND(arg_node) = TRAVdo(MONOP_OPERAND(arg_node), arg_info);
	

	//check if type is boolean.

	if(MONOP_OP(arg_node) == MO_not && INFO_TYPE(arg_info) != T_boolean){
		CTIerrorLine(NODE_LINE(arg_node), "!(not) can only be used with a boolean operand");
	}
	else{
		MONOP_OPTYPE(arg_node) = T_boolean;
	}
	if(MONOP_OP(arg_node) == MO_neg && INFO_TYPE(arg_info) == T_boolean){
		CTIerrorLine(NODE_LINE(arg_node), "-(neg) can only be used with a boolean operand");
	}
	else if(INFO_TYPE(arg_info) == T_int){
		MONOP_OPTYPE(arg_node) = T_int;
	}
	else{
		MONOP_OPTYPE(arg_node) = T_float;
	}

	DBUG_RETURN(arg_node);
}

//set info_type to type of return expression
node * CTreturn(node *arg_node, info *arg_info){
	DBUG_ENTER("CTreturn");

	// confirm fun has return
	INFO_HASRETURN(arg_info) = 1;

	if(RETURN_EXPRESSION(arg_node) == NULL){
		INFO_FUNTYPE(arg_info) = T_unknown;
		RETURN_TYPE(arg_node) = T_unknown;
	}
	else{
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
		RETURN_TYPE(arg_node) = INFO_TYPE(arg_info);
		INFO_FUNTYPE(arg_info) = INFO_TYPE(arg_info);
	}

	DBUG_RETURN(arg_node);
}

//set info_type to int
node *CTnum(node *arg_node, info *arg_info){
	DBUG_ENTER("CTNum");
	INFO_TYPE(arg_info) = T_int;
	DBUG_RETURN(arg_node);
}

//set info_type to boolean
node *CTbool(node *arg_node, info *arg_info){
	DBUG_ENTER("CTBool");
	INFO_TYPE(arg_info) = T_boolean;
	DBUG_RETURN(arg_node);
}

//set info_type to float
node *CTfloat(node *arg_node, info *arg_info){
	DBUG_ENTER("CTFloat");
	INFO_TYPE(arg_info) = T_float;

	DBUG_RETURN(arg_node);
}

//start traversal
node *CTchecktypes( node *syntaxtree){
	DBUG_ENTER("CTchecktypes");

	info *arg_info;

  TRAVpush( TR_ct);   // Push traversal "link" as defined in ast.xml
  arg_info = MakeInfo();
  syntaxtree = TRAVdo( syntaxtree, arg_info);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal
  arg_info = FreeInfo(arg_info);
  
  DBUG_RETURN( syntaxtree);
}
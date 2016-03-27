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
  type lastType;
};

#define INFO_TYPE(n)((n)->lastType)

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

//traverse over de declaraties van het progamma
node *CTprogram(node *arg_node, info *arg_info){
	DBUG_ENTER("CTprogram");
	PROGRAM_DECLARATIONS(arg_node) =  TRAVdo(PROGRAM_DECLARATIONS( arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

//check parametertypes van funcall en geef type van functie mee
node *CTfuncall(node *arg_node, info *arg_info){
	DBUG_ENTER("CTfuncall");

	//check parameter types, als er parameters zijn
	if(FUNCALL_ARGS(arg_node)!=NULL){
		node *args = FUNCALL_ARGS(arg_node);
		node * param = FUNDEF_PARAMS(FSYMBOL_FUNCTION(FUNCALL_DECL(arg_node)));
		EXPRS_EXPRS(args) = TRAVdo(EXPRS_EXPRS(args), arg_info);
		type exprtype = INFO_TYPE(arg_info);
		type paramtype = PARAM_TYPE(param);
		if(exprtype != paramtype){
			CTIerrorLine(NODE_LINE(arg_node), "argumenttype matcht niet met functiedefinitie");
		}


		while(EXPRS_NEXT(args)!=NULL){
			args = EXPRS_NEXT(args);
			param = PARAM_NEXT(param);
			EXPRS_EXPRS(args) = TRAVdo(EXPRS_EXPRS(args), arg_info);
			exprtype = INFO_TYPE(arg_info);
			paramtype = PARAM_TYPE(param);
			if(exprtype != paramtype){
				CTIerrorLine(NODE_LINE(arg_node), "argumenttype matcht niet met functiedefinitie");
			}
		}
	}

	//geef type van aangeroepen functie mee aan info_type
	INFO_TYPE(arg_info) = FUNDEF_TYPE(FSYMBOL_FUNCTION(FUNCALL_DECL(arg_node)));

	DBUG_RETURN(arg_node);
}

//check het type van de return van de functie
node *CTfundef(node *arg_node, info *arg_info){
	DBUG_ENTER("CTfundef");

	FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
	if(INFO_TYPE(arg_info)!=FUNDEF_TYPE(arg_node)){
		CTIerrorLine(NODE_LINE(arg_node), "Returntype is niet hetzelfde als functietype");
	}

	DBUG_RETURN(arg_node);
}

//geef type van varlet mee aan info_type
node *CTvarlet(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvarlet");
	
	INFO_TYPE(arg_info) = SYMBOL_TYPE(VARLET_DECL(arg_node));

	DBUG_RETURN(arg_node);
}

//check vardec type met de initialisatie
node *CTvardec(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvardec");

	//check als er een initialisatie is
	if(VARDEC_INIT(arg_node)!= NULL){
		VARDEC_INIT(arg_node) = TRAVdo(VARDEC_INIT(arg_node), arg_info);
		type vartype = INFO_TYPE(arg_info);
		if(vartype != VARDEC_TYPE(arg_node)){
			CTIerrorLine(NODE_LINE(arg_node), "Type variabele klopt niet");
		}
	}
	//ga verder met traversal
	VARDEC_NEXT(arg_node) = TRAVopt(VARDEC_NEXT(arg_node), arg_info);

	DBUG_RETURN(arg_node);
}

//check het type van de assign
node *CTassign(node *arg_node, info *arg_info){
	DBUG_ENTER("CTassign");

	//vergelijk het type van de varlet met het type van de expression na de =
	ASSIGN_LET(arg_node) = TRAVdo(ASSIGN_LET(arg_node), arg_info);
	type vartype = INFO_TYPE(arg_info);
	ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
	type exprtype = INFO_TYPE(arg_info);
	if(vartype != exprtype){
		CTIerrorLine(NODE_LINE(arg_node), "De expressie van de assign geeft het verkeerde type");
	}

	DBUG_RETURN(arg_node);
}

//geef het type van de var mee aan de info_type
node *CTvar(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvar");

	INFO_TYPE(arg_info) = SYMBOL_TYPE(VAR_DECL(arg_node));

	DBUG_RETURN(arg_node);
}

//geef het type van de cast mee aan de info_type
node *CTcast(node *arg_node, info *arg_info){
	DBUG_ENTER("CTcast");
	CAST_EXPRESSION(arg_node) = TRAVdo(CAST_EXPRESSION(arg_node), arg_info);
	type exprType = INFO_TYPE(arg_info);
	type castType = CAST_TYPE(arg_node);
	INFO_TYPE(arg_info) = CAST_TYPE(arg_node);
	if(exprType == T_boolean && castType == T_int){
		node *expr = CAST_EXPRESSION(arg_node);
		node *then = TBmakeNum(1);
		node *other = TBmakeNum(0);
		node *condexpr = TBmakeConditionexpr(expr, then, other);
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
		node *then = TBmakeBool(true);
		node *other = TBmakeBool(false);
		node *condexpr = TBmakeConditionexpr(expr, then, other);
		arg_node = condexpr;
	}
	else if(exprType == T_float && castType == T_boolean){
		node *expr = TBmakeBinop(BO_gt, CAST_EXPRESSION(arg_node), TBmakeFloat(0.0));
		node *then = TBmakeBool(true);
		node *other = TBmakeBool(false);
		node *condexpr = TBmakeConditionexpr(expr, then, other);
		arg_node = condexpr;
	}

	DBUG_RETURN(arg_node);
}

//check de types van de operanden van de binop
node * CTbinop(node *arg_node, info *arg_info){
	DBUG_ENTER("CTbinop");

	//vergelijk type van linker en rechter operanden van de binop
	BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
	type typeleft = INFO_TYPE(arg_info);
	BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
	type typeright = INFO_TYPE(arg_info);
	if(typeleft != typeright){
		CTIerrorLine(NODE_LINE(arg_node), "De types van de linker en rechter expressie van de binaire operator matchen niet");
	}

	//controleer of de juiste type operanden met de juiste operators gebruikt worden
	if((BINOP_OP(arg_node) == BO_and || BINOP_OP(arg_node) == BO_or)&&INFO_TYPE(arg_info)!=T_boolean){
		CTIerrorLine(NODE_LINE(arg_node), "De gebruikte &&(and) of ||(or) operator kan alleen twee booleans vergelijken");
	}
	if((BINOP_OP(arg_node) == BO_lt || BINOP_OP(arg_node) == BO_le ||BINOP_OP(arg_node) == BO_gt || BINOP_OP(arg_node) == BO_ge) 
		&& INFO_TYPE(arg_info) == T_boolean){
		CTIerrorLine(NODE_LINE(arg_node), "De gebruikte operator kan alleen twee ints of twee floats vergelijken");
	}

	//geef het juiste type mee aan de info_type
	if(BINOP_OP(arg_node) == BO_lt || BINOP_OP(arg_node) == BO_le ||BINOP_OP(arg_node) == BO_gt || BINOP_OP(arg_node) == BO_ge ||
		BINOP_OP(arg_node) == BO_eq || BINOP_OP(arg_node) == BO_ne || BINOP_OP(arg_node) == BO_and || BINOP_OP(arg_node) == BO_or){
		INFO_TYPE(arg_info) = T_boolean;
	}

	DBUG_RETURN(arg_node);
}

//check type van monop met operand
node *CTmonop(node *arg_node, info *arg_info){
	DBUG_ENTER("CTmonop");

	MONOP_OPERAND(arg_node) = TRAVdo(MONOP_OPERAND(arg_node), arg_info);
	//info_type is nu gevuld door operand van de monop

	//controleren of het type met de operator gebruikt kan worden

	if(MONOP_OP(arg_node) ==MO_not && INFO_TYPE(arg_info) != T_boolean){
		CTIerrorLine(NODE_LINE(arg_node), "!(not) kan alleen maar met een boolean operand gebruikt worden");
	}
	if(MONOP_OP(arg_node) == MO_neg && INFO_TYPE(arg_info) == T_boolean){
		CTIerrorLine(NODE_LINE(arg_node), "-(neg) kan niet met een boolean operand gebruikt worden");
	}

	DBUG_RETURN(arg_node);
}

//geef type van return expression terug
node * CTreturn(node *arg_node, info *arg_info){
	DBUG_ENTER("CTreturn");

	if(RETURN_EXPRESSION(arg_node) == NULL){
		INFO_TYPE(arg_info) = T_unknown;
	}
	else{
		RETURN_EXPRESSION(arg_node) = TRAVdo(RETURN_EXPRESSION(arg_node), arg_info);
	}

	DBUG_RETURN(arg_node);
}

//geef type van int mee aan de info_type
node *CTnum(node *arg_node, info *arg_info){
	DBUG_ENTER("CTNum");

	INFO_TYPE(arg_info) = T_int;

	DBUG_RETURN(arg_node);
}

//geef type van bool mee aan de info_type
node *CTbool(node *arg_node, info *arg_info){
	DBUG_ENTER("CTBool");

	INFO_TYPE(arg_info) = T_boolean;

	DBUG_RETURN(arg_node);
}

//geef type van float mee aan de info_type
node *CTfloat(node *arg_node, info *arg_info){
	DBUG_ENTER("CTFloat");

	INFO_TYPE(arg_info) = T_float;

	DBUG_RETURN(arg_node);
}

//start de traversal
node *CTchecktypes( node *syntaxtree){
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
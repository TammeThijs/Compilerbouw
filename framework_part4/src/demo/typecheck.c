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
node *CTprogram(node *arg_node, info *arg_info){
	DBUG_ENTER("CTprogram");
	PROGRAM_DECLARATIONS(arg_node) =  TRAVdo(PROGRAM_DECLARATIONS( arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *CTfuncall(node *arg_node, info *arg_info){
	DBUG_ENTER("CTfuncall");
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
	INFO_TYPE(arg_info) = FUNDEF_TYPE(FSYMBOL_FUNCTION(FUNCALL_DECL(arg_node)));
	DBUG_RETURN(arg_node);
}

node *CTfundef(node *arg_node, info *arg_info){
	DBUG_ENTER("CTfundef");
	FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
	if(INFO_TYPE(arg_info)!=FUNDEF_TYPE(arg_node)){
		CTIerrorLine(NODE_LINE(arg_node), "Returntype is niet hetzelfde als functietype");
	}
	DBUG_RETURN(arg_node);
}
node *CTvarlet(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvarlet");
	
	INFO_TYPE(arg_info) = SYMBOL_TYPE(VARLET_DECL(arg_node));
	DBUG_RETURN(arg_node);
}

node *CTvardec(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvardec");
	if(VARDEC_INIT(arg_node)!= NULL){
		VARDEC_INIT(arg_node) = TRAVdo(VARDEC_INIT(arg_node), arg_info);
		type vartype = INFO_TYPE(arg_info);
		if(vartype == T_int){
			printf("vartype is int\n");
		}
		if(vartype != VARDEC_TYPE(arg_node)){
			CTIerrorLine(NODE_LINE(arg_node), "Type variabele klopt niet");
		}
	}
	VARDEC_NEXT(arg_node) = TRAVopt(VARDEC_NEXT(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

node *CTassign(node *arg_node, info *arg_info){
	DBUG_ENTER("CTassign");
	printf("in de assign node");

	ASSIGN_LET(arg_node) = TRAVdo(ASSIGN_LET(arg_node), arg_info);
	type vartype = INFO_TYPE(arg_info);
	ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
	type exprtype = INFO_TYPE(arg_info);
	if(vartype != exprtype){
		CTIerrorLine(NODE_LINE(arg_node), "De expressie van de assign geeft het verkeerde type");
	}
	DBUG_RETURN(arg_node);
}
node *CTvar(node *arg_node, info *arg_info){
	DBUG_ENTER("CTvar");
	INFO_TYPE(arg_info) = SYMBOL_TYPE(VAR_DECL(arg_node));
	DBUG_RETURN(arg_node);
}

node *CTcast(node *arg_node, info *arg_info){
	DBUG_ENTER("CTcast");
	INFO_TYPE(arg_info) = CAST_TYPE(arg_node);
	DBUG_RETURN(arg_node);
}

node * CTbinop(node *arg_node, info *arg_info){
	DBUG_ENTER("CTbinop");
	BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
	type typeleft = INFO_TYPE(arg_info);
	BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
	type typeright = INFO_TYPE(arg_info);
	if(typeleft != typeright){
		CTIerrorLine(NODE_LINE(arg_node), "De types van de linker en rechter expressie van de binaire operator matchen niet");
	}
	DBUG_RETURN(arg_node);
}

node *CTmonop(node *arg_node, info *arg_info){
	DBUG_ENTER("CTmonop");
	MONOP_OPERAND(arg_node) = TRAVdo(MONOP_OPERAND(arg_node), arg_info);
	DBUG_RETURN(arg_node);
}

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

node *CTnum(node *arg_node, info *arg_info){
	DBUG_ENTER("CTNum");
	INFO_TYPE(arg_info) = T_int;
	printf("int toegevoegd\n");
	DBUG_RETURN(arg_node);
}

node *CTbool(node *arg_node, info *arg_info){
	DBUG_ENTER("CTBool");
	INFO_TYPE(arg_info) = T_boolean;
	printf("boolean toegevoegd\n");
	DBUG_RETURN(arg_node);
}

node *CTfloat(node *arg_node, info *arg_info){
	DBUG_ENTER("CTFloat");
	INFO_TYPE(arg_info) = T_float;
	printf("float toegevoegd\n");
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
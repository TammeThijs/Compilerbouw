
/**
 * @file print.c
 *
 * Functions needed by print traversal.
 *
 */

/**
 * @defgroup print Print Functions.
 *
 * Functions needed by print traversal.
 *
 * @{
 */


#include "print.h"
#include "traverse.h"
#include "tree_basic.h"
#include "dbug.h"
#include "memory.h"
#include "globals.h"

/*
 * INFO structure
 */
struct INFO {
  bool firsterror;
  int count;
};

#define INFO_FIRSTERROR(n) ((n)->firsterror)
#define INFO_COUNT(n) ((n)->count)


static info *MakeInfo()
{
  info *result;

  result = MEMmalloc(sizeof(info));
  INFO_COUNT( result) = 0;

    

  INFO_FIRSTERROR(result) = FALSE;
  
  return result;
}


static info *FreeInfo( info *info)
{
  info = MEMfree( info);

  return info;
}

/** <!--******************************************************************-->
 *
 * @fn PRTprogram
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/


node *
PRTsymbol (node * arg_node, info * arg_info)
{
  char *tmp;

  DBUG_ENTER ("PRTsymbol");

  switch(SYMBOL_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      DBUG_ASSERT( 0, "unknown type detected!");
  }

  printf("|   %s   |   %s   |   %d   |\n", tmp, SYMBOL_NAME(arg_node), SYMBOL_STATE(arg_node));

  SYMBOL_NEXT(arg_node) = TRAVopt(SYMBOL_NEXT(arg_node), arg_info);

  DBUG_RETURN (arg_node);
}


node *
PRTprogram (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTprogram");
  PROGRAM_DECLARATIONS(arg_node) = TRAVdo(PROGRAM_DECLARATIONS(arg_node), arg_info);
  if(PROGRAM_SYMBOLTABLE(arg_node) != NULL){
      printf("_SYMBOL TABLE PROGRAM_\n");
      PROGRAM_SYMBOLTABLE(arg_node) = TRAVopt(PROGRAM_SYMBOLTABLE(arg_node), arg_info);
  }
  else{
    printf("SYMBOL TABLE IS NULL\n");
  }
  printf("\n");
  DBUG_RETURN(arg_node);
}
/** <!--******************************************************************-->
 *
 * @fn PRTfundef
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node fundef node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTfundef (node * arg_node, info * arg_info)
{
  INFO_COUNT(arg_info) = INFO_COUNT(arg_info)+1;
  char *tmp;
  DBUG_ENTER("PRTfundef");
  switch(FUNDEF_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      tmp = "void";
  }

  printf("%*s", (INFO_COUNT(arg_info)-1)*4, " ");

  printf("%s %s(", tmp, FUNDEF_NAME( arg_node));
  FUNDEF_PARAMS( arg_node) = TRAVopt( FUNDEF_PARAMS( arg_node), arg_info);
  printf(") {\n");


  FUNDEF_FUNBODY( arg_node) = TRAVopt( FUNDEF_FUNBODY( arg_node), arg_info);
  printf("%*s", (INFO_COUNT(arg_info)-1)*4, " ");
  printf("}\n");


  INFO_COUNT(arg_info) = INFO_COUNT(arg_info)-1;
  DBUG_RETURN(arg_node);  
}

/** <!--******************************************************************-->
 *
 * @fn PRTexprstmt
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node exprstmt node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTexprstmt (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTexprsstmt");
  EXPRSTMT_EXPR( arg_node) = TRAVdo(EXPRSTMT_EXPR( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTfundefs
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node fundefs node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTfundefs (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTfundefs");
  FUNDEFS_FUNDEF(arg_node) = TRAVdo(FUNDEFS_FUNDEF(arg_node), arg_info);
  FUNDEFS_NEXT( arg_node) = TRAVopt( FUNDEFS_NEXT( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}
/** <!--******************************************************************-->
 *
 * @fn PRTarrexpr
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node arrexpr node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTarrexpr (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTarrexpr");
  ARREXPR_EXPRS( arg_node) = TRAVdo(ARREXPR_EXPRS( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTids
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node ids node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTids (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTids");
  printf("%s", IDS_NAME( arg_node));
  if(IDS_NEXT( arg_node) != NULL){
    printf(", ");
    IDS_NEXT( arg_node) = TRAVopt(IDS_NEXT( arg_node), arg_info);
  }
  DBUG_RETURN(arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTfuncall
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node funcall node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTfuncall (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTfuncall");
  printf("%s(", FUNCALL_NAME( arg_node));
  FUNCALL_ARGS( arg_node) = TRAVopt(FUNCALL_ARGS( arg_node), arg_info);
  printf(")");
  DBUG_RETURN(arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTfunbody
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node funbody node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTfunbody (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTfunbody");
  FUNBODY_VARDEC( arg_node) = TRAVopt(FUNBODY_VARDEC(arg_node), arg_info);
  FUNBODY_LOCALFUNDEFS( arg_node) = TRAVopt( FUNBODY_LOCALFUNDEFS( arg_node), arg_info);
  FUNBODY_STATEMENT( arg_node) = TRAVopt( FUNBODY_STATEMENT( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTglobaldef
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node globaldef node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTglobaldef (node * arg_node, info * arg_info)
{
  char *tmp;
  DBUG_ENTER("PRTglobaldef");
  switch(GLOBALDEF_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      DBUG_ASSERT( 0, "unknown type detected!");
  }

  printf("%s ", tmp);

  if(GLOBALDEF_DIMS( arg_node) != NULL){
    printf("[");
    GLOBALDEF_DIMS( arg_node) = TRAVopt( GLOBALDEF_DIMS( arg_node), arg_info);
    printf("]");


  }

  printf(" %s ",  GLOBALDEF_NAME( arg_node));

  if(GLOBALDEF_INIT( arg_node) != NULL){
    printf(" = ");
    GLOBALDEF_INIT(arg_node) = TRAVopt(GLOBALDEF_INIT(arg_node), arg_info);
  }

  printf(";\n");

  DBUG_RETURN(arg_node);
}
/** <!--******************************************************************-->
 *
 * @fn PRTparam
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node param node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTglobaldec (node * arg_node, info * arg_info)
{
  char *tmp;
  DBUG_ENTER("PRTglobaldec");
  switch(GLOBALDEC_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      DBUG_ASSERT( 0, "unknown type detected!");
  }

  printf("extern %s", tmp);

  if(GLOBALDEC_DIMS( arg_node) != NULL){
    printf("[");
    GLOBALDEC_DIMS( arg_node) = TRAVopt( GLOBALDEC_DIMS( arg_node), arg_info);
    printf("]");
  }

  printf(" %s;\n ",  GLOBALDEC_NAME( arg_node));
  DBUG_RETURN(arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTdeclarations
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node declarations node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTdeclarations (node * arg_node, info * arg_info)
{
  DBUG_ENTER("PRTdeclarations");
  DECLARATIONS_DECL( arg_node) = TRAVdo( DECLARATIONS_DECL( arg_node), arg_info);
  DECLARATIONS_NEXT( arg_node) = TRAVopt( DECLARATIONS_NEXT( arg_node), arg_info);
  DBUG_RETURN(arg_node);
}



/** <!--******************************************************************-->
 *
 * @fn PRTparam
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node param node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTparam (node * arg_node, info * arg_info)
{
  char *tmp;
  DBUG_ENTER ("PRTparam");
  switch(PARAM_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      DBUG_ASSERT( 0, "unknown type detected!");
  }
  printf("%s", tmp);

  if(PARAM_DIMS( arg_node) != NULL){
    printf("[");
    PARAM_DIMS( arg_node) = TRAVopt( PARAM_DIMS( arg_node), arg_info);
    printf("]");
  }

  printf(" %s",  PARAM_NAME( arg_node));

  if(PARAM_NEXT(arg_node) != NULL){
    printf(", ");
    PARAM_NEXT( arg_node) = TRAVopt( PARAM_NEXT( arg_node), arg_info);
  }


  DBUG_RETURN (arg_node);
}



/** <!--******************************************************************-->
 *
 * @fn PRTvardec
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node vardec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTvardec (node * arg_node, info * arg_info)
{

  printf("%*s", INFO_COUNT(arg_info)*4, " ");
  char *tmp;
  DBUG_ENTER ("PRTpvardec");
  switch(VARDEC_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      DBUG_ASSERT( 0, "unknown type detected!");
  }
  printf("%s", tmp);

  if(VARDEC_DIMS( arg_node) != NULL){
    printf("[");
    VARDEC_DIMS( arg_node) = TRAVopt( VARDEC_DIMS( arg_node), arg_info);
    printf("]");
  }

  printf(" %s ",  VARDEC_NAME( arg_node));

  if(VARDEC_INIT( arg_node) != NULL){
    printf(" = ");
    VARDEC_INIT(arg_node) = TRAVopt(VARDEC_INIT(arg_node), arg_info);
  } 
  
  printf(";");

  if(VARDEC_NEXT( arg_node) != NULL){
    printf("\n");
    VARDEC_NEXT( arg_node) = TRAVopt(VARDEC_NEXT(arg_node), arg_info);
  }
  else {
    printf("\n");
  }

  
  DBUG_RETURN (arg_node);
}



/** <!--******************************************************************-->
 *
 * @fn PRTcast
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node cast node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTcast (node * arg_node, info * arg_info)
{
  char *tmp;
  DBUG_ENTER ("PRTcast");
  switch(CAST_TYPE( arg_node)){
    case T_int:
      tmp = "int";
      break;
    case T_float: 
      tmp = "float";
      break;
    case T_boolean: 
      tmp = "bool";
      break;
    case T_unknown: 
      DBUG_ASSERT( 0, "unknown type detected!");
  }
  
  printf("(%s)", tmp);
  CAST_EXPRESSION( arg_node) = TRAVdo( CAST_EXPRESSION( arg_node), arg_info);

  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTif
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node if node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTif (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTif");
  printf("if (");
  IF_CONDITION( arg_node) = TRAVdo( IF_CONDITION(arg_node), arg_info);
  printf(") {\n");
  IF_IFBLOCK (arg_node) = TRAVdo(IF_IFBLOCK(arg_node), arg_info);
  printf("}");

  if(IF_ELSEBLOCK( arg_node) != NULL){
    printf(" else {\n");
    IF_ELSEBLOCK( arg_node) = TRAVopt(IF_ELSEBLOCK(arg_node), arg_info);
    printf("}");
  }
  printf("\n");
  DBUG_RETURN (arg_node);
}
/** <!--******************************************************************-->
 *
 * @fn PRTwhile
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node while node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTwhile (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTwhile");
  printf("while(");

  WHILE_CONDITION( arg_node) = TRAVdo( WHILE_CONDITION( arg_node), arg_info);
  printf("){\n");
  WHILE_BLOCK( arg_node) = TRAVdo( WHILE_BLOCK(arg_node), arg_info);
  printf("}\n");
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTdowhile
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node dowhile node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTdowhile (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTdowhile");

  printf("do {\n");

  DOWHILE_BLOCK( arg_node) = TRAVdo(DOWHILE_BLOCK(arg_node), arg_info);

  printf("\n}\nwhile(");

  DOWHILE_CONDITION( arg_node) = TRAVdo(DOWHILE_CONDITION( arg_node), arg_info);

  printf(")\n");

  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTfor
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node for node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTfor(node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTfor");

  printf("for( int %s = ", FOR_LOOPVAR( arg_node));
  
  FOR_START( arg_node) = TRAVdo( FOR_START(arg_node), arg_info);

  printf(", ");

  FOR_STOP( arg_node) = TRAVdo( FOR_STOP( arg_node), arg_info);

  if(FOR_STEP( arg_node) != NULL){
    printf(", ");
    FOR_STEP( arg_node) = TRAVopt( FOR_STEP( arg_node), arg_info);
  }
  printf(") {\n");
  FOR_BLOCK( arg_node) = TRAVdo( FOR_BLOCK( arg_node), arg_info);
  printf("\n}\n");

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTreturn
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node return node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTreturn (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTreturn");

  printf("%*s", INFO_COUNT(arg_info)*4, " ");
  printf("return");

  if(RETURN_EXPRESSION(arg_node) != NULL){
  printf(" ");
  RETURN_EXPRESSION( arg_node) = TRAVopt( RETURN_EXPRESSION( arg_node), arg_info);
  }

  printf(";\n");

  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTmonop
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Monop node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTmonop (node * arg_node, info * arg_info)
{
  char *tmp;
  DBUG_ENTER ("PRTmonop");

  switch (MONOP_OP( arg_node)) {
    case MO_not:
      tmp = "!";
      break;
    case MO_neg:
      tmp = "-";
      break;
    case MO_unknown:
      DBUG_ASSERT( 0, "unknown binop detected!");
  }

  printf("%s", tmp);

  MONOP_OPERAND( arg_node) = TRAVdo( MONOP_OPERAND( arg_node), arg_info);

  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTexprs
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Exprs node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
PRTexprs (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTexprs");

  EXPRS_EXPRS( arg_node) = TRAVdo( EXPRS_EXPRS( arg_node), arg_info);
  
  EXPRS_NEXT( arg_node) = TRAVopt( EXPRS_NEXT( arg_node), arg_info);

  DBUG_RETURN (arg_node);
}
/** <!--******************************************************************-->
 *
 * @fn PRTstmts
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Stmts node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTstmts (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTstmts");

  STMTS_STMT( arg_node) = TRAVdo( STMTS_STMT( arg_node), arg_info);
  
  STMTS_NEXT( arg_node) = TRAVopt( STMTS_NEXT( arg_node), arg_info);
  
  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTassign
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTassign (node * arg_node, info * arg_info)
{  
  DBUG_ENTER ("PRTassign");

  ASSIGN_LET( arg_node) = TRAVdo( ASSIGN_LET( arg_node), arg_info);
  printf( " = ");
  
  if (ASSIGN_EXPR( arg_node) != NULL) {
  ASSIGN_EXPR( arg_node) = TRAVdo( ASSIGN_EXPR( arg_node), arg_info);
  }
  
  printf( ";");
  
  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTbinop
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTbinop (node * arg_node, info * arg_info)
{
  char *tmp;

  DBUG_ENTER ("PRTbinop");


  BINOP_LEFT( arg_node) = TRAVdo( BINOP_LEFT( arg_node), arg_info);

  switch (BINOP_OP( arg_node)) {
    case BO_add:
      tmp = "+";
      break;
    case BO_sub:
      tmp = "-";
      break;
    case BO_mul:
      tmp = "*";
      break;
    case BO_div:
      tmp = "/";
      break;
    case BO_mod:
      tmp = "%";
      break;
    case BO_lt:
      tmp = "<";
      break;
    case BO_le:
      tmp = "<=";
      break;
    case BO_gt:
      tmp = ">";
      break;
    case BO_ge:
      tmp = ">=";
      break;
    case BO_eq:
      tmp = "==";
      break;
    case BO_ne:
      tmp = "!=";
      break;
    case BO_or:
      tmp = "||";
      break;
    case BO_and:
      tmp = "&&";
      break;
    case BO_unknown:
      DBUG_ASSERT( 0, "unknown binop detected!");
  }

  printf( " %s ", tmp);

  BINOP_RIGHT( arg_node) = TRAVdo( BINOP_RIGHT( arg_node), arg_info);


  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTfloat
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Float node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTfloat (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTfloat");

  printf("%f", FLOAT_VALUE( arg_node));

  DBUG_RETURN (arg_node);
}



/** <!--******************************************************************-->
 *
 * @fn PRTint
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node int node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTnum (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTint");

  printf( "%i", NUM_VALUE( arg_node));

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTboolean
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Boolean node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTbool (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTbool");

  if (BOOL_VALUE( arg_node)) {
    printf( "true");
  }
  else {
    printf( "false");
  }
  
  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTvar
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTvar (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTvar");

  printf( "%s", VAR_NAME( arg_node));

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTvarlet
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTvarlet (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTvarlet");

  printf( "%s", VARLET_NAME( arg_node));

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTerror
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTerror (node * arg_node, info * arg_info)
{
  bool first_error;

  DBUG_ENTER ("PRTerror");

  if (NODE_ERROR (arg_node) != NULL) {
    NODE_ERROR (arg_node) = TRAVdo (NODE_ERROR (arg_node), arg_info);
  }

  first_error = INFO_FIRSTERROR( arg_info);

  if( (global.outfile != NULL)
      && (ERROR_ANYPHASE( arg_node) == global.compiler_anyphase)) {

    if ( first_error) {
      printf ( "\n/******* BEGIN TREE CORRUPTION ********\n");
      INFO_FIRSTERROR( arg_info) = FALSE;
    }

    printf ( "%s\n", ERROR_MESSAGE( arg_node));

    if (ERROR_NEXT (arg_node) != NULL) {
      TRAVopt (ERROR_NEXT (arg_node), arg_info);
    }

    if ( first_error) {
      printf ( "********  END TREE CORRUPTION  *******/\n");
      INFO_FIRSTERROR( arg_info) = TRUE;
    }
  }

  DBUG_RETURN (arg_node);
}



/** <!-- ****************************************************************** -->
 * @brief Prints the given syntaxtree
 * 
 * @param syntaxtree a node structure
 * 
 * @return the unchanged nodestructure
 ******************************************************************************/

node 
*PRTdoPrint( node *syntaxtree)
{
  info *info;
  
  DBUG_ENTER("PRTdoPrint");

  DBUG_ASSERT( (syntaxtree!= NULL), "PRTdoPrint called with empty syntaxtree");

  printf( "\n\n------------------------------\n\n");

  info = MakeInfo();
  
  TRAVpush( TR_prt);

  syntaxtree = TRAVdo( syntaxtree, info);

  TRAVpop();

  info = FreeInfo(info);

  printf( "\n------------------------------\n\n");

  DBUG_RETURN( syntaxtree);
}

/**
 * @}
 */

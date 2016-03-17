
/**
 * @file eval.c
 *
 * Functions needed for compiling
 * 
 * THIS FILE HAS BEEN GENERATED USING 
 * $Id: free_node.c.xsl 14593 2006-01-31 17:09:55Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

/**
 * @defgroup comp Compilation functions.
 *
 * Functions needed for compiling.
 *
 * @{
 */


#include "eval.h"
#include "traverse.h"
#include "dbug.h"


/** <!--******************************************************************-->
 *
 * @fn EVALarrexpr
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Arrexpr node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALarrexpr (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALarrexpr");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALassign
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Assign node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALassign (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALassign");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALbinop
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALbinop (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALbinop");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALbool
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Bool node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALbool (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALbool");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALcast
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Cast node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALcast (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALcast");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALdeclarations
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Declarations node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALdeclarations (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALdeclarations");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALdowhile
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node DoWhile node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALdowhile (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALdowhile");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALerror
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Error node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALerror (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALerror");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALexprs
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Exprs node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALexprs (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALexprs");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALexprstmt
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Exprstmt node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALexprstmt (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALexprstmt");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALfloat
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Float node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALfloat (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALfloat");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALfor
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node For node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALfor (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALfor");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALfunbody
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node FunBody node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALfunbody (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALfunbody");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALfundef
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node FunDef node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALfundef (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALfundef");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALfundefs
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node FunDefs node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALfundefs (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALfundefs");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALfuncall
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Funcall node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALfuncall (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALfuncall");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALglobaldec
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node GlobalDec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALglobaldec (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALglobaldec");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALglobaldef
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node GlobalDef node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALglobaldef (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALglobaldef");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALids
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Ids node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALids (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALids");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALif
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node If node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALif (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALif");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALmonop
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node MonOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALmonop (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALmonop");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALnum
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Num node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALnum (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALnum");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALparam
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Param node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALparam (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALparam");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALprogram
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Program node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALprogram (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALprogram");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALreturn
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Return node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALreturn (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALreturn");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALstmts
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Stmts node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALstmts (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALstmts");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALsymbol
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Symbol node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALsymbol (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALsymbol");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALvar
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node Var node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALvar (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALvar");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALvardec
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node VarDec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALvardec (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALvardec");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALvarlet
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node VarLet node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALvarlet (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALvarlet");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn EVALwhile
 *
 * @brief Frees the node and its sons/attributes
 *
 * @param arg_node While node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/
node *
EVALwhile (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("EVALwhile");
  arg_node = TRAVcont (arg_node, arg_info);
  DBUG_RETURN (arg_node);
}

/**
 * @}
 */

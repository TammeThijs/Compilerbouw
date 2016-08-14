#ifndef _SYMBOL_TABLE_H_
#define _SYMBOl_TABLE_H_
#include "types.h"

extern node *SYMprogram (node *arg_node, info *arg_info);
extern node *SYMdeclarations (node *arg_node, info *arg_info);
extern node *SYMcreatesymboltable( node *syntaxtree);
extern node *SYMglobaldec(node *arg_node, info *arg_info);
extern node *SYMglobaldef(node *arg_node, info *arg_info);
extern node *SYMfundef(node *arg_node, info *arg_info);
extern node *SYMparam(node *arg_node, info *arg_info);
extern node *SYMvardec(node *arg_node, info *arg_info);
extern node *SYMfundefs(node *arg_node, info *arg_info);
extern node *SYMstmts(node *arg_node, info *arg_info);
extern node *SYMfor(node *arg_node, info *arg_info);
extern node *SYMfunbody (node *arg_node, info *arg_info);

#endif

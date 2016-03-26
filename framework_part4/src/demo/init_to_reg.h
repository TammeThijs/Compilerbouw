#ifndef _INIT_TO_REG_H_
#define _INIT_TO_REG_H_
#include "types.h"

extern node *INITglobaldef (node *arg_node, info *arg_info);
extern node *INITglobaldec (node *arg_node, info *arg_info);
extern node *INITvardec (node *arg_node, info *arg_info);
extern node *INITfunbody (node *arg_node, info *arg_info);
extern node *INITstmts (node *arg_node, info *arg_info);
extern node *INITdoInitToReg( node *syntaxtree);

#endif

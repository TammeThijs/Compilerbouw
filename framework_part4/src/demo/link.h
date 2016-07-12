#ifndef _LINK_H_
#define _LINK_H_
#include "types.h"

extern node *LINKcreatelinks(node *syntaxtree);
extern node *LINKprogram(node *arg_node, info *arg_info);
extern node *LINKfundef(node *arg_node, info *arg_info);
extern node *LINKvar(node *arg_node, info *arg_info);
extern node *LINKassign(node *arg_node, info *arg_info);
extern node *LINKvarlet( node *arg_node, info *arg_info);
extern node *LINKfuncall( node *arg_node, info *arg_info);

#endif
#ifndef _REWRITE_H_
#define _REWRITE_H_
#include "types.h"

extern node RWrewritecode(node *syntaxtree);
extern node RWbinop(node *arg_node, info *arg_info);
extern node RWcast(node *arg_node, info *arg_info);

#endif
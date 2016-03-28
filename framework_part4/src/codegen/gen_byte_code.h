#ifndef _GEN_BYTE_CODE_H_
#define _GEN_BYTE_CODE_H_
#include "types.h"

extern node *GBCdoGenByteCode( node *syntaxtree);
extern node *GBCfundef( node *arg_node, info *arg_info);
extern node *GBCbinop( node *arg_node, info *arg_info);
extern node *GBCassign( node *arg_node, info *arg_info);

#endif

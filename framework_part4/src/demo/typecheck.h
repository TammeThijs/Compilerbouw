#ifndef _TYPECHECK_H_
#define _TYPECHECK_H_
#include "types.h"

extern node *CTchecktypes(node *syntaxtree);
extern node *CTprogram(node *arg_node, info *arg_info);
extern node *CTvar(node *arg_node, info *arg_info);
extern node *CTvarlet( node *arg_node, info *arg_info);
extern node *CTfuncall( node *arg_node, info *arg_info);
extern node *CTfundef( node *arg_node, info *arg_info);
extern node *CTvardec( node *arg_node, info *arg_info);
extern node *CTassign(node *arg_node, info *arg_info);
extern node *CTcast( node *arg_node, info *arg_info);
extern node *CTbinop( node *arg_node, info *arg_info);
extern node *CTmonop( node *arg_node, info *arg_info);
extern node *CTnum(node *arg_node, info *arg_info);

extern node *CTbool(node *arg_node, info *arg_info);

extern node *CTfloat(node *arg_node, info *arg_info);

#endif
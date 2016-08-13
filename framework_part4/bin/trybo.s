__init:

printBool:
   bload_0
   branch_f 1_else
   isrg
   iloadc_1
   jsre 0
   jump 2_end
1_else:
   isrg
   iloadc_0
   jsre 0
2_end:
   isrg
   iloadc_1
   jsre 1

   return
t:
   isrg
   iloadc_1
   jsre 0
   bloadc_t
   breturn

f:
   isrg
   iloadc_0
   jsre 0
   bloadc_f
   breturn

main:
   isrg
   isrg
   jsr 0 t
   branch_f 3_false_expr
   isrg
   jsr 0 f
   jump 4_end
3_false_expr:
   bloadc_t
4_end:
   jsr 1 printBool
   iloadc_0
   ireturn

.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printNewlines" void int 

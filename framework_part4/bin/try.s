__init:

main:
   esr 2
   iloadc 0
   istore 0
   iloadc_0
1_for:
   iload 1
   iload_0
   ilt   branch_f 2_end
   isrg
   iload_1
   jsre 0
   isrg
   iloadc_1
   jsre 1
   iinc_1 1
   jump 1_for
2_end: 
   isrg
   iloadc_1
   jsre 2
   iloadc_0
   ireturn

.const int  10
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printSpaces" void int 
.importfun "printNewlines" void int 

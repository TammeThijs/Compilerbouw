__init:

main:
   esr 1
1_for:
   iload_0
   iloadc 0
   ilt
   branch_f 2_end
   isrg
   iload_0
   jsre 0
   isrg
   iloadc_1
   jsre 1
   iinc_1 0
   jump 1_for
2_end: 
   iloadc_0
   ireturn

.const int  4
.exportfun "__init" void __init
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printSpaces" void int 
.importfun "printNewlines" void int 

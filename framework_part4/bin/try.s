__init:

main:
   esr 5
   iloadc 0
   istore 0
   iloadc_0
   istore 1
   iloadc 0
   istore 2
   iloadc 2
   istore 3
   iloadc 0
   istore 4
   iloadc 2
   istore 2
   iload_1
1_for:
   iload 5
   iload_2
   ilt   branch_f 2_end
   iload 4
   iloadc_1
   isub
   istore 4
   isrg
   iload 4
   jsre 0
   isrg
   iloadc 5
   jsre 4
   iinc_1 5
   jump 1_for
2_end: 
   isrg
   iloadc_1
   jsre 5
   iloadc 2
   istore 2
   iload_0
3_for:
   iload 5
   iload_2
   ilt   branch_f 4_end
   iload 4
   iloadc_1
   isub
   istore 4
   isrg
   iload 4
   jsre 0
   isrg
   iloadc 5
   jsre 4
   iinc_1 5
   jump 3_for
4_end: 
   isrg
   iloadc_1
   jsre 5
   iloadc_0
   ireturn

.const int  10
.const int  10
.const int  5
.const int  10
.const int  5
.const int  3
.const int  5
.const int  3
.exportfun "__init" void __init
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printFloat" void float 
.importfun "scanInt" int 
.importfun "scanFloat" float 
.importfun "printSpaces" void int 
.importfun "printNewlines" void int 

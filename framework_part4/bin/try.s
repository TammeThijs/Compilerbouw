main:
   esr 6
   iloadc_0
   istore 0
   iloadc 0
   istore 1
   iloadc_0
   istore 2
   iloadc 1
   istore 3
   iloadc_0
   istore 4
   iloadc_0
   istore 5
   jump 1_for
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
   isrg
   iloadc_1
   jsre 2
   jump 3_for
3_for:
   iload_1
   iloadc_0
   igt
   branch_f 4_end
   isrg
   iload_1
   jsre 0
   isrg
   iloadc_1
   jsre 1
   idec_1 1
   jump 3_for
4_end: 
   isrg
   iloadc_1
   jsre 2
   jump 5_for
5_for:
   iload_2
   iloadc 0
   ilt
   branch_f 6_end
   isrg
   iload_2
   jsre 0
   isrg
   iloadc_1
   jsre 1
   iinc 2  2
   jump 5_for
6_end: 
   isrg
   iloadc_1
   jsre 2
   jump 7_for
7_for:
   iload_3
   iloadc_0
   igt
   branch_f 8_end
   isrg
   iload_3
   jsre 0
   isrg
   iloadc_1
   jsre 1
   idec 3  3
   jump 7_for
8_end: 
   jump 9_for
9_for:
   iload 4
   iloadc 4
   ilt
   branch_f 10_end
   jump 11_for
11_for:
   iload 5
   iloadc 5
   ilt
   branch_f 12_end
   isrg
   iload 4
   jsre 0
   isrg
   iloadc_1
   jsre 1
   isrg
   iload 5
   jsre 0
   isrg
   iloadc_1
   jsre 1
   iinc_1 5
   jump 11_for
12_end: 
   isrg
   iloadc_1
   jsre 2
   iinc_1 4
   jump 9_for
10_end: 
   iloadc_0
   ireturn

.const int  10
.const int  7
.const int  2
.const int  3
.const int  5
.const int  4
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printSpaces" void int 
.importfun "printNewlines" void int 

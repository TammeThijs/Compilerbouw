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
   isrg
   jsr 0 f
   beq
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 t
   beq
   jsr 1 printBool
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 t
   beq
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 f
   beq
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 f
   bne
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 t
   bne
   jsr 1 printBool
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 t
   bne
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 f
   bne
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   isrg
   jsr 0 t
   branch_f 3_false_expr
   isrg
   jsr 0 f
   jump 4_end
3_false_expr:
   bloadc_f
4_end:
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   branch_f 5_false_expr
   isrg
   jsr 0 t
   jump 6_end
5_false_expr:
   bloadc_f
6_end:
   jsr 1 printBool
   isrg
   isrg
   jsr 0 t
   branch_f 7_false_expr
   isrg
   jsr 0 t
   jump 8_end
7_false_expr:
   bloadc_f
8_end:
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   branch_f 9_false_expr
   isrg
   jsr 0 f
   jump 10_end
9_false_expr:
   bloadc_f
10_end:
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   isrg
   jsr 0 t
   branch_f 11_false_expr
   bloadc_t
   jump 12_end
11_false_expr:
   isrg
   jsr 0 f
12_end:
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   branch_f 13_false_expr
   bloadc_t
   jump 14_end
13_false_expr:
   isrg
   jsr 0 t
14_end:
   jsr 1 printBool
   isrg
   isrg
   jsr 0 t
   branch_f 15_false_expr
   bloadc_t
   jump 16_end
15_false_expr:
   isrg
   jsr 0 t
16_end:
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   branch_f 17_false_expr
   bloadc_t
   jump 18_end
17_false_expr:
   isrg
   jsr 0 f
18_end:
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 f
   bmul
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 t
   bmul
   jsr 1 printBool
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 t
   bmul
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 f
   bmul
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 f
   badd
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 t
   badd
   jsr 1 printBool
   isrg
   isrg
   jsr 0 t
   isrg
   jsr 0 t
   badd
   jsr 1 printBool
   isrg
   isrg
   jsr 0 f
   isrg
   jsr 0 f
   badd
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   iloadc 0
   iloadc_0
   igt
   branch_f 19_false_expr
   bloadc_t
   jump 20_end
19_false_expr:
   bloadc_f
20_end:
   jsr 1 printBool
   isrg
   iloadc_0
   iloadc_0
   igt
   branch_f 21_false_expr
   bloadc_t
   jump 22_end
21_false_expr:
   bloadc_f
22_end:
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   isrg
   floadc 1
   floadc_0
   fgt
   branch_f 23_false_expr
   bloadc_t
   jump 24_end
23_false_expr:
   bloadc_f
24_end:
   jsr 1 printBool
   isrg
   floadc_0
   floadc_0
   fgt
   branch_f 25_false_expr
   bloadc_t
   jump 26_end
25_false_expr:
   bloadc_f
26_end:
   jsr 1 printBool
   isrg
   iloadc_1
   jsre 1
   iloadc_0
   ireturn

.const int  5
.const float  5.000000
.exportfun "__init" void __init
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printNewlines" void int 

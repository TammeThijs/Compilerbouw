__init:

foo:
   iload_0
   fload_1
   f2i
   iadd
   iload_2
   iadd
   ireturn

fun:
   esr 7
   iloadc_1
   istore 0
   iloadc 0
   istore 1
   iloadc 1
   istore 2
   iloadc 2
   istore 3
   floadc_1
   fstore 4
   floadc 3
   fstore 5
   bloadc_t
   bstore 6
   iload_0
   iload_1
   ilt
   branch_f 1_false_expr
   iload_2
   iload_3
   igt
   jump 2_end
1_false_expr:
   bloadc_f
2_end:
   branch_f 3_false_expr
   iloadc_0
   jump 4_end
3_false_expr:
   iloadc_1
4_end:
   istore 3
   isrg
   iload_3
   jsre 0
   isrg
   iloadc_1
   jsre 5
   isrg
   iload_0
   iload_2
   ilt
   branch_f 5_false_expr
   iloadc_0
   jump 6_end
5_false_expr:
   iloadc_1
6_end:
   fload 4
   fload 5
   fadd
   iload_1
   iload_3
   ilt
   branch_f 7_false_expr
   iloadc_0
   jump 8_end
7_false_expr:
   iloadc_1
8_end:
   jsr 3 foo
   istore 3
   isrg
   iload_3
   jsre 0
   isrg
   iloadc_1
   jsre 5
   iload_1
   iload_3
   ilt
   branch_f 9_false_expr
   iload_0
   iload_2
   igt
   jump 10_end
9_false_expr:
   bloadc_t
10_end:
   branch_f 11_end
   iloadc 4
   istore 0
   jump 11_end

11_end:
   iloadc_1
   ireturn

bar:
   esr 3
   iloadc 5
   istore 0
   floadc 6
   fstore 1
   iload_0
   fload_1
   f2i
   iload_0
   imul
   iadd
   istore 2
   isrg
   iload_2
   jsre 0
   isrg
   iloadc_1
   jsre 5

main:
   isrg
   jsr 0 fun
   isrg
   jsr 0 bar
   iloadc_0
   ireturn

.const int  2
.const int  3
.const int  4
.const float  2.000000
.const int  7
.const int  5
.const float  6.000000
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printFloat" void float 
.importfun "scanInt" int 
.importfun "scanFloat" float 
.importfun "printSpaces" void int 
.importfun "printNewlines" void int 

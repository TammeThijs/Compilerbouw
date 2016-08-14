__init:
   iloadc_1
   istoreg 0
   iloadc 0
   istoreg 1
   return

foo:
   esr 2
   iloadc 1
   istore 0
   iload_0
   istore 1
   isrg
   iload_0
   jsre 0
   isrg
   iloadc_1
   jsre 1
   isrg
   iload_1
   jsre 0
   isrg
   iloadc_1
   jsre 1
   isrg
   iloadg 1
   jsre 0
   isrg
   iloadc_1
   jsre 1

   return
bar:
   esr 1
   iload_0
   iloadc_1
   iadd
   istore 0
   isrg
   iload_0
   jsre 0
   isrg
   iloadc_1
   jsre 1

   return
baz:
   esr 2
   iload_0
   istore 1
   iloadc 2
   istore 0
   isrg
   iload_1
   jsre 0
   isrg
   iloadc_1
   jsre 1

   return
main:
   isrg
   jsr 0 foo
   isrg
   jsr 0 bar
   isrg
   iloadg 0
   jsre 0
   isrg
   iloadc_1
   jsre 1
   isrg
   jsr 0 baz
   isrg
   iloadg 1
   jsre 0
   isrg
   iloadc_1
   jsre 1
   iloadc_0
   ireturn

.const int  10
.const int  3
.const int  5
.exportfun "__init" void __init
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printNewlines" void int 
.global int
.global int

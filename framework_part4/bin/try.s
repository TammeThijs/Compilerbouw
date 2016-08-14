main:
   esr 2
   iloadc 0
   istore 0
   iload_0
   istore 1
   isrl
   iload_0
   jsr 1 _main_bar
   isrg
   iload_0
   jsre 0
   isrg
   iloadc 1
   jsre 2
   isrg
   iload_0
   jsr 1 baz
   isrg
   iload_0
   jsre 0
   isrg
   iloadc 1
   jsre 2
   isrg
   iload_0
   jsr 1 bor
   isrg
   iload_0
   jsre 0
   isrg
   iloadc 1
   jsre 2
   isrl
   jsr 0 _main_boz
   isrg
   iload_0
   jsre 0
   isrg
   iloadc 1
   jsre 2
   isrg
   iload_1
   jsre 0
   isrg
   iloadc 1
   jsre 2
   isrl
   jsr 0 _main_biz
   isrg
   iload_0
   jsre 0
   isrg
   iloadc 1
   jsre 2
   isrg
   iload_1
   jsre 0
   isrg
   iloadc_1
   jsre 2
   iloadc_0
   ireturn

_main_bar:
   iloadc 2
   istore 0
   isrg
   iload_0
   jsre 0
   isrg
   iloadc_1
   jsre 2
   return
_main_boz:
   esr 1
   iloadn 1 0
   istore 0
   iload_0
   iloadc 2
   iadd
   istore 0
   isrg
   iload_0
   jsre 0
   isrg
   iloadc_1
   jsre 2
   return
_main_biz:
   iloadc 3
   istoren 0 0
   return
baz:
   isrl
   jsr 0 _baz_baz_inner
   return
_baz_baz_inner:
   esr 1
   iloadc 4
   istore 0
   isrg
   iload_0
   jsre 0
   isrg
   iloadc_1
   jsre 2
   return
bor:
   isrl
   jsr 0 _bor_baz_inner
   return
_bor_baz_inner:
   isrl
   jsr 0 __bor_baz_inner_b
   return
__bor_baz_inner_b:
   isrg
   iloadc 5
   jsre 0
   isrg
   iloadc_1
   jsre 2
   return
.const int  123
.const int  2
.const int  11111
.const int  55555
.const int  22222
.const int  33333
.exportfun "main" int main
.importfun "printInt" void int 
.importfun "printSpaces" void int 
.importfun "printNewlines" void int 

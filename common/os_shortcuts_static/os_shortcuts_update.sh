#!/bin/bash
#
# Script to update static macro definition files
gcc -E -D'DEFINE_SHORTCUT(n,m,w,l)=__DEF__ SC_##n m' ../os_shortcut_defs.h | sed -e 's/__DEF__/#define/g' > os_shortcuts_macos.h
gcc -E -D'DEFINE_SHORTCUT(n,m,w,l)=__DEF__ SC_##n w' ../os_shortcut_defs.h | sed -e 's/__DEF__/#define/g' > os_shortcuts_windows.h
gcc -E -D'DEFINE_SHORTCUT(n,m,w,l)=__DEF__ SC_##n l' ../os_shortcut_defs.h | sed -e 's/__DEF__/#define/g' > os_shortcuts_linux.h 
gcc -E -D'DEFINE_SHORTCUT(n,m,w,l)=__DEF__ SC_##n KC_NO' ../os_shortcut_defs.h | sed -e 's/__DEF__/#define/g' > os_shortcuts_null.h


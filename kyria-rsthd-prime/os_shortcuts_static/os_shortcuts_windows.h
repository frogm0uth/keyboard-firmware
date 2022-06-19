# 1 "../os_shortcut_defs.h"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 361 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../os_shortcut_defs.h" 2
# 25 "../os_shortcut_defs.h"
#define SC_CMD_CTRL KC_LCTL





#define SC_WORD_LEFT C(KC_LEFT)
#define SC_WORD_RIGHT C(KC_RGHT)
#define SC_START_OF_LINE KC_HOME
#define SC_END_OF_LINE KC_END
#define SC_START_OF_PARA C(KC_UP)
#define SC_END_OF_PARA C(KC_DOWN)
#define SC_START_OF_DOC C(KC_HOME)
#define SC_END_OF_DOC C(KC_END)





#define SC_DEL_WORD_LEFT C(KC_BSPC)
#define SC_DEL_WORD_RIGHT C(KC_DEL)





#define SC_APPSWITCH_START KC_LALT
#define SC_APPSWITCH_RIGHT KC_TAB
#define SC_APPSWITCH_LEFT S(KC_TAB)





#define SC_EXPOSE_ALL G(KC_TAB)
#define SC_NEXT_SCREEN G(C(KC_RGHT))
#define SC_PREV_SCREEN G(C(KC_LEFT))
#define SC_FULLSCREEN KC_F11

#define SC_EXPOSE_WINDOWS G(A(KC_TAB))
#define SC_NEXT_APP KC_NO
#define SC_PREV_APP KC_NO
#define SC_REVEAL_DESKTOP G(KC_D)






#define SC_SNAP_LEFT G(KC_LEFT)
#define SC_SNAP_RIGHT G(KC_RIGHT)
#define SC_SNAP_TOP A(G(KC_UP))
#define SC_SNAP_BOTTOM A(G(KC_DOWN))

#define SC_SNAP_TOPLEFT KC_NO
#define SC_SNAP_TOPRIGHT G(KC_Z)
#define SC_SNAP_BOTTOMLEFT KC_NO
#define SC_SNAP_BOTTOMRIGHT KC_NO

#define SC_SNAP_VERTICAL S(G(KC_UP))





#define SC_NEXT_WINDOW A(KC_ESC)
#define SC_PREV_WINDOW S(A(KC_ESC))
#define SC_TAB_RIGHT C(KC_TAB)
#define SC_TAB_LEFT S(C(KC_TAB))





#define SC_NEXT_SEARCH KC_F3
#define SC_PREV_SEARCH S(KC_F3)
#define SC_BROWSER_BACK A(KC_LEFT)
#define SC_BROWSER_FWD A(KC_RIGHT)





#define SC_SELECT_ALL C(KC_A)
#define SC_CUT_SELECTION C(KC_X)
#define SC_COPY_SELECTION C(KC_C)
#define SC_PASTE_CLIPBOARD C(KC_V)
#define SC_UNDO_ACTION C(KC_Z)
#define SC_REDO_ACTION C(KC_Y)





#define SC_APP_ZOOM_IN C(KC_EQL)
#define SC_APP_ZOOM_OUT C(KC_MINS)
#define SC_APP_ZOOM_RESET C(KC_0)

#define SC_SCR_ZOOM_IN G(KC_EQL)
#define SC_SCR_ZOOM_OUT G(KC_MINS)
#define SC_SCR_ZOOM_RESET KC_NO





#define SC_SHOT_SCREEN G(KC_PSCR)
#define SC_SHOT_REGION G(S(KC_S))





#define SC_OPEN C(KC_O)
#define SC_CLOSE_TAB C(KC_W)
#define SC_QUIT A(KC_F4)
#define SC_NEW C(KC_N)
#define SC_NEW_TAB C(KC_T)

#define SC_SAVE C(KC_N)
#define SC_SAVE_AS KC_F12
#define SC_PRINT C(KC_P)
#define SC_FIND C(KC_F)
#define SC_BIN C(KC_D)





#define SC_SEARCH KC_LGUI
#define SC_SCREEN_LOCK G(KC_L)
#define SC_SYSTEM_SLEEP KC_SLEP

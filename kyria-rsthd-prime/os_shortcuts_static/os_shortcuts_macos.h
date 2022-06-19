# 1 "../os_shortcut_defs.h"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 361 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../os_shortcut_defs.h" 2
# 25 "../os_shortcut_defs.h"
#define SC_CMD_CTRL KC_LGUI





#define SC_WORD_LEFT A(KC_LEFT)
#define SC_WORD_RIGHT A(KC_RGHT)
#define SC_START_OF_LINE G(KC_LEFT)
#define SC_END_OF_LINE G(KC_RGHT)
#define SC_START_OF_PARA A(KC_UP)
#define SC_END_OF_PARA A(KC_DOWN)
#define SC_START_OF_DOC G(KC_UP)
#define SC_END_OF_DOC G(KC_DOWN)





#define SC_DEL_WORD_LEFT A(KC_BSPC)
#define SC_DEL_WORD_RIGHT A(KC_DEL)





#define SC_APPSWITCH_START KC_LGUI
#define SC_APPSWITCH_RIGHT KC_TAB
#define SC_APPSWITCH_LEFT S(KC_TAB)





#define SC_EXPOSE_ALL C(KC_UP)
#define SC_NEXT_SCREEN C(KC_RGHT)
#define SC_PREV_SCREEN C(KC_LEFT)
#define SC_FULLSCREEN G(C(KC_F))

#define SC_EXPOSE_WINDOWS C(KC_DOWN)
#define SC_NEXT_APP KC_TAB
#define SC_PREV_APP S(KC_TAB)
#define SC_REVEAL_DESKTOP KC_F11






#define SC_SNAP_LEFT C(A(KC_LEFT))
#define SC_SNAP_RIGHT C(A(KC_RIGHT))
#define SC_SNAP_TOP C(A(KC_UP))
#define SC_SNAP_BOTTOM C(A(KC_DOWN))

#define SC_SNAP_TOPLEFT C(A(KC_U))
#define SC_SNAP_TOPRIGHT C(A(KC_I))
#define SC_SNAP_BOTTOMLEFT C(A(KC_J))
#define SC_SNAP_BOTTOMRIGHT C(A(KC_K))

#define SC_SNAP_VERTICAL S((A(KC_UP)))





#define SC_NEXT_WINDOW G(KC_GRAVE)
#define SC_PREV_WINDOW S(G(KC_GRAVE))
#define SC_TAB_RIGHT G(KC_RCBR)
#define SC_TAB_LEFT G(KC_LCBR)





#define SC_NEXT_SEARCH G(KC_G)
#define SC_PREV_SEARCH S(G(KC_G))
#define SC_BROWSER_BACK G(KC_LBRC)
#define SC_BROWSER_FWD G(KC_RBRC)





#define SC_SELECT_ALL G(KC_A)
#define SC_CUT_SELECTION G(KC_X)
#define SC_COPY_SELECTION G(KC_C)
#define SC_PASTE_CLIPBOARD G(KC_V)
#define SC_UNDO_ACTION G(KC_Z)
#define SC_REDO_ACTION S(G(KC_Z))





#define SC_APP_ZOOM_IN G(KC_EQL)
#define SC_APP_ZOOM_OUT G(KC_MINS)
#define SC_APP_ZOOM_RESET G(KC_0)

#define SC_SCR_ZOOM_IN A(G(KC_EQL))
#define SC_SCR_ZOOM_OUT A(G(KC_MINS))
#define SC_SCR_ZOOM_RESET A(G(KC_8))





#define SC_SHOT_SCREEN S(G(KC_3))
#define SC_SHOT_REGION S(G(KC_4))





#define SC_OPEN G(KC_O)
#define SC_CLOSE_TAB G(KC_W)
#define SC_QUIT G(KC_Q)
#define SC_NEW G(KC_N)
#define SC_NEW_TAB G(KC_T)

#define SC_SAVE G(KC_S)
#define SC_SAVE_AS S(G(KC_S))
#define SC_PRINT G(KC_P)
#define SC_FIND G(KC_F)
#define SC_BIN G(KC_BSPC)





#define SC_SEARCH G(KC_SPC)
#define SC_SCREEN_LOCK C(G(KC_Q))
#define SC_SYSTEM_SLEEP A(G(KC_EJCT))

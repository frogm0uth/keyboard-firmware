/* Copyright 2020 @frogm0uth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 ** Platform-dependent shortcuts. This file is included in multiple places
 ** with different definitions of DEFINE_SHORTCUT.
 **/

// clang-format off

/**
 * Command or ctrl, depending on OS
 */
DEFINE_SHORTCUT( CMD_CTRL,       KC_LGUI,   KC_LCTL,   KC_LCTL )


/** 
 * Moving the cursor in text
 */
DEFINE_SHORTCUT( WORD_LEFT,      A(KC_LEFT),   C(KC_LEFT),   C(KC_LEFT) )    // Move word left
DEFINE_SHORTCUT( WORD_RIGHT,     A(KC_RGHT),   C(KC_RGHT),   C(KC_RGHT) )    // Move word right
DEFINE_SHORTCUT( START_OF_LINE,  G(KC_LEFT),   KC_HOME,      KC_HOME )       // Move to start of line
DEFINE_SHORTCUT( END_OF_LINE,    G(KC_RGHT),   KC_END,       KC_END )        // Move to end of line
DEFINE_SHORTCUT( START_OF_PARA,  A(KC_UP),     C(KC_UP),     C(KC_UP) )      // Move to start of paragraph (or up one)
DEFINE_SHORTCUT( END_OF_PARA,    A(KC_DOWN),   C(KC_DOWN),   C(KC_DOWN) )    // Move to end of paragraph (or down one)
DEFINE_SHORTCUT( START_OF_DOC,   G(KC_UP),     C(KC_HOME),   C(KC_HOME) )    // Move to start of document
DEFINE_SHORTCUT( END_OF_DOC,     G(KC_DOWN),   C(KC_END),    C(KC_END) )     // Move to end of document

DEFINE_SHORTCUT( REALPAGE_UP,    G(KC_PGUP),   KC_UP,     KC_UP )    // Move up a physical page
DEFINE_SHORTCUT( REALPAGE_DOWN,  G(KC_PGDN),   KC_UP,     KC_UP )    // Move down a physical page


/**
 * Text deletion
 */
DEFINE_SHORTCUT( DEL_WORD_LEFT,      A(KC_BSPC),   C(KC_BSPC),   C(KC_BSPC) )    // Delete word left
DEFINE_SHORTCUT( DEL_WORD_RIGHT,     A(KC_DEL),    C(KC_DEL),    C(KC_DEL) )     // Delete word right


/**
 * App switcher
 */
DEFINE_SHORTCUT( APPSWITCH_START, KC_LGUI,   KC_LALT,   KC_LALT )   // Start app switcher
DEFINE_SHORTCUT( APPSWITCH_RIGHT, KC_TAB,    KC_TAB,    KC_TAB )    // Next application
DEFINE_SHORTCUT( APPSWITCH_LEFT,  S(KC_TAB), S(KC_TAB), S(KC_TAB) ) // Previous application


/**
 * Window management
 */
DEFINE_SHORTCUT( EXPOSE_ALL,      C(KC_UP),    G(KC_TAB),       G(KC_TAB) )       // Expose all windows and desktops
DEFINE_SHORTCUT( NEXT_SCREEN,     C(KC_RGHT),  G(C(KC_RGHT)),   G(C(KC_RGHT)) )   // Move to next screen
DEFINE_SHORTCUT( PREV_SCREEN,     C(KC_LEFT),  G(C(KC_LEFT)),   G(C(KC_LEFT)) )   // Move to previous screen
DEFINE_SHORTCUT( FULLSCREEN,      G(C(KC_F)),  KC_F11,          KC_F11 )          // Toggle window to/from full-screen

DEFINE_SHORTCUT( EXPOSE_WINDOWS,  C(KC_DOWN),  G(A(KC_TAB)),    G(A(KC_TAB))  )   // Expose windows of current app
DEFINE_SHORTCUT( NEXT_APP,        KC_TAB,      KC_NO,           KC_NO  )          // Next application while in Mission Control FIXME not working in Win/Linux
DEFINE_SHORTCUT( PREV_APP,        S(KC_TAB),   KC_NO,           KC_NO  )          // Previous application
DEFINE_SHORTCUT( REVEAL_DESKTOP,  KC_F11,      G(KC_D),         G(KC_D)  )        // Reveal desktop


/**
 * Window snapping. On macOS this needs Rectangle Pro installed
 * FIXME for Linux (KDE)
 */
DEFINE_SHORTCUT( SNAP_LEFT,       C(A(KC_LEFT)),   G(KC_LEFT),      KC_NO )       // Snap to left half of screen
DEFINE_SHORTCUT( SNAP_RIGHT,      C(A(KC_RIGHT)),  G(KC_RIGHT),     KC_NO )       // Snap to right half of screen
DEFINE_SHORTCUT( SNAP_TOP,        C(A(KC_UP)),     A(G(KC_UP)),     KC_NO )       // Snap to top half of screen
DEFINE_SHORTCUT( SNAP_BOTTOM,     C(A(KC_DOWN)),   A(G(KC_DOWN)),   KC_NO )       // Snap to bottom half of screen

DEFINE_SHORTCUT( SNAP_TOPLEFT,     C(A(KC_U)),      KC_NO,        KC_NO )       // Snap to top left quadrant of screen
DEFINE_SHORTCUT( SNAP_TOPRIGHT,    C(A(KC_I)),      G(KC_Z),      KC_NO )       // Snap to top right quadrant of screen (macOS), open snap options (Windows)
DEFINE_SHORTCUT( SNAP_BOTTOMLEFT,  C(A(KC_J)),      KC_NO,        KC_NO )       // Snap to bottom left quadrant of screen
DEFINE_SHORTCUT( SNAP_BOTTOMRIGHT, C(A(KC_K)),      KC_NO,        KC_NO )       // Snap to bottom right quadrant of screen

DEFINE_SHORTCUT( SNAP_VERTICAL,    S(C(A(KC_UP))),  S(G(KC_UP)),  KC_NO )       // Snap vertical i.e. maximize height

DEFINE_SHORTCUT( SNAP_LEFTTHIRD,   C(A(KC_D)),  KC_NO,     KC_NO )       // Snap to left third of screen
DEFINE_SHORTCUT( SNAP_RIGHTTHIRD,  C(A(KC_G)),  KC_NO,     KC_NO )       // Snap to right third of screen

DEFINE_SHORTCUT( SNAP_LEFTQUARTER,   C(A(KC_Q)),    KC_NO,     KC_NO )       // Snap to left quarter of screen
DEFINE_SHORTCUT( SNAP_RIGHTQUARTER,  S(C(A(KC_Q))), KC_NO,     KC_NO )       // Snap to right quarter of screen

DEFINE_SHORTCUT( SNAP_LEFTTWOTHIRDS,   C(A(KC_E)),  KC_NO,     KC_NO )       // Snap to left two-thirds of screen
DEFINE_SHORTCUT( SNAP_MIDTWOTHIRDS,    C(A(KC_X)),  KC_NO,     KC_NO )       // Snap to middle two-thirds of screen
DEFINE_SHORTCUT( SNAP_RIGHTTWOTHIRDS,  C(A(KC_T)),  KC_NO,     KC_NO )       // Snap to right two-thirds of screen

/**
 * Window/tab navigation
 */
DEFINE_SHORTCUT( NEXT_WINDOW,     G(KC_GRAVE),     A(KC_ESC),       A(KC_ESC) )     // Next window of same app
DEFINE_SHORTCUT( PREV_WINDOW,     S(G(KC_GRAVE)),  S(A(KC_ESC)),    S(A(KC_ESC)) )  // Previous window of same app
DEFINE_SHORTCUT( TAB_RIGHT,       G(KC_RCBR),      C(KC_TAB),       C(KC_TAB) )     // Move to tab on right
DEFINE_SHORTCUT( TAB_LEFT,        G(KC_LCBR),      S(C(KC_TAB)),    S(C(KC_TAB)) )  // Move to tab on left


/**
 * Searching, moving forward and back
 */
DEFINE_SHORTCUT( NEXT_SEARCH,     G(KC_G),     KC_F3,        KC_F3 )         // Next search result
DEFINE_SHORTCUT( PREV_SEARCH,     S(G(KC_G)),  S(KC_F3),     S(KC_F3) )      // Previous search result
DEFINE_SHORTCUT( BROWSER_BACK,    G(KC_LBRC),  A(KC_LEFT),   A(KC_LEFT) )    // Go back one page
DEFINE_SHORTCUT( BROWSER_FWD,     G(KC_RBRC),  A(KC_RIGHT),  A(KC_RIGHT) )   // Go forward one page


/**
 * Selection/cut/copy/paste/undo
 */
DEFINE_SHORTCUT( SELECT_ALL,  G(KC_A),      C(KC_A),    C(KC_A) )     // Select all
DEFINE_SHORTCUT( CUT,         G(KC_X),      C(KC_X),    C(KC_X) )     // Cut
DEFINE_SHORTCUT( COPY,        G(KC_C),      C(KC_C),    C(KC_C) )     // Copy
DEFINE_SHORTCUT( PASTE,       G(KC_V),      C(KC_V),    C(KC_V) )     // Paste
DEFINE_SHORTCUT( UNDO,        G(KC_Z),      C(KC_Z),    C(KC_Z) )     // Undo
DEFINE_SHORTCUT( REDO,        S(G(KC_Z)),   C(KC_Y),    S(C(KC_Z)) )  // Redo


/**
 * Zooming
 */
DEFINE_SHORTCUT( APP_ZOOM_IN,       G(KC_EQL),       C(KC_EQL),    C(KC_EQL) )     // Application zoom in
DEFINE_SHORTCUT( APP_ZOOM_OUT,      G(KC_MINS),      C(KC_MINS),   C(KC_MINS) )    // Application zoom out
DEFINE_SHORTCUT( APP_ZOOM_RESET,    G(KC_0),         C(KC_0),      C(KC_0) )       // Application zoom default

DEFINE_SHORTCUT( SCR_ZOOM_IN,       A(G(KC_EQL)),    G(KC_EQL),    G(KC_EQL) )     // Screen zoom in (needs to be enabled in Accessibility)
DEFINE_SHORTCUT( SCR_ZOOM_OUT,      A(G(KC_MINS)),   G(KC_MINS),   G(KC_MINS) )    // Screen zoom out
DEFINE_SHORTCUT( SCR_ZOOM_RESET,    A(G(KC_8)),      KC_NO,        G(KC_0) )       // Screen zoom default FIXME


/**
 * Screenshots - may need additional OS-specific code
 */
DEFINE_SHORTCUT( SCREENSHOT_SCREEN,   S(G(KC_3)),   G(KC_PSCR),   G(KC_PSCR) )  // Take whole screen
DEFINE_SHORTCUT( SCREENSHOT_REGION,   S(G(KC_4)),   G(S(KC_S)),   KC_NO )       // Start screenshot of region
DEFINE_SHORTCUT( SCREENSHOT_APP,      S(G(KC_5)),   G(S(KC_S)),   KC_NO )       // Start screen shot app


/**
 * Common file and window operations
 */
DEFINE_SHORTCUT( OPEN,        G(KC_O),     C(KC_O),    C(KC_O) )    // Open file
DEFINE_SHORTCUT( CLOSE_TAB,   G(KC_W),     C(KC_W),    C(KC_W) )    // Close tab
DEFINE_SHORTCUT( QUIT,        G(KC_Q),     A(KC_F4),   A(KC_F4) )   // Quit app
DEFINE_SHORTCUT( NEW,         G(KC_N),     C(KC_N),    C(KC_N) )    // New file/window
DEFINE_SHORTCUT( NEW_TAB,     G(KC_T),     C(KC_T),    C(KC_T) )    // New tab

DEFINE_SHORTCUT( RELOAD,      G(KC_R),     C(KC_R),    C(KC_R) )    // Reload file/page
DEFINE_SHORTCUT( SAVE,        G(KC_S),     C(KC_N),    C(KC_N) )    // Save file
DEFINE_SHORTCUT( SAVE_AS,     S(G(KC_S)),  KC_F12,     C(S(KC_S)) ) // Save to different file
DEFINE_SHORTCUT( PRINT,       G(KC_P),     C(KC_P),    C(KC_P) )    // Print
DEFINE_SHORTCUT( FIND,        G(KC_F),     C(KC_F),    C(KC_F) )    // Find/search
DEFINE_SHORTCUT( BIN,         G(KC_BSPC),  C(KC_D) ,   C(KC_D)  )   // Delete item in Finder/Explorer


/**
 * System control
 */
DEFINE_SHORTCUT( SEARCH,        G(KC_SPC),      KC_LGUI,    KC_LGUI )    // Run application/search system
DEFINE_SHORTCUT( SCREEN_LOCK,   C(G(KC_Q)),     G(KC_L),    G(KC_L)   )  // Lock screen
DEFINE_SHORTCUT( SYSTEM_SLEEP,  A(G(KC_EJCT)),  KC_SLEP,    KC_SLEP   )  // System sleep


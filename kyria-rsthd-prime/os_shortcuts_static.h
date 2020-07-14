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

#pragma once

/**
 * Platform-dependent shortcuts.
 */

// Start and end markers
//
#define MAC_SC_ID_START KC_NO
#define MAC_SC_ID_END   KC_NO

#define WIN_SC_ID_START KC_NO
#define WIN_SC_ID_END   KC_NO


// Moving the cursor
//
#define MAC_SC_WORD_LEFT     A(KC_LEFT)    // Move word left
#define MAC_SC_WORD_RIGHT    A(KC_RIGHT)   // Move word right

#define MAC_SC_START_OF_LINE G(KC_LEFT)     // Move to start of line
#define MAC_SC_END_OF_LINE   G(KC_RIGHT)    // Move to end of line

#define MAC_SC_START_OF_PARA A(KC_UP)       // Move to start of paragraph (or up one)
#define MAC_SC_END_OF_PARA   A(KC_DOWN)     // Move to end of paragraph (or down one)

#define MAC_SC_START_OF_DOC  G(KC_UP)       // Move to start of document
#define MAC_SC_END_OF_DOC    G(KC_DOWN)     // Move to end of document


#define WIN_SC_WORD_LEFT     C(KC_LEFT)    // Move word left
#define WIN_SC_WORD_RIGHT    C(KC_RIGHT)   // Move word right

#define WIN_SC_START_OF_LINE KC_HOME       // Move to start of line
#define WIN_SC_END_OF_LINE   KC_END        // Move to end of line

#define WIN_SC_START_OF_PARA C(KC_UP)      // Move to start of paragraph (or up one)
#define WIN_SC_END_OF_PARA   C(KC_DOWN)    // Move to end of paragraph (or down one)

#define WIN_SC_START_OF_DOC  C(KC_HOME)    // Move to start of document
#define WIN_SC_END_OF_DOC    C(KC_END)     // Move to end of document


// Deletion
//
#define MAC_SC_DEL_WORD_LEFT  A(KC_BSPC)    // Delete word left
#define MAC_SC_DEL_WORD_RIGHT A(KC_DEL)     // Delete word right

#define WIN_SC_DEL_WORD_LEFT  C(KC_BSPC)    // Delete word left
#define WIN_SC_DEL_WORD_RIGHT C(KC_DEL)     // Delete word right


// Searching, moving forward and back
#define MAC_SC_NEXT_SEARCH  G(KC_G)      // Next search result
#define MAC_SC_PREV_SEARCH  S(G(KC_G))   // Previous search result

#define MAC_SC_BROWSER_BACK G(KC_LBRC)   // Go back one page
#define MAC_SC_BROWSER_FWD  G(KC_RBRC)   // Go forward one page


#define WIN_SC_NEXT_SEARCH  KC_F3        // Next search result
#define WIN_SC_PREV_SEARCH  S(KC_F3)     // Previous search result

#define WIN_SC_BROWSER_BACK A(KC_LEFT)   // Go back one page
#define WIN_SC_BROWSER_FWD  A(KC_RIGHT)  // Go forward one page


// Selection/cut/copy/paste/undo
//
#define MAC_SC_SELECT_ALL      G(KC_A)   // Select all
#define MAC_SC_CUT_SELECTION   G(KC_X)   // Cut/copy/paste
#define MAC_SC_COPY_SELECTION  G(KC_C)
#define MAC_SC_PASTE_CLIPBOARD G(KC_V)
#define MAC_SC_UNDO_ACTION     G(KC_Z)    // Undo
#define MAC_SC_REDO_ACTION     S(G(KC_Z)) // Redo

#define WIN_SC_SELECT_ALL      C(KC_A)    // Select all
#define WIN_SC_CUT_SELECTION   C(KC_X)    // Cut/copy/paste
#define WIN_SC_COPY_SELECTION  C(KC_C)
#define WIN_SC_PASTE_CLIPBOARD C(KC_V)
#define WIN_SC_UNDO_ACTION     C(KC_Z)    // Undo
#define WIN_SC_REDO_ACTION     C(KC_Y)    // Redo

// App switcher
//
#define MAC_SC_APPSWITCH_START KC_LGUI         // Start app switcher
#define MAC_SC_APPSWITCH_RIGHT KC_TAB          // Next application
#define MAC_SC_APPSWITCH_LEFT  S(KC_TAB)       // Previous application

#define WIN_SC_APPSWITCH_START KC_LALT         // Start app switcher
#define WIN_SC_APPSWITCH_RIGHT KC_TAB          // Next application
#define WIN_SC_APPSWITCH_LEFT  S(KC_TAB)       // Previous application


// Window/tab navigation
//
#define MAC_SC_NEXT_WINDOW G(KC_GRAVE)     // Next application window
#define MAC_SC_PREV_WINDOW S(G(KC_GRAVE))  // Previous application window

#define MAC_SC_TAB_RIGHT C(KC_TAB)       // Move to next tab
#define MAC_SC_TAB_LEFT  S(C(KC_TAB))    // Move to previous tab

#define MAC_SC_TAB_RIGHT_ALT A(G(KC_RIGHT)) // Move to next tab, alternate version
#define MAC_SC_TAB_LEFT_ALT  A(G(KC_LEFT))  // Move to previous tab, alternate version


#define WIN_SC_NEXT_WINDOW A(KC_ESC)     // Next application window
#define WIN_SC_PREV_WINDOW S(A(KC_ESC))  // Previous application window

#define WIN_SC_TAB_RIGHT C(KC_TAB)       // Move to next tab
#define WIN_SC_TAB_LEFT  S(C(KC_TAB))    // Move to previous tab

#define WIN_SC_TAB_RIGHT_ALT WIN_SC_TAB_RIGHT  // Same as above
#define WIN_SC_TAB_LEFT_ALT  WIN_SC_TAB_LEFT


// Zooming
//
#define MAC_SC_APP_ZOOM_IN    G(KC_EQL)     // Application zoom in
#define MAC_SC_APP_ZOOM_OUT   G(KC_MINS)    // Application zoom out
#define MAC_SC_APP_ZOOM_RESET G(KC_0)       // Application zoom default
#define MAC_SC_SCR_ZOOM_IN    A(G(KC_EQL))  // Screen zoom in (needs to be enabled in Accessibility)
#define MAC_SC_SCR_ZOOM_OUT   A(G(KC_MINS)) // Screen zoom out screen
#define MAC_SC_SCR_ZOOM_RESET A(G(KC_8))    // Screen zoom default

#define WIN_SC_APP_ZOOM_IN    C(KC_EQL)     // Application zoom in
#define WIN_SC_APP_ZOOM_OUT   C(KC_MINS)    // Application zoom out
#define WIN_SC_APP_ZOOM_RESET C(KC_0)       // Application zoom default
#define WIN_SC_SCR_ZOOM_IN    G(KC_EQL)     // Screen zoom in
#define WIN_SC_SCR_ZOOM_OUT   G(KC_MINS)    // Screen zoom out
#define WIN_SC_SCR_ZOOM_RESET G(KC_MINS)    // not useful, really want Screen zoom default


// Screenshots - may need additional code
//
#define MAC_SC_SHOT_SCREEN S(G(KC_3))  // Take whole screen and save to file
#define MAC_SC_SHOT_REGION S(G(KC_4))  // Then drag-select region

#define WIN_SC_SHOT_SCREEN G(KC_PSCR)  // Take whole screen and save to file
#define WIN_SC_SHOT_REGION G(S(KC_S))  // Start Snip & Sketch


// Window management
//
#define MAC_SC_EXPOSE_ALL  C(KC_UP)        // Expose all windows and desktops
#define MAC_SC_NEXT_SCREEN C(KC_RIGHT)     // Move to next screen
#define MAC_SC_PREV_SCREEN C(KC_LEFT)      // Move to previous screen
#define MAC_SC_FULLSCREEN  G(C(KC_F))      // Toggle window to/from full-screen

#define MAC_SC_EXPOSE_WINDOWS C(KC_DOWN)   // Expose windows of current app
#define MAC_SC_NEXT_APP       KC_TAB       // Next application while in Mission Control
#define MAC_SC_PREV_APP       S(KC_TAB)    // Previous application

#define MAC_SC_REVEAL_DESKTOP KC_F11       // Reveal desktop


#define WIN_SC_EXPOSE_ALL  G(KC_TAB)       // Expose all windows
#define WIN_SC_NEXT_SCREEN G(C(KC_RIGHT))  // Move to next screen
#define WIN_SC_PREV_SCREEN G(C(KC_LEFT))   // Move to previous screen
#define WIN_SC_FULLSCREEN  KC_F11          // Toggle full-screen

#define WIN_SC_EXPOSE_WINDOWS G(A(KC_TAB)) // Expose app windows (like alt-tab but persistent)
#define WIN_SC_NEXT_APP       KC_NO        // Does nothing FIXME
#define WIN_SC_PREV_APP       KC_NO

#define WIN_SC_REVEAL_DESKTOP G(KC_D)      // Reveal desktop


// System control
//
#define MAC_SC_SCREEN_LOCK   C(G(KC_Q))     // Lock screen
#define MAC_SC_SYSTEM_SLEEP  A(G(KC_EJCT))  // System sleep

#define WIN_SC_SCREEN_LOCK   G(KC_L)        // Lock screen
#define WIN_SC_SYSTEM_SLEEP  KC_SLEP        // System sleep


/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//----------------------------------------------------------------------------
// ergohaven
//----------------------------------------------------------------------------

// translate from Ergohaven DM 5x6 (which the QMK Configurator knows as 5x6_5)
// by discarding the bottom two keys in the thumb clusters (L54,L52 & R53,R51)
#define LAYOUT_5x6_5( \
    L00, L01, L02, L03, L04, L05,                          R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                          R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                          R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35,                          R30, R31, R32, R33, R34, R35, \
              L42, L43,      L44, L55, L53,      R52, R50, R41,      R42, R43, \
                                  L54, L52,      R53, R51 \
) \
LAYOUT_5x6( \
    L00, L01, L02, L03, L04, L05,                          R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                          R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                          R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35,                          R30, R31, R32, R33, R34, R35, \
         L42, L43,                                                   R42, R43,           \
                   L44, L55, L53,                          R52, R50, R41                 \
)

// #define RGBLED_NUM DRIVER_LED_TOTAL // from ../../../remnant/config.h
#define RGB_MATRIX_LED_COUNT DRIVER_LED_TOTAL // from ../../../remnant/config.h

// RGB indicators on split keyboards will require state information synced to the slave half (e.g. #define SPLIT_LAYER_STATE_ENABLE). See data sync options for more details.
// https://docs.qmk.fm/#/feature_split_keyboard?id=data-sync-options
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// Remove the spread effect entirely.
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effect-typing-heatmap
#define RGB_MATRIX_TYPING_HEATMAP_SLIM

// Gradient mode will loop through the color wheel hues over time and its duration can be controlled with the effect speed keycodes (RGB_SPI/RGB_SPD).
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effect-solid-reactive
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

// https://github.com/qmk/qmk_firmware/issues/18511#issuecomment-1264604610
// https://github.com/qmk/qmk_firmware/issues/8990#issuecomment-851055637
#undef SPLIT_USB_DETECT

//----------------------------------------------------------------------------
// getreuer
//----------------------------------------------------------------------------

#define CAPS_WORD_TOGGLE_KEY
#define CAPS_WORD_INVERT_ON_SHIFT

//----------------------------------------------------------------------------
// home row mods
//----------------------------------------------------------------------------
// https://sunaku.github.io/home-row-mods.html
// https://github.com/manna-harbour/qmk_firmware/pull/56
// https://github.com/manna-harbour/qmk_firmware/issues/29

/* QMK */
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT /* for rolling on mod-tap keys */

/* Miryoku */
#define BILATERAL_COMBINATIONS
#define BILATERAL_COMBINATIONS_LIMIT_CHORD_TO_N_KEYS 4 /* GUI, Alt, Ctrl, Shift */
#define BILATERAL_COMBINATIONS_DELAY_MODS_THAT_MATCH MOD_MASK_GUI
#define BILATERAL_COMBINATIONS_DELAY_MATCHED_MODS_BY 120  /* ms */
#define BILATERAL_COMBINATIONS_ALLOW_CROSSOVER_AFTER 80  /* ms */
#define BILATERAL_COMBINATIONS_ALLOW_SAMESIDED_AFTER 3000 /* ms */
#define BILATERAL_COMBINATIONS_TYPING_STREAK_TIMEOUT 160 /* ms */
#define BILATERAL_COMBINATIONS_TYPING_STREAK_MODMASK (~MOD_MASK_SHIFT)

//----------------------------------------------------------------------------
// vial
//----------------------------------------------------------------------------
#ifdef VIAL_ENABLE

// run `python3 ~/qmk_firmware/util/build_id.py` to generate this
#define BUILD_ID ((uint32_t)0x000A8B54)

#endif

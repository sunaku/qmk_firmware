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

#define USE_SERIAL

#define MASTER_LEFT
//#define MASTER_RIGHT

//#define EE_HANDS

//----------------------------------------------------------------------------
// ergohaven
//----------------------------------------------------------------------------
// https://github.com/kissetfall/qmk_firmware/blob/master/keyboards/handwired/dactyl_manuform/5x6/keymaps/eh/config.h

/*** NOTE: these are defined above in handwired/dactyl_manuform/5x6/config.h
 * so we must undefine them to avoid avr-gcc 11.2.0 stopping us on -Werror */
#undef RGB_DI_PIN
#undef RGBLED_NUM

// Underglow
#define RGB_DI_PIN D1
#define RGBLED_NUM 18
#define RGBLED_SPLIT { 9, 9 }
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 150
#define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

//----------------------------------------------------------------------------
// home row mods
//----------------------------------------------------------------------------
// https://sunaku.github.io/home-row-mods.html
// https://github.com/manna-harbour/qmk_firmware/pull/56
// https://github.com/manna-harbour/qmk_firmware/issues/29


/* QMK */
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT /* for rolling on mod-tap keys */
#define PERMISSIVE_HOLD /* for quicker layers & mods activation */

/* Miryoku */
#define BILATERAL_COMBINATIONS
#define BILATERAL_COMBINATIONS_DELAY_MODS_THAT_MATCH MOD_MASK_GUI
#define BILATERAL_COMBINATIONS_DELAY_MATCHED_MODS_BY 100  /* ms */
#define BILATERAL_COMBINATIONS_ALLOW_CROSSOVER_AFTER 75   /* ms */
#define BILATERAL_COMBINATIONS_ALLOW_SAMESIDED_AFTER 3000 /* ms */

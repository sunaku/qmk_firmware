#include "features/caps_word.h"
#include "features/select_word.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_caps_word(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELECT_WORD)) { return false; }
    // Your macros ...

    // handle sticky holding of Miryoku thumb cluster layer-taps as toggles
    if (keycode == STICKY_LAYER_TOGGLE && record->event.pressed) {
        default_layer_set(default_layer_state ? 0 : (1 << get_highest_layer(layer_state)));
    }

    return true;
}

//----------------------------------------------------------------------------
// per-key color indicators for layers and modifiers
//----------------------------------------------------------------------------

void keyboard_post_init_user(void) {
    // https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
    // set initial effect on keyboard start; ignore what's in EEPROM!
    rgb_matrix_mode_noeeprom(
      // RGB_MATRIX_TYPING_HEATMAP
      RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    );

    /*
    // https://docs.qmk.fm/#/feature_rgb_matrix?id=indicators-without-rgb-matrix-effect
    //
    // Indicators without RGB Matrix Effect
    //
    // If you want to just use RGB indicators without RGB matrix effect, it is not
    // possible to disable the latter because toggling RGB off will disable
    // everything. You can workaround it with solid effect and colors off using
    // this init function:
    //
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    // rgb_matrix_sethsv_noeeprom(HSV_OFF); // XXX: this throws away the color!
    HSV hsv = rgb_matrix_get_hsv();
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, 0); // turn off, preserving color
    */
}

// dim indicator colors by this much (default is MAX brightness!)
#define DIM_BY 2
#define DIMMED(rgb_color) DIMMED_(rgb_color)
#define DIMMED_(r, g, b) ((r)/DIM_BY), ((g)/DIM_BY), ((b)/DIM_BY)

#define INDEX_FINGER_COLOR  DIMMED(RGB_YELLOW)
#define MIDDLE_FINGER_COLOR DIMMED(RGB_GREEN)
#define RING_FINGER_COLOR   DIMMED(RGB_CYAN)
#define PINKY_FINGER_COLOR  DIMMED(RGB_MAGENTA)
#define LEFT_THUMB_COLOR    DIMMED(RGB_RED)
#define RIGHT_THUMB_COLOR   DIMMED(RGB_PURPLE)
#define EXTRA_LAYER_COLOR   DIMMED(RGB_BLUE)
#define CAPS_LOCK_COLOR     DIMMED(RGB_BLUE)
#define CAPS_WORD_COLOR     DIMMED(RGB_SPRINGGREEN)

// see ../../../remnant/remnant.c
static const uint8_t
    // { 25, 18, 17,  8,  7,  0 }, // { 29, 36, 37, 46, 47, 54 },
    // { 24, 19, 16,  9,  6,  1 }, // { 30, 35, 38, 45, 48, 53 },
    // { 23, 20, 15, 10,  5,  2 }, // { 31, 34, 39, 44, 49, 52 },
    // { 22, 21, 14, 11,  4,  3 }, // { 32, 33, 40, 43, 50, 51 },
    // { __, __, 13, 12, __, __ }, // { __, __, 41, 42, __, __ },
    // { __, __, __, 26, 27, 28 }, // { 57, 56, 55, __, __, __ }
    LEFT_INDEX_FINGER_HOME   = 7,  RIGHT_INDEX_FINGER_HOME   = 36,
    LEFT_MIDDLE_FINGER_HOME  = 8,  RIGHT_MIDDLE_FINGER_HOME  = 37,
    LEFT_RING_FINGER_HOME    = 17, RIGHT_RING_FINGER_HOME    = 46,
    LEFT_PINKY_FINGER_HOME   = 18, RIGHT_PINKY_FINGER_HOME   = 47,
    LEFT_THUMB_CLUSTER_HOME  = 1,  RIGHT_THUMB_CLUSTER_HOME  = 30,
    LEFT_THUMB_CLUSTER_INNER = 2,  RIGHT_THUMB_CLUSTER_INNER = 31,
    LEFT_THUMB_CLUSTER_OUTER = 3,  RIGHT_THUMB_CLUSTER_OUTER = 32,
    LEFT_CAPS_LOCK           = 0,  RIGHT_CAPS_LOCK           = 29;

// https://docs.qmk.fm/#/feature_caps_word?id=representing-caps-word-state
static bool is_caps_word_active = false;
void caps_word_set_user(bool active) {
  is_caps_word_active = active;
  // TODO: add this to "split transport" payload
}

// https://qmk.github.io/qmk_mkdocs/master/en/feature_rgb_matrix/#indicator-examples
#ifdef VIAL_ENABLE
  void
#else
  bool
#endif
rgb_matrix_indicators_user(void) {

    uint8_t mods = get_mods();

    if (mods & MOD_MASK_SHIFT) {
        rgb_matrix_set_color( LEFT_INDEX_FINGER_HOME, INDEX_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_INDEX_FINGER_HOME, INDEX_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_INDEX_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_INDEX_FINGER_HOME, RGB_OFF);
    }

    if (mods & MOD_MASK_CTRL) {
        rgb_matrix_set_color( LEFT_MIDDLE_FINGER_HOME, MIDDLE_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_MIDDLE_FINGER_HOME, MIDDLE_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_MIDDLE_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_MIDDLE_FINGER_HOME, RGB_OFF);
    }

    if (mods & MOD_MASK_ALT) {
        rgb_matrix_set_color( LEFT_RING_FINGER_HOME, RING_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_RING_FINGER_HOME, RING_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_RING_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_RING_FINGER_HOME, RGB_OFF);
    }

    if (mods & MOD_MASK_GUI) {
        rgb_matrix_set_color( LEFT_PINKY_FINGER_HOME, PINKY_FINGER_COLOR);
        rgb_matrix_set_color(RIGHT_PINKY_FINGER_HOME, PINKY_FINGER_COLOR);
    }
    else {
        rgb_matrix_set_color( LEFT_PINKY_FINGER_HOME, RGB_OFF);
        rgb_matrix_set_color(RIGHT_PINKY_FINGER_HOME, RGB_OFF);
    }

    switch (get_highest_layer(layer_state|default_layer_state)) {
        case 1:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  LEFT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  LEFT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 2:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, LEFT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, LEFT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 3:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, LEFT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, LEFT_THUMB_COLOR);
            break;

        case 4:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RIGHT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RIGHT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 5:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RIGHT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RIGHT_THUMB_COLOR);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;

        case 6:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RIGHT_THUMB_COLOR);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RIGHT_THUMB_COLOR);
            break;

        default:
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME,  RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, RGB_OFF);
            rgb_matrix_set_color( LEFT_THUMB_CLUSTER_OUTER, RGB_OFF);
            rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_OUTER, RGB_OFF);
            break;
    }

    if (IS_LAYER_ON(7)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_INNER, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_INNER, EXTRA_LAYER_COLOR);
    }

    if (IS_LAYER_ON(8)) {
        rgb_matrix_set_color( LEFT_THUMB_CLUSTER_HOME, EXTRA_LAYER_COLOR);
        rgb_matrix_set_color(RIGHT_THUMB_CLUSTER_HOME, EXTRA_LAYER_COLOR);
    }

    if (host_keyboard_led_state().caps_lock) {
      rgb_matrix_set_color( LEFT_CAPS_LOCK, CAPS_LOCK_COLOR);
      rgb_matrix_set_color(RIGHT_CAPS_LOCK, CAPS_LOCK_COLOR);
    }
    else if (is_caps_word_active) {
      rgb_matrix_set_color( LEFT_CAPS_LOCK, CAPS_WORD_COLOR);
      rgb_matrix_set_color(RIGHT_CAPS_LOCK, CAPS_WORD_COLOR);
    }
    else {
      rgb_matrix_set_color( LEFT_CAPS_LOCK, RGB_OFF);
      rgb_matrix_set_color(RIGHT_CAPS_LOCK, RGB_OFF);
    }

#ifndef VIAL_ENABLE
    return true;
#endif
}

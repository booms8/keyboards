// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _LW 1
#define _RS 2
#define _SS 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = { /* Qwerty */
        {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
        {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
        {F(3),    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, F(2)   },
        {M(0),    KC_LCTL, KC_LALT, KC_LGUI, MO(_LW), F(1),    F(1),    MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
    },
    [_RS] = { /* RAISE */
        {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
        {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
        {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
        {RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
    },
    [_LW] = { /* LOWER */
        {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
        {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
        {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
        {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
    },
    [_SS] = { /* UNIX SHELL */
        {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(5),    M(6),    M(7),    M(8),    KC_TRNS},
        {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(1),    M(2),    M(3),    M(4),    KC_TRNS},
        {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(9),    M(10),   KC_TRNS, KC_TRNS, KC_TRNS},
        {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
    }
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_KEY(_SS, KC_SPC),
    [2] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
    [3] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ENT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
        } else {
            unregister_code(KC_RSFT);
        }
        break;

        //SHELL MACROS
        //ls
        case 1:
            return MACRODOWN(TYPE(KC_L), TYPE(KC_S), TYPE(KC_ENT), END);
            break;
        //la
        case 2:
            return MACRODOWN(TYPE(KC_L), TYPE(KC_A), TYPE(KC_ENT), END);
            break;
        //cd ../
        case 3:
            return MACRODOWN(TYPE(KC_C), TYPE(KC_D), TYPE(KC_SPC), TYPE(KC_DOT), TYPE(KC_DOT), TYPE(KC_SLSH), TYPE(KC_ENT), END);
            break;
        //cd ~
        case 4:
            return MACRODOWN(TYPE(KC_C), TYPE(KC_D), TYPE(KC_SPC), DOWN(KC_LSFT), TYPE(KC_TILD), UP(KC_LSFT), TYPE(KC_ENT), END);
            break;
        //ls...
        case 5:
            return MACRODOWN(TYPE(KC_L), TYPE(KC_S), TYPE(KC_SPC), END);
            break;
        //cd...
        case 6:
            return MACRODOWN(TYPE(KC_C), TYPE(KC_D), TYPE(KC_SPC), END);
            break;
        //sudo...
        case 7:
            return MACRODOWN(TYPE(KC_S), TYPE(KC_U), TYPE(KC_D), TYPE(KC_O), TYPE(KC_SPC), END);
            break;
        //git...
        case 8:
            return MACRODOWN(TYPE(KC_G), TYPE(KC_I), TYPE(KC_T), TYPE(KC_SPC), END);
            break;
        //git add -A
        case 9:
            return MACRODOWN(TYPE(KC_G), TYPE(KC_I), TYPE(KC_T), TYPE(KC_SPC), TYPE(KC_A), TYPE(KC_D), TYPE(KC_D), TYPE(KC_SPC), TYPE(KC_MINS), DOWN(KC_LSFT), TYPE(KC_A), UP(KC_LSFT), TYPE(KC_ENT), END);
            break;
        //git commit
        case 10:
            return MACRODOWN(TYPE(KC_G), TYPE(KC_I), TYPE(KC_T), TYPE(KC_SPC), TYPE(KC_C), TYPE(KC_O), TYPE(KC_M), TYPE(KC_M), TYPE(KC_I), TYPE(KC_T), TYPE(KC_SPC), TYPE(KC_MINS), TYPE(KC_M), TYPE(KC_SPC), DOWN(KC_LSFT), TYPE(KC_QUOT), TYPE(KC_QUOT), UP(KC_LSFT), TYPE(KC_LEFT), END);
            break;
      }
    return MACRO_NONE;
};

/* Copyright 2015-2017 Jack Humbert
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
#include QMK_KEYBOARD_H
#include "solidtux.h"
#include "muse.h"
#include <virtser.h>
#include <print.h>

#define ESCAPE MT(MOD_RALT, KC_ESC)
#define LSHIFT MT(MOD_LSFT, KC_BSLS)
#define RSHIFT MT(MOD_RSFT, KC_ENT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    ESCAPE,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LSHIFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSHIFT,
    NUMPAD,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  KC_INS,
    _______, _______, _______, _______, _______, HALF_SP, HALF_SP, _______,    KC_MUTE,    KC_VOLD, KC_VOLU, KC_MPLY
),
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_INS,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, _______, _______, KC_MNXT
),
[_ADJUST] = LAYOUT_planck_grid(
    SCREENS, _______, AU_ON,   AU_OFF,  _______, RGBANIM, IMAGE,   LED_LEV, _______, _______, _______, KC_DEL,
    KC_WFAV, _______, MI_ON,   MI_OFF,  _______, COLOR,   HEATMAP, RGB_TOG, RGB_VAI, RGB_VAD, _______, RESET,
    KC_CAPS, _______, MU_ON,   MU_OFF,  MU_MOD,  _______, _______, RGB_MOD, RGB_HUI, RGB_HUD, _______, _______,
    DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_NUMPAD] = LAYOUT_planck_grid(
    QWERTY,  EMOJI1,  EMOJI2,  EMOJI3,  EMOJI4,  _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______,
    GAME,    EMOJI5,  EMOJI6,  EMOJI7,  EMOJI8,  _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, KC_NUMLOCK,
    GAMEARR, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PAST, _______,
    _______, _______, _______, _______, _______,  _______, _______, KC_KP_0, KC_PDOT, KC_PEQL, KC_PSLS, _______
),
[_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    ESCAPE,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSHIFT,KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    NUMPAD,  KC_LCTL, KC_LALT, KC_LGUI, RAISE,   KC_SPC,  KC_SPC,  RAISE,   _______, _______, KC_F3,   KC_MAIL
),
[_GAME_ARROW] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_UP,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    ESCAPE,  KC_LEFT, KC_DOWN, KC_RGHT, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSHIFT,KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    NUMPAD,  KC_LCTL, KC_LALT, KC_LGUI, RAISE,   KC_SPC,  KC_SPC,  RAISE,   _______, _______, KC_F3,   KC_MAIL
)
};

uint8_t PROGMEM numpad_mask[47] = {
    0,1,1,1,1,0,0,2,2,2,6,0,
    0,1,1,1,0,0,0,2,2,2,6,2,
    0,0,0,0,0,0,0,2,2,2,6,0,
    0,0,0,0,0,0,  2,1,1,6,0
};

uint8_t PROGMEM game_mask[47] = {
    0,0,2,0,0,0,0,0,0,0,0,0,
    0,2,2,2,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,  0,0,0,0,0
};

uint8_t PROGMEM game_arrow_mask[47] = {
    0,0,4,0,0,0,0,0,0,0,0,0,
    0,4,4,4,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,  0,0,0,0,0
};
// clang-format on

layer_state_t layer_state_set_keyboard(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

uint8_t* rgb_matrix_mask_kb(uint8_t default_layer, uint8_t current_layer) {
    uint8_t* mask = 0;
    switch (default_layer) {
        case _GAME:
            mask = game_mask;
            break;
        case _GAME_ARROW:
            mask = game_arrow_mask;
            break;
    }
    switch (current_layer) {
        case _NUMPAD:
            mask = numpad_mask;
            break;
    }
    return mask;
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        planck_ez_left_led_on();
    } else {
        planck_ez_left_led_off();
    }
    if (led_state.num_lock) {
        planck_ez_right_led_on();
    } else {
        planck_ez_right_led_off();
    }
    return true;
}

bool process_record_keyboard(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LED_LEV:
            if (record->event.pressed) {
                keyboard_config.led_level++;
                if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                }
                planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4);
                planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4);
                eeconfig_update_kb(keyboard_config.raw);
                layer_state_set_kb(layer_state);
            }
            return false;
    }
    return true;
}
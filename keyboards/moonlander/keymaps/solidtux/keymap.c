/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"

#define ESCCTL RCTL_T(KC_ESC)
#define SHTAB S(KC_TAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LOWER,             LOWER,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    RAISE,             RAISE,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    GAME,              GAMEARR, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LGUI, KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,          KC_RALT,           ESCCTL,           KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_LGUI,
                                            KC_SPACE,KC_BSPC, KC_DEL,            SHTAB,   KC_TAB,  KC_ENT
    ),

    [_GAME] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LOWER,             LOWER,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    RAISE,             RAISE,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    QWERTY,            QWERTY, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LGUI, KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,          KC_RALT,           ESCCTL,           KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_LGUI,
                                            KC_SPACE,KC_BSPC, KC_DEL,            SHTAB,   KC_TAB,  KC_ENT
    ),

    [_GAME_ARROW] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LOWER,             LOWER,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        _______, KC_Q,    KC_UP,   KC_E,    KC_R,    KC_T,    RAISE,             RAISE,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_F,    KC_G,    QWERTY,            QWERTY,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LGUI, KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,          KC_RALT,           ESCCTL,           KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_LGUI,
                                            KC_SPACE,KC_BSPC, KC_DEL,            SHTAB,   KC_TAB,  KC_ENT
    ),

    [_LOWER] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, EMOJI1,  EMOJI2,  EMOJI3,  EMOJI4,  _______, _______,           _______, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        _______, EMOJI5,  EMOJI6,  EMOJI7,  EMOJI8,  _______, _______,           _______, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______, _______, _______, _______, _______, _______,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
        EEP_RST, _______, _______, _______, _______,          RGB_VAI,           RGB_TOG,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI,           _______, _______, _______
    ),

    [_RAISE] = LAYOUT_moonlander(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, RESET,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};
// clang-format on

bool process_record_keyboard(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LED_LEV:
            if (record->event.pressed) {
                keyboard_config.led_level = !keyboard_config.led_level;
                eeconfig_update_kb(keyboard_config.raw);
                layer_state_set_kb(layer_state);
            }
            return false;
    }
    return true;
}

bool led_update_user(led_t led_state) {
    if (layer_state_is(_LOWER)) {
        ML_LED_1(false);
        ML_LED_2(true);
        ML_LED_3(false);
    } else if (layer_state_is(_RAISE)) {
        ML_LED_1(false);
        ML_LED_2(false);
        ML_LED_3(true);
    } else {
        ML_LED_1(true);
        ML_LED_2(false);
        ML_LED_3(false);
    }
    ML_LED_4(led_state.caps_lock);
    ML_LED_5(led_state.num_lock);
    return true;
}
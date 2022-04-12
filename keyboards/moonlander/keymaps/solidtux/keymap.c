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
#define ESCALT RALT_T(KC_ESC)
#define SHTAB S(KC_TAB)
#define SF(N) S(KC_F##N)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_moonlander(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LOWER,             LOWER,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    RAISE,             RAISE,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        ESCALT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    NUMPAD,            GAME,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LEFT, KC_RGHT,          KC_RALT,           ESCCTL,           KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_BSLS,
                                            KC_SPACE,KC_BSPC, KC_DEL,            KC_TAB,  KC_DEL,  KC_ENT
    ),

    [_GAME] = LAYOUT_moonlander(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LOWER,             LOWER,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    RAISE,             RAISE,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        ESCALT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    NUMPAD,            GAMEARR, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LEFT, KC_RGHT,          KC_RALT,           ESCCTL,           KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_BSLS,
                                            KC_SPACE,KC_BSPC, KC_DEL,            SHTAB,   KC_TAB,  KC_ENT
    ),

    [_GAME_ARROW] = LAYOUT_moonlander(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LOWER,             LOWER,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_UP,   KC_E,    KC_R,    KC_T,    RAISE,             RAISE,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        ESCALT,  KC_LEFT, KC_DOWN, KC_RIGHT,KC_F,    KC_G,    NUMPAD,            QWERTY,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LEFT, KC_RGHT,          KC_RALT,           ESCCTL,           KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_BSLS,
                                            KC_SPACE,KC_BSPC, KC_DEL,            SHTAB,   KC_TAB,  KC_ENT
    ),

    [_LOWER] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______,           _______, KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,
        _______, EMOJI1,  EMOJI2,  EMOJI3,  EMOJI4,  _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, EMOJI5,  EMOJI6,  EMOJI7,  EMOJI8,  _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_HOME, KC_END,           _______,           RGB_TOG,          KC_PGUP, KC_PGDN, _______, _______, _______,
                                            IMAGE,   RGBANIM, RGB_RMOD,          RGB_MOD, COLOR,   HEATMAP
    ),
 
    [_RAISE] = LAYOUT_moonlander(
        _______, SF(1),   SF(2),   SF(3),   SF(4),   SF(5),   _______,           _______, SF(6),   SF(7),   SF(8),   SF(9),   SF(10),  SF(11),
        _______, SF(11),  SF(12),  SF(13),  SF(14),  SF(15),  _______,           _______, SF(16),  SF(17),  SF(18),  SF(19),  SF(20),  SF(21),
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          RESET,             EEP_RST,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [_NUMPAD] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, KC_NUM,  _______, _______, _______, RESET,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST, _______,
        _______, _______, _______, _______, _______, _______,                             _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PMNS, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          KC_KP_0, KC_DOT,  KC_EQL,  KC_PPLS, _______,
                                            _______, _______, _______,           _______, _______, KC_PENT
    ),
};

uint8_t PROGMEM game_mask[DRIVER_LED_TOTAL] = {
    0,0,0,0,0,
    0,0,2,0,0,
    0,2,2,0,0,
    0,0,2,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0,

    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0
};


uint8_t PROGMEM game_arrow_mask[DRIVER_LED_TOTAL] = {
    0,0,0,0,0,
    0,0,4,0,0,
    0,4,4,0,0,
    0,0,4,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0,

    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0
};

uint8_t PROGMEM lower_mask[DRIVER_LED_TOTAL] = {
    0,0,0,0,0,
    0,0,5,5,0,
    0,0,5,5,0,
    0,0,5,5,0,
    0,0,5,5,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0,

    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0
};

uint8_t PROGMEM raise_mask[DRIVER_LED_TOTAL] = {
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0,

    0,0,0,0,0,
    0,2,2,2,2,
    0,2,2,2,2,
    0,2,2,2,2,
    2,2,2,2,2,
    0,0,0,0,
    0,0,0,

    2,0,0,
    0
};

uint8_t PROGMEM adjust_mask[DRIVER_LED_TOTAL] = {
    3,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0,

    3,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,
    0,0,0,

    0,0,0,
    0
};
// clang-format on

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
        case _ADJUST:
            mask = adjust_mask;
            break;
        case _LOWER:
            mask = lower_mask;
            break;
        case _RAISE:
            mask = raise_mask;
            break;
    }
    return mask;
}

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

layer_state_t layer_state_set_keyboard(layer_state_t state) {
    switch (state) {
        case _ADJUST:
            ML_LED_1(false);
            ML_LED_2(true);
            ML_LED_3(true);
            break;
        case _LOWER:
            ML_LED_1(false);
            ML_LED_2(true);
            ML_LED_3(false);
            break;
        case _RAISE:
            ML_LED_1(false);
            ML_LED_2(false);
            ML_LED_3(true);
            break;
        default:
            ML_LED_1(true);
            ML_LED_2(false);
            ML_LED_3(false);
            break;
    }
    return state;
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
    } else if (layer_state_is(_ADJUST)) {
        ML_LED_1(false);
        ML_LED_2(true);
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
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
#include "muse.h"
#include <virtser.h>
#include <print.h>

enum planck_layers { _QWERTY, _GAME, _GAME_ARROW, _LOWER, _RAISE, _ADJUST, _NUMPAD, _MOUSE };

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLOR,
    HEATMAP,
    IMAGE,
    RGBANIM,
    LED_LEV,
    SCREENS,
    EMOJI1,
    EMOJI2,
    EMOJI3,
    EMOJI4,
    EMOJI5,
    EMOJI6,
    EMOJI7,
    EMOJI8,
    HALF_SP,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUMPAD TT(_NUMPAD)
#define GAME DF(_GAME)
#define GAMEARR DF(_GAME_ARROW)
#define QWERTY DF(_QWERTY)
#define MOUSE MO(_MOUSE)
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
    _______, _______, _______, _______, MOUSE,   _______, _______, KC_KP_0, KC_PDOT, KC_PEQL, KC_PSLS, _______
),
[_MOUSE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
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

uint8_t PROGMEM mouse_mask[47] = {
    0,0,0,0,0,0,0,0,2,2,2,0,
    0,0,0,0,0,0,0,0,2,2,2,2,
    0,0,0,0,0,0,0,0,2,2,2,2,
    0,0,0,0,0,0,  0,2,2,2,2
};
// clang-format on

uint8_t last_layer    = 0;
uint8_t current_layer = 0;
uint8_t default_layer = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
    state         = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    uint8_t layer = biton32(state);
    current_layer = layer;
    last_layer    = layer;
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    default_layer = layer;
    switch (layer) {
        case _GAME:
            rgb_matrix_config.mode = RGB_MATRIX_SPLASH;
            break;
        case _GAME_ARROW:
            rgb_matrix_config.mode = RGB_MATRIX_SPLASH;
            break;
        case _QWERTY:
            rgb_matrix_config.mode = RGB_MATRIX_STARTUP_MODE;
            break;
    }
    return state;
}

bool    progress_enable[4] = {false, false, false, false};
uint8_t progress[4]        = {0, 0, 0, 0};
RGB     progress_color[4]  = {
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
};

void rgb_matrix_indicators_kb(void) {
    uint8_t* mask = 0;
    if (rgb_matrix_config.mode == RGB_MATRIX_EFFECT_MAX) {
        return;
    }
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
        case _MOUSE:
            mask = mouse_mask;
            break;
    }
    bool cont = mask != 0;
    for (uint8_t i = 0; i < 4; i++) {
        cont = cont || progress_enable[i];
    }
    if (!cont) {
        return;
    }
    for (uint8_t i = 0; i < 47; i++) {
        uint8_t x = i % 12;
        uint8_t y = i / 12;
        if (y == 3 && x > 4) {
            x++;
        }
        if (mask != 0) {
            if (mask[i] > 0) {
                HSV hsv = rgb_matrix_config.hsv;
                hsv.h += (255 * mask[i]) / 8;
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        } else if (progress_enable[y]) {
            if (progress[y] > x) {
                rgb_matrix_set_color(i, progress_color[y].r, progress_color[y].g, progress_color[y].b);
            } else {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
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

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case IMAGE:
            if (record->event.pressed) {
                rgb_matrix_config.mode = RGB_MATRIX_CUSTOM_image;
            }
            return false;
        case RGBANIM:
            if (record->event.pressed) {
                rgb_matrix_config.mode = RGB_MATRIX_RAINBOW_MOVING_CHEVRON;
            }
            return false;
        case COLOR:
            if (record->event.pressed) {
                rgb_matrix_config.mode = RGB_MATRIX_ALPHAS_MODS;
            }
            return false;
        case HEATMAP:
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix_default();
            }
            return false;
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
        case SCREENS:
            if (record->event.pressed) {
                host_consumer_send(0x19E);
            } else {
                host_consumer_send(0);
            }
            return false;
        case EMOJI1:
            if (record->event.pressed) {
                send_unicode_string("🙂");
            }
            return false;
        case EMOJI2:
            if (record->event.pressed) {
                send_unicode_string("😉");
            }
            return false;
        case EMOJI3:
            if (record->event.pressed) {
                send_unicode_string("😂");
            }
            return false;
        case EMOJI4:
            if (record->event.pressed) {
                send_unicode_string("☺️");
            }
            return false;
        case EMOJI5:
            if (record->event.pressed) {
                send_unicode_string("🙈");
            }
            return false;
        case EMOJI6:
            if (record->event.pressed) {
                send_unicode_string("🤦");
            }
            return false;
        case EMOJI7:
            if (record->event.pressed) {
                send_unicode_string("🤷");
            }
            return false;
        case EMOJI8:
            if (record->event.pressed) {
                send_unicode_string("🎉");
            }
            return false;
        case HALF_SP:
            if (record->event.pressed) {
                send_unicode_string(" ");
            }
            return false;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
#else
            tap_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
#else
            tap_code(KC_PGUP);
#endif
        }
    }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}

void suspend_power_down_user(void) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }

typedef enum { CMD_NOP, CMD_RGB_MODE, CMD_COLOR, CMD_PIXEL, CMD_RGB_SAVE, CMD_RGB_RESTORE, CMD_PROGRESS, CMD_LAST } cmd_t;

uint8_t ser_buffer[256];
uint8_t ser_counter = 0;
uint8_t ser_length  = 0;
uint8_t ser_mode    = 10;

void virtser_recv(uint8_t c) {
    if (ser_counter == 0) {
        ser_length = c;
    } else {
        ser_buffer[ser_counter - 1] = c;
    }
    if (ser_counter == ser_length && ser_counter > 0) {
        cmd_t cmd = (cmd_t)ser_buffer[0];
        switch (cmd) {
            case CMD_RGB_MODE:
                rgb_matrix_config.mode = ser_buffer[1];
                break;
            case CMD_COLOR:
                rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX;
                rgb_matrix_set_color_all(ser_buffer[1], ser_buffer[2], ser_buffer[3]);
                break;
            case CMD_PIXEL:
                rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX;
                rgb_matrix_set_color(ser_buffer[1], ser_buffer[2], ser_buffer[3], ser_buffer[4]);
                break;
            case CMD_RGB_SAVE:
                ser_mode = rgb_matrix_config.mode;
                break;
            case CMD_RGB_RESTORE:
                rgb_matrix_config.mode = ser_mode;
                break;
            case CMD_PROGRESS:
                progress_enable[ser_buffer[1]]  = ser_buffer[2];
                progress[ser_buffer[1]]         = ser_buffer[3];
                progress_color[ser_buffer[1]].r = ser_buffer[4];
                progress_color[ser_buffer[1]].g = ser_buffer[5];
                progress_color[ser_buffer[1]].b = ser_buffer[6];
                break;
            default:
                break;
        }
        ser_counter = 0;
    } else {
        ser_counter++;
    }
}

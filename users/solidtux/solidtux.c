#include QMK_KEYBOARD_H
#include "solidtux.h"
#include "virtser.h"
#include "raw_hid.h"

typedef enum { CMD_NOP, CMD_RGB_MODE, CMD_COLOR, CMD_PIXEL, CMD_RGB_SAVE, CMD_RGB_RESTORE, CMD_PROGRESS, CMD_SIZE, CMD_LED, CMD_LAST } cmd_t;

bool    progress_enable[4] = {false, false, false, false};
uint8_t progress[4]        = {0, 0, 0, 0};
RGB     progress_color[4]  = {
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
};
const uint8_t PROGMEM canvas_map[CANVAS_H][CANVAS_W] = CANVAS_MAP;

__attribute__((weak)) uint8_t* rgb_matrix_mask_kb(uint8_t default_layer, uint8_t current_layer) {
    return 0;
}

uint8_t last_layer    = 0;
uint8_t current_layer = 0;
uint8_t default_layer = 0;

__attribute__((weak)) layer_state_t layer_state_set_keyboard(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state         = layer_state_set_keyboard(state);
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
        case _GAME_BOTH:
            rgb_matrix_config.mode = RGB_MATRIX_SPLASH;
            break;
        case _QWERTY:
            rgb_matrix_config.mode = RGB_MATRIX_DEFAULT_MODE;
            break;
    }
    return state;
}

bool rgb_matrix_indicators_user(void) {
    if (rgb_matrix_config.mode == RGB_MATRIX_EFFECT_MAX) {
        return false;
    }
    uint8_t* mask = rgb_matrix_mask_kb(default_layer, current_layer);
    bool     cont = mask != 0;
    for (uint8_t i = 0; i < 4; i++) {
        cont = cont || progress_enable[i];
    }
    if (!cont) {
        return false;
    }
    for (uint8_t x = 0; x < CANVAS_W; x++) {
        for (uint8_t y = 0; y < 4; y++) {
            uint8_t i = canvas_map[y][x];
            if (progress_enable[y]) {
                if (progress[y] > x) {
                    rgb_matrix_set_color(i, progress_color[y].r, progress_color[y].g, progress_color[y].b);
                } else {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (mask != 0) {
            if (mask[i] > 0) {
                HSV hsv = rgb_matrix_config.hsv;
                hsv.h += (255 * mask[i]) / 8;
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return true;
}

__attribute__((weak)) bool process_record_keyboard(uint16_t keycode, keyrecord_t* record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_keyboard(keycode, record)) {
        return false;
    }
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

uint8_t raw_mode = 10;

void raw_hid_receive(uint8_t* data, uint8_t length) {
    uint8_t out_data[length];
    cmd_t   cmd = (cmd_t)data[0];
    switch (cmd) {
        case CMD_RGB_MODE:
            rgb_matrix_config.mode = data[1];
            break;
        case CMD_COLOR:
            rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX;
            rgb_matrix_set_color_all(data[1], data[2], data[3]);
            break;
        case CMD_PIXEL:
            rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX;
            uint8_t x              = data[1];
            uint8_t y              = data[2];
            uint8_t ind            = canvas_map[y][x];
            rgb_matrix_set_color(ind, data[3], data[4], data[5]);
            break;
        case CMD_RGB_SAVE:
            raw_mode = rgb_matrix_config.mode;
            break;
        case CMD_RGB_RESTORE:
            rgb_matrix_config.mode = raw_mode;
            break;
        case CMD_PROGRESS:
            progress_enable[data[1]]  = data[2];
            progress[data[1]]         = data[3];
            progress_color[data[1]].r = data[4];
            progress_color[data[1]].g = data[5];
            progress_color[data[1]].b = data[6];
            break;
        case CMD_SIZE:
            memset(out_data, 0, length);
            out_data[0] = 2;
            out_data[1] = CANVAS_W;
            out_data[2] = CANVAS_H;
            raw_hid_send(out_data, length);
            break;
        case CMD_LED:
            rgb_matrix_set_color(data[1], data[2], data[3], data[4]);
            break;
        default:
            break;
    }
}
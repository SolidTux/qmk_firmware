#include QMK_KEYBOARD_H
#include "solidtux.h"

typedef enum { CMD_NOP, CMD_RGB_MODE, CMD_COLOR, CMD_PIXEL, CMD_RGB_SAVE, CMD_RGB_RESTORE, CMD_PROGRESS, CMD_LAST } cmd_t;

bool    progress_enable[4] = {false, false, false, false};
uint8_t progress[4]        = {0, 0, 0, 0};
RGB     progress_color[4]  = {
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
};

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
        case _QWERTY:
            rgb_matrix_config.mode = RGB_MATRIX_STARTUP_MODE;
            break;
    }
    return state;
}

void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_config.mode == RGB_MATRIX_EFFECT_MAX) {
        return;
    }
    uint8_t* mask = rgb_matrix_mask_kb(default_layer, current_layer);
    bool     cont = mask != 0;
    for (uint8_t i = 0; i < 4; i++) {
        cont = cont || progress_enable[i];
    }
    if (!cont) {
        return;
    }
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        uint8_t x = i % MATRIX_COLS;
        uint8_t y = i / MATRIX_COLS;
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
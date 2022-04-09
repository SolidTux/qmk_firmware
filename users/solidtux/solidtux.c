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

__attribute__((weak)) uint8_t* rgb_matrix_mask_kb(void) {
    return 0;
}

void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_config.mode == RGB_MATRIX_EFFECT_MAX) {
        return;
    }
    uint8_t* mask = rgb_matrix_mask_kb();
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
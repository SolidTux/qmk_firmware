RGB_MATRIX_EFFECT(image)
RGB_MATRIX_EFFECT(numpad)
RGB_MATRIX_EFFECT(game)
RGB_MATRIX_EFFECT(alphamap)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// clang-format off
const bool PROGMEM image_mask[47] = {
    0,0,1,1,0,0,0,1,0,1,0,0,
    0,0,1,0,1,0,0,1,1,1,0,0,
    0,0,1,1,0,0,0,1,0,1,0,0,
    0,0,0,0,0,0,  0,0,0,0,0
};

const bool PROGMEM numpad_mask[47] = {
    0,0,0,0,0,0,0,1,1,1,1,0,
    0,0,0,0,0,0,0,1,1,1,1,1,
    0,0,0,0,0,0,0,1,1,1,1,0,
    0,0,0,0,0,0,  1,1,1,1,0
};

const bool PROGMEM game_mask[47] = {
    0,0,1,0,0,0,0,0,0,0,0,0,
    0,1,1,1,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,  0,0,0,0,0
};
// clang-format on

static bool image(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (led_max > 48) {
        led_max = 48;
    }
    for (uint8_t i = led_min; i < led_max; i++) {
        if (image_mask[i]) {
            rgb_matrix_set_color(i, 0x00, 0xff, 0xff);
        } else {
            rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool game(effect_params_t* params) {
    bool super = SPLASH(params);
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (led_max > 48) {
        led_max = 48;
    }
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (game_mask[i]) {
            case 1:
                rgb_matrix_set_color(i, 0, 255, 0);
                break;
            default:
                continue;
        }
    }
    return (led_max < DRIVER_LED_TOTAL) || super;
}


static bool numpad(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (led_max > 48) {
        led_max = 48;
    }
    for (uint8_t i = led_min; i < led_max; i++) {
        HSV hsv = rgb_matrix_config.hsv;
        if (numpad_mask[i]) {
            hsv.h += rgb_matrix_config.speed / 2;
        }
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            hsv.h += rgb_matrix_config.speed;
        }
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

void process_rgb_matrix_typing_alphamap(keyrecord_t* record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], 32);
}

bool alphamap(effect_params_t* params) {
    // Modified version of RGB_MATRIX_USE_LIMITS to work off of matrix row / col size
    uint8_t led_min = RGB_MATRIX_LED_PROCESS_LIMIT * params->iter;
    uint8_t led_max = led_min + RGB_MATRIX_LED_PROCESS_LIMIT;
    if (led_max > sizeof(g_rgb_frame_buffer)) led_max = sizeof(g_rgb_frame_buffer);

    if (params->init) {
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }

    // Render heatmap & decrease
    for (int i = led_min; i < led_max; i++) {
        uint8_t row = i % MATRIX_ROWS;
        uint8_t col = i / MATRIX_ROWS;
        uint8_t val = g_rgb_frame_buffer[row][col];

        // set the pixel colour
        uint8_t led[LED_HITS_TO_REMEMBER];
        uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);
        for (uint8_t j = 0; j < led_count; ++j) {
            if (!HAS_ANY_FLAGS(g_led_config.flags[led[j]], params->flags)) continue;

            HSV hsv = rgb_matrix_config.hsv;
            hsv.s   = qsub8(hsv.s, val);
            if (HAS_FLAGS(g_led_config.flags[led[j]], LED_FLAG_MODIFIER)) {
                hsv.h += rgb_matrix_config.speed;
            }
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(led[j], rgb.r, rgb.g, rgb.b);
        }

        g_rgb_frame_buffer[row][col] = qsub8(val, 1);
    }

    return led_max < sizeof(g_rgb_frame_buffer);
}

#endif

RGB_MATRIX_EFFECT(alphamap)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void process_rgb_matrix_typing_alphamap(uint8_t row, uint8_t col) {
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

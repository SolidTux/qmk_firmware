RGB_MATRIX_EFFECT(image)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// clang-format off
const bool PROGMEM image_mask[47] = {
    0,0,1,1,0,0,0,1,0,1,0,0,
    0,0,1,0,1,0,0,1,1,1,0,0,
    0,0,1,1,0,0,0,1,0,1,0,0,
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

#endif
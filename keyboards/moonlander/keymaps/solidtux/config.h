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

#pragma once

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(NO_SOUND)
#    define GOODBYE_SONG SONG(NO_SOUND)
#endif

#define ORYX_CONFIGURATOR

#define TAPPING_TERM 170
#define PERMISSIVE_HOLD
//#define RETRO_TAPPING
#define TAPPING_TOGGLE 2

//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_alphamap
#define RGB_MATRIX_STARTUP_HUE 43
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL 255

#define UNICODE_SELECTED_MODES UC_LNX

#define MOONLANDER_USER_LEDS

#define CANVAS_H 5
#define CANVAS_W 14

// clang-format off
#define CANVAS_MAP { \
    {   0,   5,  10,  15,  20,  25,  29,    65,  61,  56,  51,  46,  41,  36}, \
    {   1,   6,  11,  16,  21,  26,  30,    66,  62,  57,  52,  47,  42,  37}, \
    {   2,   7,  12,  17,  22,  27,  31,    67,  63,  58,  53,  48,  43,  38}, \
    {   3,   8,  13,  18,  23,  28, 255,   255,  64,  59,  54,  49,  44,  39}, \
    {   4,   9,  14,  19,  24, 255, 255,   255, 255,  60,  55,  50,  45,  40} \
}

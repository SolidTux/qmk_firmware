#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#define RGB_MATRIX_CUSTOM_image RGB_MATRIX_EFFECT_MAX

enum layers { _QWERTY, _GAME, _GAME_ARROW, _LOWER, _RAISE, _ADJUST, _NUMPAD, _MOUSE };

enum keycodes {
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

#endif
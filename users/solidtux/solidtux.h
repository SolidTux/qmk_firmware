#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

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

#endif
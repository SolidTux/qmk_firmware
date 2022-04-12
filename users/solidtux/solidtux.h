#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum layers { _QWERTY, _GAME, _GAME_ARROW, _LOWER, _RAISE, _ADJUST, _NUMPAD };

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

#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define NUMPAD TT(_NUMPAD)
#define GAME DF(_GAME)
#define GAMEARR DF(_GAME_ARROW)
#define QWERTY DF(_QWERTY)

#endif
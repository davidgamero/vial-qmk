/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_COL_PINS \
    { D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS \
    { B7, D5, C7, F1, F0, B6 }

#define DIODE_DIRECTION ROW2COL

// WS2812 RGB LED strip input and number of LEDs
// #define RGB_DI_PIN D3
// #define RGBLED_NUM 12

/* define if matrix has ghost */
// #define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3
#define PMW33XX_CS_PIN F7
#define USE_I2C
#define MASTER_RIGHT
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define PMW3360_CPI 200
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE

// homerow mods
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200

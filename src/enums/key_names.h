#ifndef KEY_NAMES_H
#define KEY_NAMES_H

#include <linux/input.h>

typedef enum {
    // Alphabet keys
    KEY_NAME_A = KEY_A,
    KEY_NAME_B = KEY_B,
    KEY_NAME_C = KEY_C,
    KEY_NAME_D = KEY_D,
    KEY_NAME_E = KEY_E,
    KEY_NAME_F = KEY_F,
    KEY_NAME_G = KEY_G,
    KEY_NAME_H = KEY_H,
    KEY_NAME_I = KEY_I,
    KEY_NAME_J = KEY_J,
    KEY_NAME_K = KEY_K,
    KEY_NAME_L = KEY_L,
    KEY_NAME_M = KEY_M,
    KEY_NAME_N = KEY_N,
    KEY_NAME_O = KEY_O,
    KEY_NAME_P = KEY_P,
    KEY_NAME_Q = KEY_Q,
    KEY_NAME_R = KEY_R,
    KEY_NAME_S = KEY_S,
    KEY_NAME_T = KEY_T,
    KEY_NAME_U = KEY_U,
    KEY_NAME_V = KEY_V,
    KEY_NAME_W = KEY_W,
    KEY_NAME_X = KEY_X,
    KEY_NAME_Y = KEY_Y,
    KEY_NAME_Z = KEY_Z,

    // Number keys
    KEY_NAME_0 = KEY_0,
    KEY_NAME_1 = KEY_1,
    KEY_NAME_2 = KEY_2,
    KEY_NAME_3 = KEY_3,
    KEY_NAME_4 = KEY_4,
    KEY_NAME_5 = KEY_5,
    KEY_NAME_6 = KEY_6,
    KEY_NAME_7 = KEY_7,
    KEY_NAME_8 = KEY_8,
    KEY_NAME_9 = KEY_9,

    // Special keys
    KEY_NAME_SPACE = KEY_SPACE,
    KEY_NAME_ENTER = KEY_ENTER,
    KEY_NAME_BACKSPACE = KEY_BACKSPACE,
    KEY_NAME_TAB = KEY_TAB,
    KEY_NAME_ESC = KEY_ESC,
    KEY_NAME_PRINT_SCREEN = KEY_SYSRQ,

    // Function keys
    KEY_NAME_F1 = KEY_F1,
    KEY_NAME_F2 = KEY_F2,
    KEY_NAME_F3 = KEY_F3,
    KEY_NAME_F4 = KEY_F4,
    KEY_NAME_F5 = KEY_F5,
    KEY_NAME_F6 = KEY_F6,
    KEY_NAME_F7 = KEY_F7,
    KEY_NAME_F8 = KEY_F8,
    KEY_NAME_F9 = KEY_F9,
    KEY_NAME_F10 = KEY_F10,
    KEY_NAME_F11 = KEY_F11,
    KEY_NAME_F12 = KEY_F12,

    // Modifier keys
    KEY_NAME_LEFT_SHIFT = KEY_LEFTSHIFT,
    KEY_NAME_RIGHT_SHIFT = KEY_RIGHTSHIFT,
    KEY_NAME_LEFT_CTRL = KEY_LEFTCTRL,
    KEY_NAME_RIGHT_CTRL = KEY_RIGHTCTRL,
    KEY_NAME_LEFT_ALT = KEY_LEFTALT,
    KEY_NAME_RIGHT_ALT = KEY_RIGHTALT,

    // Unknown key
    KEY_NAME_UNKNOWN = -1
} KeyName;

const char* key_name_to_string(KeyName key);
KeyName string_to_key_name(const char *key_str);

#endif // KEY_NAMES_H
#include "key_names.h"
#include <string.h>

const char* key_name_to_string(KeyName key) {
    switch (key) {
        // Alphabet keys
        case KEY_NAME_A: return "A";
        case KEY_NAME_B: return "B";
        case KEY_NAME_C: return "C";
        case KEY_NAME_D: return "D";
        case KEY_NAME_E: return "E";
        case KEY_NAME_F: return "F";
        case KEY_NAME_G: return "G";
        case KEY_NAME_H: return "H";
        case KEY_NAME_I: return "I";
        case KEY_NAME_J: return "J";
        case KEY_NAME_K: return "K";
        case KEY_NAME_L: return "L";
        case KEY_NAME_M: return "M";
        case KEY_NAME_N: return "N";
        case KEY_NAME_O: return "O";
        case KEY_NAME_P: return "P";
        case KEY_NAME_Q: return "Q";
        case KEY_NAME_R: return "R";
        case KEY_NAME_S: return "S";
        case KEY_NAME_T: return "T";
        case KEY_NAME_U: return "U";
        case KEY_NAME_V: return "V";
        case KEY_NAME_W: return "W";
        case KEY_NAME_X: return "X";
        case KEY_NAME_Y: return "Y";
        case KEY_NAME_Z: return "Z";

        // Number keys
        case KEY_NAME_0: return "0";
        case KEY_NAME_1: return "1";
        case KEY_NAME_2: return "2";
        case KEY_NAME_3: return "3";
        case KEY_NAME_4: return "4";
        case KEY_NAME_5: return "5";
        case KEY_NAME_6: return "6";
        case KEY_NAME_7: return "7";
        case KEY_NAME_8: return "8";
        case KEY_NAME_9: return "9";

        // Special keys
        case KEY_NAME_SPACE: return "SPACE";
        case KEY_NAME_ENTER: return "ENTER";
        case KEY_NAME_BACKSPACE: return "BACKSPACE";
        case KEY_NAME_TAB: return "TAB";
        case KEY_NAME_ESC: return "ESC";
        case KEY_NAME_PRINT_SCREEN: return "PRINT";

        // Function keys
        case KEY_NAME_F1: return "F1";
        case KEY_NAME_F2: return "F2";
        case KEY_NAME_F3: return "F3";
        case KEY_NAME_F4: return "F4";
        case KEY_NAME_F5: return "F5";
        case KEY_NAME_F6: return "F6";
        case KEY_NAME_F7: return "F7";
        case KEY_NAME_F8: return "F8";
        case KEY_NAME_F9: return "F9";
        case KEY_NAME_F10: return "F10";
        case KEY_NAME_F11: return "F11";
        case KEY_NAME_F12: return "F12";

        // Modifier keys
        case KEY_NAME_LEFT_SHIFT: return "LEFT_SHIFT";
        case KEY_NAME_RIGHT_SHIFT: return "RIGHT_SHIFT";
        case KEY_NAME_LEFT_CTRL: return "LEFT_CTRL";
        case KEY_NAME_RIGHT_CTRL: return "RIGHT_CTRL";
        case KEY_NAME_LEFT_ALT: return "LEFT_ALT";
        case KEY_NAME_RIGHT_ALT: return "RIGHT_ALT";

        // Unknown key
        default: return "UNKNOWN";
    }
}

KeyName string_to_key_name(const char *key_str) {
    if (!key_str) return KEY_NAME_UNKNOWN;

    // Alphabet keys
    if (strcmp(key_str, "A") == 0) return KEY_NAME_A;
    if (strcmp(key_str, "B") == 0) return KEY_NAME_B;
    if (strcmp(key_str, "C") == 0) return KEY_NAME_C;
    if (strcmp(key_str, "D") == 0) return KEY_NAME_D;
    if (strcmp(key_str, "E") == 0) return KEY_NAME_E;
    if (strcmp(key_str, "F") == 0) return KEY_NAME_F;
    if (strcmp(key_str, "G") == 0) return KEY_NAME_G;
    if (strcmp(key_str, "H") == 0) return KEY_NAME_H;
    if (strcmp(key_str, "I") == 0) return KEY_NAME_I;
    if (strcmp(key_str, "J") == 0) return KEY_NAME_J;
    if (strcmp(key_str, "K") == 0) return KEY_NAME_K;
    if (strcmp(key_str, "L") == 0) return KEY_NAME_L;
    if (strcmp(key_str, "M") == 0) return KEY_NAME_M;
    if (strcmp(key_str, "N") == 0) return KEY_NAME_N;
    if (strcmp(key_str, "O") == 0) return KEY_NAME_O;
    if (strcmp(key_str, "P") == 0) return KEY_NAME_P;
    if (strcmp(key_str, "Q") == 0) return KEY_NAME_Q;
    if (strcmp(key_str, "R") == 0) return KEY_NAME_R;
    if (strcmp(key_str, "S") == 0) return KEY_NAME_S;
    if (strcmp(key_str, "T") == 0) return KEY_NAME_T;
    if (strcmp(key_str, "U") == 0) return KEY_NAME_U;
    if (strcmp(key_str, "V") == 0) return KEY_NAME_V;
    if (strcmp(key_str, "W") == 0) return KEY_NAME_W;
    if (strcmp(key_str, "X") == 0) return KEY_NAME_X;
    if (strcmp(key_str, "Y") == 0) return KEY_NAME_Y;
    if (strcmp(key_str, "Z") == 0) return KEY_NAME_Z;

    // Number keys
    if (strcmp(key_str, "0") == 0) return KEY_NAME_0;
    if (strcmp(key_str, "1") == 0) return KEY_NAME_1;
    if (strcmp(key_str, "2") == 0) return KEY_NAME_2;
    if (strcmp(key_str, "3") == 0) return KEY_NAME_3;
    if (strcmp(key_str, "4") == 0) return KEY_NAME_4;
    if (strcmp(key_str, "5") == 0) return KEY_NAME_5;
    if (strcmp(key_str, "6") == 0) return KEY_NAME_6;
    if (strcmp(key_str, "7") == 0) return KEY_NAME_7;
    if (strcmp(key_str, "8") == 0) return KEY_NAME_8;
    if (strcmp(key_str, "9") == 0) return KEY_NAME_9;

    // Special keys
    if (strcmp(key_str, "SPACE") == 0) return KEY_NAME_SPACE;
    if (strcmp(key_str, "ENTER") == 0) return KEY_NAME_ENTER;
    if (strcmp(key_str, "BACKSPACE") == 0) return KEY_NAME_BACKSPACE;
    if (strcmp(key_str, "TAB") == 0) return KEY_NAME_TAB;
    if (strcmp(key_str, "ESC") == 0) return KEY_NAME_ESC;
    if (strcmp(key_str, "PRINT") == 0) return KEY_NAME_PRINT_SCREEN;

    // Function keys
    if (strcmp(key_str, "F1") == 0) return KEY_NAME_F1;
    if (strcmp(key_str, "F2") == 0) return KEY_NAME_F2;
    if (strcmp(key_str, "F3") == 0) return KEY_NAME_F3;
    if (strcmp(key_str, "F4") == 0) return KEY_NAME_F4;
    if (strcmp(key_str, "F5") == 0) return KEY_NAME_F5;
    if (strcmp(key_str, "F6") == 0) return KEY_NAME_F6;
    if (strcmp(key_str, "F7") == 0) return KEY_NAME_F7;
    if (strcmp(key_str, "F8") == 0) return KEY_NAME_F8;
    if (strcmp(key_str, "F9") == 0) return KEY_NAME_F9;
    if (strcmp(key_str, "F10") == 0) return KEY_NAME_F10;
    if (strcmp(key_str, "F11") == 0) return KEY_NAME_F11;
    if (strcmp(key_str, "F12") == 0) return KEY_NAME_F12;

    // Modifier keys
    if (strcmp(key_str, "LEFT_SHIFT") == 0) return KEY_NAME_LEFT_SHIFT;
    if (strcmp(key_str, "RIGHT_SHIFT") == 0) return KEY_NAME_RIGHT_SHIFT;
    if (strcmp(key_str, "LEFT_CTRL") == 0) return KEY_NAME_LEFT_CTRL;
    if (strcmp(key_str, "RIGHT_CTRL") == 0) return KEY_NAME_RIGHT_CTRL;
    if (strcmp(key_str, "LEFT_ALT") == 0) return KEY_NAME_LEFT_ALT;
    if (strcmp(key_str, "RIGHT_ALT") == 0) return KEY_NAME_RIGHT_ALT;

    return KEY_NAME_UNKNOWN;
}
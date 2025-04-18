#include "key_names.h"
#include <string.h>
#include <ctype.h>

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

        // Super/Windows keys
        case KEY_NAME_LEFT_SUPER: return "LEFT_SUPER";
        case KEY_NAME_RIGHT_SUPER: return "RIGHT_SUPER";

        // Additional special characters
        case KEY_NAME_SLASH: return "/";
        case KEY_NAME_ASTERISK: return "*";
        case KEY_NAME_MINUS: return "-";
        case KEY_NAME_PLUS: return "+";
        case KEY_NAME_BACKTICK: return "`";
        case KEY_NAME_BACKSLASH: return "\\";
        case KEY_NAME_LEFTSQUAREBRACKET: return "[";
        case KEY_NAME_RIGHTSQUAREBRACKET: return "]";
        case KEY_NAME_SEMICOLON: return ";";
        case KEY_NAME_COMMA: return ",";
        case KEY_NAME_DOT: return ".";
        case KEY_NAME_EQUALS: return "=";

        // Numpad keys
        case KEY_NAME_KP_0: return "KP_0";
        case KEY_NAME_KP_1: return "KP_1";
        case KEY_NAME_KP_2: return "KP_2";
        case KEY_NAME_KP_3: return "KP_3";
        case KEY_NAME_KP_4: return "KP_4";
        case KEY_NAME_KP_5: return "KP_5";
        case KEY_NAME_KP_6: return "KP_6";
        case KEY_NAME_KP_7: return "KP_7";
        case KEY_NAME_KP_8: return "KP_8";
        case KEY_NAME_KP_9: return "KP_9";
        case KEY_NAME_KP_DOT: return "KP_DOT";
        case KEY_NAME_KP_ENTER: return "KP_ENTER";
        case KEY_NAME_KP_SLASH: return "KP_SLASH";
        case KEY_NAME_KP_MINUS: return "KP_MINUS";
        // Note: KP_ASTERISK and KP_PLUS are handled by '*' and '+' cases above
    
        // Unknown key
        default: return "UNKNOWN";
      }
    }

KeyName string_to_key_name(const char *key_str) {
    if (!key_str) return KEY_NAME_UNKNOWN;

    // Single character keys
    if (strlen(key_str) == 1) {
        char key = key_str[0];

        // Alphabet keys
        if (key >= 'A' && key <= 'Z') {
            switch (key) {
                case 'A': return KEY_NAME_A;
                case 'B': return KEY_NAME_B;
                case 'C': return KEY_NAME_C;
                case 'D': return KEY_NAME_D;
                case 'E': return KEY_NAME_E;
                case 'F': return KEY_NAME_F;
                case 'G': return KEY_NAME_G;
                case 'H': return KEY_NAME_H;
                case 'I': return KEY_NAME_I;
                case 'J': return KEY_NAME_J;
                case 'K': return KEY_NAME_K;
                case 'L': return KEY_NAME_L;
                case 'M': return KEY_NAME_M;
                case 'N': return KEY_NAME_N;
                case 'O': return KEY_NAME_O;
                case 'P': return KEY_NAME_P;
                case 'Q': return KEY_NAME_Q;
                case 'R': return KEY_NAME_R;
                case 'S': return KEY_NAME_S;
                case 'T': return KEY_NAME_T;
                case 'U': return KEY_NAME_U;
                case 'V': return KEY_NAME_V;
                case 'W': return KEY_NAME_W;
                case 'X': return KEY_NAME_X;
                case 'Y': return KEY_NAME_Y;
                case 'Z': return KEY_NAME_Z;
                default: return KEY_NAME_UNKNOWN;
            }
        }
        if (key >= 'a' && key <= 'z') {
            switch (key) {
                case 'a': return KEY_NAME_A;
                case 'b': return KEY_NAME_B;
                case 'c': return KEY_NAME_C;
                case 'd': return KEY_NAME_D;
                case 'e': return KEY_NAME_E;
                case 'f': return KEY_NAME_F;
                case 'g': return KEY_NAME_G;
                case 'h': return KEY_NAME_H;
                case 'i': return KEY_NAME_I;
                case 'j': return KEY_NAME_J;
                case 'k': return KEY_NAME_K;
                case 'l': return KEY_NAME_L;
                case 'm': return KEY_NAME_M;
                case 'n': return KEY_NAME_N;
                case 'o': return KEY_NAME_O;
                case 'p': return KEY_NAME_P;
                case 'q': return KEY_NAME_Q;
                case 'r': return KEY_NAME_R;
                case 's': return KEY_NAME_S;
                case 't': return KEY_NAME_T;
                case 'u': return KEY_NAME_U;
                case 'v': return KEY_NAME_V;
                case 'w': return KEY_NAME_W;
                case 'x': return KEY_NAME_X;
                case 'y': return KEY_NAME_Y;
                case 'z': return KEY_NAME_Z;
                default: return KEY_NAME_UNKNOWN;
            }
        }

        // Number keys
        if (key >= '0' && key <= '9') return (KeyName)(KEY_NAME_0 + (key - '0'));

        // Special characters
        switch (key) {
            case '/': return KEY_NAME_SLASH;
            case '*': return KEY_NAME_ASTERISK;
            case '-': return KEY_NAME_MINUS;
            case '+': return KEY_NAME_PLUS;
            case '`': return KEY_NAME_BACKTICK;
            case '\\': return KEY_NAME_BACKSLASH;
            case '[': return KEY_NAME_LEFTSQUAREBRACKET;
            case ']': return KEY_NAME_RIGHTSQUAREBRACKET;
            case ';': return KEY_NAME_SEMICOLON;
            case ',': return KEY_NAME_COMMA;
            case '.': return KEY_NAME_DOT;
            case '=': return KEY_NAME_EQUALS;
        }
    }

    // Named keys
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

    // Super/Windows keys
    if (strcmp(key_str, "LEFT_SUPER") == 0) return KEY_NAME_LEFT_SUPER;
    if (strcmp(key_str, "RIGHT_SUPER") == 0) return KEY_NAME_RIGHT_SUPER;
  
    // Numpad keys
    if (strcmp(key_str, "KP_0") == 0) return KEY_NAME_KP_0;
    if (strcmp(key_str, "KP_1") == 0) return KEY_NAME_KP_1;
    if (strcmp(key_str, "KP_2") == 0) return KEY_NAME_KP_2;
    if (strcmp(key_str, "KP_3") == 0) return KEY_NAME_KP_3;
    if (strcmp(key_str, "KP_4") == 0) return KEY_NAME_KP_4;
    if (strcmp(key_str, "KP_5") == 0) return KEY_NAME_KP_5;
    if (strcmp(key_str, "KP_6") == 0) return KEY_NAME_KP_6;
    if (strcmp(key_str, "KP_7") == 0) return KEY_NAME_KP_7;
    if (strcmp(key_str, "KP_8") == 0) return KEY_NAME_KP_8;
    if (strcmp(key_str, "KP_9") == 0) return KEY_NAME_KP_9;
    if (strcmp(key_str, "KP_DOT") == 0) return KEY_NAME_KP_DOT;
    if (strcmp(key_str, "KP_ENTER") == 0) return KEY_NAME_KP_ENTER;
    if (strcmp(key_str, "KP_SLASH") == 0) return KEY_NAME_KP_SLASH;
    if (strcmp(key_str, "KP_MINUS") == 0) return KEY_NAME_KP_MINUS;
    // Note: KP_ASTERISK and KP_PLUS are handled by '*' and '+' cases above
  
    return KEY_NAME_UNKNOWN;
  }
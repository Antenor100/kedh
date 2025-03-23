#ifndef KEYBINDS_PARSER_H
#define KEYBINDS_PARSER_H

#include "../enums/key_names.h"
#include <ctype.h>
#include <string.h>

#define MAX_KEYBINDS 64
#define MAX_KEY_COMBINATION_LENGTH 5
#define MAX_COMMAND_LENGTH 256

typedef struct {
    KeyName keys[MAX_KEY_COMBINATION_LENGTH];
    int key_count;
    char command[MAX_COMMAND_LENGTH];
} KeybindConfig;

typedef struct {
    KeybindConfig bindings[MAX_KEYBINDS];
    int binding_count;
} KeybindsConfig;

int load_keybinds_config(const char *config_path, KeybindsConfig *config);

KeybindConfig *find_matching_keybind(KeybindsConfig *config,
                                     KeyName *pressed_keys,
                                     int pressed_key_count);

void trim_whitespace(char *str);

#endif
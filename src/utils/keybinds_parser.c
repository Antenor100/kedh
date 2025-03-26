#include "keybinds_parser.h"
#include "../enums/key_names.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert string to uppercase for case-insensitive comparison
void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int load_keybinds_config(const char *keybinds_path, KeybindsConfig *config) {
    FILE *file = fopen(keybinds_path, "r");

    if (!file) {
        fprintf(stderr, "Could not open keybinds config file: %s - %s\n",
                keybinds_path, strerror(errno));
        return 0;
    }

    config->binding_count = 0;

    char line[512];
    int line_number = 0;

    while (fgets(line, sizeof(line), file) &&
           config->binding_count < MAX_KEYBINDS) {
        line_number++;

        trim_whitespace(line);

        if (line[0] == '#' || line[0] == '\0') {
            continue;
        }

        char *command_start = strchr(line, '=');
        if (!command_start) {
            continue;
        }

        *command_start = '\0';
        command_start++;

        trim_whitespace(command_start);
        trim_whitespace(line);

        KeybindConfig *current_bind = &config->bindings[config->binding_count];
        current_bind->key_count = 0;

        char line_copy[512];
        strcpy(line_copy, line);

        char *key_token = strtok(line_copy, "+");

        while (key_token &&
               current_bind->key_count < MAX_KEY_COMBINATION_LENGTH) {
            // Convert to uppercase for case-insensitive matching
            to_uppercase(key_token);

            // Normalize some common key names
            if (strcmp(key_token, "CTRL") == 0) key_token = "LEFT_CTRL";
            if (strcmp(key_token, "ALT") == 0) key_token = "LEFT_ALT";
            if (strcmp(key_token, "SHIFT") == 0) key_token = "LEFT_SHIFT";
            if (strcmp(key_token, "PRINTSCREEN") == 0) key_token = "PRINT";
            if (strcmp(key_token, "SUPER") == 0) key_token = "LEFT_SUPER";

            KeyName key = string_to_key_name(key_token);
            if (key != KEY_NAME_UNKNOWN) {
                current_bind->keys[current_bind->key_count++] = key;
            } else {
                fprintf(stderr, "Unknown key on line %d: %s\n", line_number,
                        key_token);
            }
            key_token = strtok(NULL, "+");
        }

        if (strlen(command_start) > 0) {
            strncpy(current_bind->command, command_start,
                    MAX_COMMAND_LENGTH - 1);
            current_bind->command[MAX_COMMAND_LENGTH - 1] = '\0';
        } else {
            fprintf(stderr, "Empty command on line %d\n", line_number);
            continue;
        }

        if (current_bind->key_count > 0 && strlen(current_bind->command) > 0) {
            config->binding_count++;
        }
    }

    fclose(file);

    if (config->binding_count == 0) {
        fprintf(stderr, "No valid keybindings found in %s\n", keybinds_path);
    }

    return config->binding_count;
}

KeybindConfig *find_matching_keybind(KeybindsConfig *config,
                                     KeyName *pressed_keys,
                                     int pressed_key_count) {
    for (int i = 0; i < config->binding_count; i++) {
        KeybindConfig *binding = &config->bindings[i];

        if (binding->key_count != pressed_key_count) {
            continue;
        }

        int match = 1;
        for (int j = 0; j < binding->key_count; j++) {
            int key_found = 0;
            for (int k = 0; k < pressed_key_count; k++) {
                if (binding->keys[j] == pressed_keys[k]) {
                    key_found = 1;
                    break;
                }
            }

            if (!key_found) {
                match = 0;
                break;
            }
        }

        if (match) {
            return binding;
        }
    }

    return NULL;
}

void trim_whitespace(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;

    while (isspace(*start))
        start++;

    while (end > start && isspace(*end))
        end--;

    if (start != str) {
        memmove(str, start, end - start + 1);
    }
    str[end - start + 1] = '\0';
}
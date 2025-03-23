#include "config_properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *configPath = "/home/antenor/.kedh/.config";

char *read_property(const char *key) {
    FILE *file = fopen(configPath, "r");
    if (file == NULL) {
        return NULL;
    }

    char line[MAX_PROP_LENGTH];
    char *value = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *equals = strchr(line, '=');
        if (equals == NULL)
            continue;

        *equals = '\0';
        char *prop_key = line;
        char *prop_value = equals + 1;

        if (strcmp(prop_key, key) == 0) {
            value = strdup(prop_value);
            break;
        }
    }

    fclose(file);
    return value;
}

int read_int_property(const char *key, int default_value) {
    char *value_str = read_property(key);
    if (value_str == NULL) {
        return default_value;
    }

    int value = atoi(value_str);
    free(value_str);
    return value;
}

int save_property(const char *key, const char *value) {
    FILE *file = fopen(configPath, "r");
    if (file == NULL) {
        file = fopen(configPath, "w");
        if (file == NULL) {
            return 0;
        }
        fprintf(file, "%s=%s\n", key, value);
        fclose(file);
        return 1;
    }

    char temp_path[MAX_PROP_LENGTH];
    snprintf(temp_path, sizeof(temp_path), "%s.tmp", configPath);
    FILE *temp_file = fopen(temp_path, "w");
    if (temp_file == NULL) {
        fclose(file);
        return 0;
    }

    char line[MAX_PROP_LENGTH];
    int property_found = 0;

    while (fgets(line, sizeof(line), file)) {
        char *equals = strchr(line, '=');
        if (equals != NULL) {
            *equals = '\0';
            char *prop_key = line;

            if (strcmp(prop_key, key) == 0) {
                fprintf(temp_file, "%s=%s\n", key, value);
                property_found = 1;
            } else {
                *equals = '=';
                fputs(line, temp_file);
            }
        } else {
            fputs(line, temp_file);
        }
    }

    if (!property_found) {
        fprintf(temp_file, "%s=%s\n", key, value);
    }

    fclose(file);
    fclose(temp_file);

    if (rename(temp_path, configPath) != 0) {
        return 0;
    }

    return 1;
}
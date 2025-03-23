#ifndef KEYBIND_COMMAND_SERVICE_H
#define KEYBIND_COMMAND_SERVICE_H

#include "../utils/keybinds_parser.h"

int keybind_command_service_init();

int execute_keybind_command(KeybindConfig *keybind);

void keybind_command_service_stop();

KeybindsConfig *get_keybinds_config(void);

#endif
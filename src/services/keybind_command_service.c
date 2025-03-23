#include "keybind_command_service.h"
#include "../utils/keybinds_parser.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static KeybindsConfig g_keybinds_config = {0};

int keybind_command_service_init() {
    char default_keybinds_path[256] = {0};

    const char *home = getenv("HOME");

    if (!home) {
        fprintf(stderr, "Could not determine home directory\n");
        return -1;
    }

    snprintf(default_keybinds_path, sizeof(default_keybinds_path),
             "%s/.kedh/.keybinds", home);

    int loaded_bindings =
        load_keybinds_config(default_keybinds_path, &g_keybinds_config);

    if (loaded_bindings == 0) {
        fprintf(stderr, "No keybindings loaded from %s\n",
                default_keybinds_path);
        return -1;
    }

    printf("Loaded %d keybindings from %s\n", loaded_bindings,
           default_keybinds_path);
           
    return 0;
}

int execute_keybind_command(KeybindConfig *keybind) {
    if (!keybind || strlen(keybind->command) == 0) {
        return -1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Failed to fork for command execution: %s\n",
                strerror(errno));
        return -1;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", keybind->command, NULL);

        fprintf(stderr, "Failed to execute command: %s\n", keybind->command);
        exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        if (exit_status != 0) {
            fprintf(stderr, "Command '%s' exited with status %d\n",
                    keybind->command, exit_status);
            return -1;
        }
        return 0;
    }

    return -1;
}

void keybind_command_service_stop() {
    memset(&g_keybinds_config, 0, sizeof(g_keybinds_config));
}

KeybindsConfig *get_keybinds_config(void) { return &g_keybinds_config; }
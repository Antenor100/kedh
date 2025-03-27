#include "main.h"
#include "enums/key_names.h"
#include "services/key_monitor_service.h"
#include "services/keybind_command_service.h"
#include "utils/keybinds_parser.h"
#include "utils/keyboard_device.h"
#include "utils/array_utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PRESSED_KEYS 5
#define PID_FILE "/tmp/kedh.pid"

static KeyName g_pressed_keys[MAX_PRESSED_KEYS];
static int g_pressed_key_count = 0;

static volatile int g_should_exit = 0;
static int g_test_mode = 0;
static int g_standalone_mode = 0;

void signal_handler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
        g_should_exit = 1;
    }
}

void key_event_handler(KeyName key, int event_type) {
    const char *key_name = key_name_to_string(key);

    if (event_type == 1) {
        if (g_test_mode) {
            printf("Key Pressed: %s\n", key_name);
        }

        if (g_pressed_key_count < MAX_PRESSED_KEYS) {
            int is_duplicate = 0;
            for (int i = 0; i < g_pressed_key_count; i++) {
                if (g_pressed_keys[i] == key) {
                    is_duplicate = 1;
                    break;
                }
            }

            if (!is_duplicate) {
                g_pressed_keys[g_pressed_key_count++] = key;
            }
        }

        KeybindsConfig *keybinds_config = get_keybinds_config();
        KeybindConfig *matching_keybind = find_matching_keybind(
            keybinds_config, g_pressed_keys, g_pressed_key_count);

        if (matching_keybind) {
            if (g_test_mode) {
                printf("Executing keybind command: %s\n",
                       matching_keybind->command);
            }
            execute_keybind_command(matching_keybind);
        }

        if (g_test_mode && key == KEY_NAME_ESC) {
            g_should_exit = 1;
            printf("ESC key pressed. Stopping key monitoring...\n");
        }

    } else if (event_type == 0) {
        if (g_test_mode) {
            printf("Key Released: %s\n", key_name);
        }

        for (int i = 0; i < g_pressed_key_count; i++) {
            if (g_pressed_keys[i] == key) {
                memmove(&g_pressed_keys[i], &g_pressed_keys[i + 1],
                        (g_pressed_key_count - i - 1) * sizeof(KeyName));
                g_pressed_key_count--;
                break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    char selected_device[G_MAX_PATH_LENGTH] = {0};
    int device_selected = 0;

    if (contains_str(argc, argv, "-h")) {
        printf("Usage: kedh-dev [-c] [-n NAME] [-h] [-t] [-v] [-s] [-k]\n");
        printf("Options:\n");
        printf("  No params     Start key monitor and run indefinitely\n");
        printf("  -c            Choose an event device by index and start key monitor (saves KEYBOARD_DEVICE_INDEX)\n");
        printf("  -n \"NAME\"   Choose a keyboard device by its name (saves KEYBOARD_DEVICE_NAME)\n");
        printf("  -t            Start in test mode (exit on ESC)\n");
        printf("  -v            Enable verbose logging\n");
        printf("  -s            Run in standalone mode (background process)\n");
        printf("  -k            Kill all running kedh processes\n");
        printf("  -h            Show this help message\n");
        return 0;
    }

    if (contains_str(argc, argv, "-k")) {
        system("pkill -f kedh");
        printf("Killed all running kedh processes.\n");
        return 0;
    }

    if (contains_str(argc, argv, "-v")) {
        printf("KEDH - Keyboard Event Device Handler (by devantenor) -> "
               "Version: %s\n",
               G_KEDH_VERSION);
        return 0;
    }

    if (contains_str(argc, argv, "-t")) {
        g_test_mode = 1;

    } else if (contains_str(argc, argv, "-s")) {
        g_standalone_mode = 1;
    }

    if (contains_str(argc, argv, "-c")) {
        if (!choose_keyboard_device(selected_device)) {
            fprintf(stderr, "Failed to choose a keyboard device.\n");
            return 1;
        }
        device_selected = 1;

    } else if (contains_str(argc, argv, "-n")) {

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0) {
                if (i + 1 < argc) {
                    strncpy(selected_device, argv[i + 1], G_MAX_PATH_LENGTH - 1);
                    selected_device[G_MAX_PATH_LENGTH - 1] = '\0';
                    break;
                    
                } else {
                    fprintf(stderr, "Error: Device name required with -n option.\n");
                    return 1;
                }
            }
        }

        if (!find_keyboard_device_by_name(selected_device, selected_device)) {
            fprintf(stderr, "Failed to find keyboard device with name '%s'.\n", selected_device);
            return 1;
        }
        device_selected = 1;
    }

    if (keybind_command_service_init() != 0) {
        fprintf(stderr, "Failed to initialize keybind command service.\n");
        return 1;
    }

    if (g_standalone_mode) {
        pid_t pid = fork();
        
        if (pid < 0) {
            fprintf(stderr, "Failed to fork background process.\n");
            return 1;
        }
        
        if (pid > 0) {            
            printf("Kedh started in standalone mode. PID: %d\n", pid);
            return 0;
        }
                
        setsid(); 
                
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
                
        FILE *pid_file = fopen(PID_FILE, "w");
        if (pid_file) {
            fprintf(pid_file, "%d", getpid());
            fclose(pid_file);
        }
    }

    if (device_selected) {
        if (key_monitor_service_init(key_event_handler) != 0) {
            fprintf(stderr, "Failed to start key monitoring service.\n");
            return 1;
        }
    } else {
        if (key_monitor_service_init(key_event_handler) != 0) {
            fprintf(stderr, "Failed to start key monitoring service.\n");
            return 1;
        }
    }

    if (g_test_mode) {
        printf("Press keys according to configured keybindings. Press ESC to exit. Verbose logging enabled.\n");
    } else if (!g_standalone_mode) {
        printf("Press keys according to configured keybindings. Press Ctrl+C to exit.\n");
    } else {
        printf("Kedh started in standalone mode. Run 'kedh -k' for stop.\n");
    }

    struct timespec timeout = {.tv_sec = 0, .tv_nsec = 50000000};

    while (!g_should_exit) {
        nanosleep(&timeout, NULL);
    }

    key_monitor_service_stop();
    keybind_command_service_stop();
    
    if (g_standalone_mode) {
        unlink(PID_FILE);
    }

    return 0;
}

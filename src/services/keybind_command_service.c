#define _GNU_SOURCE
#include "keybind_command_service.h"
#include "../utils/keybinds_parser.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/time.h>

#define COMMAND_TIMEOUT_SECONDS 1

static KeybindsConfig g_keybinds_config = {0};

typedef struct {
    char command[MAX_COMMAND_LENGTH];
    int result;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int completed;
} CommandExecutionContext;

static void *execute_command_thread(void *arg) {
    CommandExecutionContext *context = (CommandExecutionContext *)arg;
    
    pid_t pid = fork();
    
    if (pid == -1) {
        pthread_mutex_lock(&context->mutex);
        context->result = -1;
        context->completed = 1;
        pthread_cond_signal(&context->cond);
        pthread_mutex_unlock(&context->mutex);
        return NULL;
    }
    
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", context->command, NULL);

        fprintf(stderr, "Failed to execute command: %s\n", context->command);
        exit(1);
    }

    int status;
    waitpid(pid, &status, 0);
    
    pthread_mutex_lock(&context->mutex);
    context->result = (WIFEXITED(status) && WEXITSTATUS(status) == 0) ? 0 : -1;
    context->completed = 1;
    pthread_cond_signal(&context->cond);
    pthread_mutex_unlock(&context->mutex);
    
    return NULL;
}

int execute_keybind_command(KeybindConfig *keybind) {
    if (!keybind || strlen(keybind->command) == 0) {
        return -1;
    }
    
    CommandExecutionContext context = {0};
    strncpy(context.command, keybind->command, MAX_COMMAND_LENGTH - 1);
    context.command[MAX_COMMAND_LENGTH - 1] = '\0';
    context.result = -1;
    context.completed = 0;
    
    pthread_mutex_init(&context.mutex, NULL);
    pthread_cond_init(&context.cond, NULL);
    
    pthread_t thread;
    if (pthread_create(&thread, NULL, execute_command_thread, &context) != 0) {
        fprintf(stderr, "Failed to create thread for command execution\n");
        pthread_mutex_destroy(&context.mutex);
        pthread_cond_destroy(&context.cond);
        return -1;
    }
    
    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += COMMAND_TIMEOUT_SECONDS;
    
    pthread_mutex_lock(&context.mutex);
    int wait_result = 0;
    while (!context.completed && wait_result == 0) {
        wait_result = pthread_cond_timedwait(&context.cond, &context.mutex, &timeout);
    }
    
    if (wait_result != 0) {
        pthread_cancel(thread);
        context.result = -1;
        fprintf(stderr, "Command timed out or failed: %s\n", context.command);
    }
    
    pthread_mutex_unlock(&context.mutex);
    
    pthread_join(thread, NULL);
    
    pthread_mutex_destroy(&context.mutex);
    pthread_cond_destroy(&context.cond);
    
    return context.result;
}

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

void keybind_command_service_stop() {
    memset(&g_keybinds_config, 0, sizeof(g_keybinds_config));
}

KeybindsConfig *get_keybinds_config(void) { return &g_keybinds_config; }
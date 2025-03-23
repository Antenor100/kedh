#include "key_monitor_service.h"
#include "../enums/key_names.h"
#include "../utils/keyboard_device.h"
#include <errno.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <linux/input.h>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_POLL_TIMEOUT_MS 500
#define EVENT_BUFFER_SIZE 16

static pthread_t monitor_thread;
static volatile int is_monitoring = 0;
static KeyEventCallback event_callback = NULL;
static pthread_mutex_t monitoring_mutex = PTHREAD_MUTEX_INITIALIZER;

static void log_error(const char *message) {
    fprintf(stderr, "[Key Monitor] %s: %s\n", message, strerror(errno));
}

static void *key_monitor_thread(void *arg __attribute__((unused))) {
    char selected_device[G_MAX_PATH_LENGTH];

    pthread_mutex_lock(&monitoring_mutex);
    if (!read_configured_keyboard_device(selected_device,
                                         sizeof(selected_device))) {
        log_error("No keyboard device configured");
        is_monitoring = 0;
        pthread_mutex_unlock(&monitoring_mutex);
        return NULL;
    }
    pthread_mutex_unlock(&monitoring_mutex);

    struct libevdev *dev = NULL;
    int fd;
    int rc;

    fd = open(selected_device, O_RDWR | O_NONBLOCK);
    if (fd < 0) {
        log_error("Error opening device");
        return NULL;
    }

    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        log_error("Error creating evdev device");
        close(fd);
        return NULL;
    }

    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    while (is_monitoring) {
        rc = poll(fds, 1, MAX_POLL_TIMEOUT_MS);

        if (rc < 0) {
            log_error("Poll error");
            break;
        }

        if (rc == 0) {
            continue;
        }

        struct input_event events[EVENT_BUFFER_SIZE];
        int num_events = 0;

        while ((rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL,
                                         &events[num_events])) == 0) {
            if (events[num_events].type == EV_KEY) {
                num_events++;

                if (num_events >= EVENT_BUFFER_SIZE) {
                    break;
                }
            }
        }

        for (int i = 0; i < num_events; i++) {
            if (event_callback) {
                KeyName key_name = events[i].code;
                event_callback(key_name, events[i].value);
            }
        }

        if (rc != -EAGAIN) {
            log_error("Unexpected event reading error");
            break;
        }
    }

    libevdev_free(dev);
    close(fd);

    pthread_mutex_lock(&monitoring_mutex);
    is_monitoring = 0;
    pthread_mutex_unlock(&monitoring_mutex);

    return NULL;
}

int key_monitor_service_init(KeyEventCallback callback) {
    pthread_mutex_lock(&monitoring_mutex);
    if (is_monitoring) {
        pthread_mutex_unlock(&monitoring_mutex);
        return 0;
    }

    event_callback = callback;
    is_monitoring = 1;
    pthread_mutex_unlock(&monitoring_mutex);

    if (pthread_create(&monitor_thread, NULL, key_monitor_thread, NULL) != 0) {
        pthread_mutex_lock(&monitoring_mutex);
        is_monitoring = 0;
        pthread_mutex_unlock(&monitoring_mutex);
        return -1;
    }

    return 0;
}

void key_monitor_service_stop() {
    pthread_mutex_lock(&monitoring_mutex);
    if (is_monitoring) {
        is_monitoring = 0;
        pthread_mutex_unlock(&monitoring_mutex);
        pthread_join(monitor_thread, NULL);
    } else {
        pthread_mutex_unlock(&monitoring_mutex);
    }
}

int key_monitor_service_is_running() {
    pthread_mutex_lock(&monitoring_mutex);
    int status = is_monitoring;
    pthread_mutex_unlock(&monitoring_mutex);
    return status;
}
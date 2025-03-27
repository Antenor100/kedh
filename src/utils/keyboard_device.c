#include "../main.h"
#include "config_properties.h"
#include <errno.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_DEVICES_DIR (read_property("INPUT_DEVICES_DIR") ?: "/dev/input/")

int list_keyboard_devices(char devices[][G_MAX_PATH_LENGTH]) {
    struct libevdev *dev = NULL;
    int fd;
    char device_path[G_MAX_PATH_LENGTH];
    int device_count = 0;

    for (int i = 0; i < G_MAX_DEVICES && device_count < G_MAX_PATH_LENGTH;
         i++) {
        snprintf(device_path, sizeof(device_path), "%sevent%d",
                 INPUT_DEVICES_DIR, i);

        fd = open(device_path, O_RDONLY);
        if (fd < 0) {
            continue;
        }

        int rc = libevdev_new_from_fd(fd, &dev);
        if (rc < 0) {
            close(fd);
            continue;
        }

        if (libevdev_has_event_type(dev, EV_KEY)) {
            strncpy(devices[device_count], device_path, G_MAX_PATH_LENGTH);
            device_count++;
        }

        libevdev_free(dev);
        close(fd);
    }

    return device_count;
}

int read_configured_keyboard_device(char *device_path, size_t path_size) {
    const char *device_index = read_property("KEYBOARD_DEVICE_INDEX");
    const char *device_name = read_property("KEYBOARD_DEVICE_NAME");
    char devices[G_MAX_DEVICES][G_MAX_PATH_LENGTH];
    int device_count = list_keyboard_devices(devices);

    if (device_count == 0) {
        return 0;
    }

    if (device_index && *device_index) {
        int index = atoi(device_index);
        if (index > 0 && index <= device_count) {
            strncpy(device_path, devices[index - 1], path_size);
            return 1;
        }
    }

    if (device_name && *device_name) {
        struct libevdev *dev = NULL;
        int fd;

        for (int i = 0; i < device_count; i++) {
            fd = open(devices[i], O_RDONLY);
            if (fd < 0) {
                continue;
            }

            int rc = libevdev_new_from_fd(fd, &dev);
            if (rc < 0) {
                close(fd);
                continue;
            }

            const char *name = libevdev_get_name(dev);
            if (name && strcmp(name, device_name) == 0) {
                strncpy(device_path, devices[i], path_size);

                libevdev_free(dev);
                close(fd);
                return 1;
            }

            libevdev_free(dev);
            close(fd);
        }
    }

    return 0;
}

int choose_keyboard_device(char *selected_device) {
    char devices[G_MAX_DEVICES][G_MAX_PATH_LENGTH];
    int device_count = list_keyboard_devices(devices);

    if (device_count == 0) {
        printf("No keyboard devices found.\n");
        return 0;
    }

    if (device_count == 1) {
        strncpy(selected_device, devices[0], G_MAX_PATH_LENGTH);
        return 1;
    }

    printf("Available Keyboard Devices:\n");
    for (int i = 0; i < device_count; i++) {
        struct libevdev *dev = NULL;
        int fd = open(devices[i], O_RDONLY);
        if (fd < 0) continue;

        int rc = libevdev_new_from_fd(fd, &dev);
        if (rc < 0) {
            close(fd);
            continue;
        }

        const char *name = libevdev_get_name(dev);
        printf("%d: %s (%s)\n", i + 1, name ? name : "Unknown", devices[i]);

        libevdev_free(dev);
        close(fd);
    }

    int choice;
    printf("Enter the number of the device you want to use: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > device_count) {
        printf("Invalid selection. Please choose a number between 1 and %d.\n",
               device_count);
        return 0;
    }

    strncpy(selected_device, devices[choice - 1], G_MAX_PATH_LENGTH);

    char index_str[16];
    snprintf(index_str, sizeof(index_str), "%d", choice);

    if (!save_property("KEYBOARD_DEVICE_INDEX", index_str)) {
        printf("Could not save device index configuration.\n");
        return 0;
    }

    save_property("KEYBOARD_DEVICE_NAME", "");

    printf("Device saved as default.\n");
    return 1;
}

int find_keyboard_device_by_name(const char *device_name,
                                 char *selected_device) {
    char devices[G_MAX_DEVICES][G_MAX_PATH_LENGTH];
    int device_count = list_keyboard_devices(devices);

    if (device_count == 0) {
        printf("No keyboard devices found.\n");
        return 0;
    }

    struct libevdev *dev = NULL;
    int fd;

    for (int i = 0; i < device_count; i++) {
        fd = open(devices[i], O_RDONLY);
        if (fd < 0) {
            continue;
        }

        int rc = libevdev_new_from_fd(fd, &dev);
        if (rc < 0) {
            close(fd);
            continue;
        }

        const char *name = libevdev_get_name(dev);
        
        if (name && strcmp(name, device_name) == 0) {
            strncpy(selected_device, name, G_MAX_PATH_LENGTH);

            libevdev_free(dev);
            close(fd);

            if (!save_property("KEYBOARD_DEVICE_NAME", device_name)) {
                printf("Could not save device name configuration.\n");
                return 0;
            }

            save_property("KEYBOARD_DEVICE_INDEX", "");

            printf("Device '%s' found and saved as default.\n", device_name);
            return 1;
        }

        libevdev_free(dev);
        close(fd);
    }

    printf("No device found with name '%s'.\n", device_name);
    return 0;
}
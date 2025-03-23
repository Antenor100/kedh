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
    const char *configured_device = read_property("KEYBOARD_DEVICE");

    if (configured_device == NULL) {
        return 0;
    }

    if (strlen(configured_device) >= path_size) {
        return 0;
    }

    int fd = open(configured_device, O_RDONLY);
    if (fd < 0) {
        return 0;
    }

    struct libevdev *dev = NULL;
    int rc = libevdev_new_from_fd(fd, &dev);
    close(fd);

    if (rc < 0 || !libevdev_has_event_type(dev, EV_KEY)) {
        if (dev)
            libevdev_free(dev);
        return 0;
    }

    libevdev_free(dev);
    strncpy(device_path, configured_device, path_size);
    return 1;
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
        printf("%d: %s\n", i + 1, devices[i]);
    }

    int choice;
    printf("Enter the number of the device you want to use: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > device_count) {
        printf("Invalid selection. Please choose a number between 1 and %d.\n",
               device_count);
        return 0;
    }

    strncpy(selected_device, devices[choice - 1], G_MAX_PATH_LENGTH);

    if (!save_property("KEYBOARD_DEVICE", selected_device)) {
        printf("Could not save device configuration.\n");
        return 0;
    }

    printf("Device saved as default.\n");
    return 1;
}
#ifndef KEYBOARD_DEVICE_H
#define KEYBOARD_DEVICE_H

#include "../enums/key_names.h"
#include "../main.h"
#include "config_properties.h"
#include <libevdev-1.0/libevdev/libevdev.h>
#include <linux/input.h>

#define MAX_DEVICES (read_int_property("MAX_DEVICES", 30))

int choose_keyboard_device(char *selected_device);

int list_keyboard_devices(char devices[][G_MAX_PATH_LENGTH]);

int read_configured_keyboard_device(char *device_path, size_t path_size);

int find_keyboard_device_by_name(const char *device_name, char *selected_device);

#endif
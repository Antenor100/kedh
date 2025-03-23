#ifndef KEY_MONITOR_SERVICE_H
#define KEY_MONITOR_SERVICE_H

#include "../enums/key_names.h"
#include "../main.h"

typedef void (*KeyEventCallback)(KeyName key, int event_type);

int key_monitor_service_init(KeyEventCallback callback);

void key_monitor_service_stop();

int key_monitor_service_is_running();

#endif
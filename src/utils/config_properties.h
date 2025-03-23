#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <stdio.h>

#define MAX_PROP_LENGTH 256

char* read_property(const char* key);
int read_int_property(const char* key, int default_value);
int save_property(const char* key, const char* value);

#endif
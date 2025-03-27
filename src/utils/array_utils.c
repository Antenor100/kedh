#include "array_utils.h"
#include <string.h>

int contains_str(int argc, char *argv[], const char *flag) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], flag) == 0) {
            return 1;
        }
    }
    return 0;
}
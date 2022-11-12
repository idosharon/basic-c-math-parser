#include "log.h"

void warn(const char *msg) {
    printf("[Warning]: %s\n", msg);
}

void error(const char *msg) {
    printf("[Error]: %s\n", msg);
    exit(1);
}

void note(const char *msg) {
    printf("[Note]: %s\n", msg);
}

void status(const char *msg) {
    printf("[Status]: %s\n", msg);
}
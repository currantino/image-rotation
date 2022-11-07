#ifndef UTIL_H
#define UTIL_H

enum color { RED, GREEN, DEFAULT };

void log_err(const char *const message);

void log_ok(const char *const message);
static const char *const color_codes[] = {
    [RED] = "\x1B[31m", [GREEN] = "\x1B[32m", [DEFAULT] = "\x1B[0m"};
#endif

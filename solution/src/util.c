#include "util.h"

void log_ok(const char *const message)
{
	fprintf(stderr, "%s%s%s%s\n", color_codes[GREEN], "[ OK ]\t",
		color_codes[DEFAULT], message);
}

void log_err(const char *const message)
{
	if (errno) {
		fprintf(stderr, "%s%s%s%s: %s\n", color_codes[RED],
			"[ ERROR ]\t", color_codes[DEFAULT], message,
			strerror(errno));
	} else {
		fprintf(stderr, "%s%s%s%s\n", color_codes[RED], "[ ERROR ]\t",
			color_codes[DEFAULT], message);
	}
}

void log_msg(const char *const message)
{
	errno == 0 ? log_ok(message) : log_err(message);
}

void err(const char *const message) { fprintf(stderr, "%s\n", message); }

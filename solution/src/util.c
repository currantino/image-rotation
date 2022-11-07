#include <stdio.h>

#include "util.h"

void log_ok(const char *const message)
{
	fprintf(stderr, "%s%s%s%s\n", color_codes[GREEN], "[ OK ]\t",
		color_codes[DEFAULT], message);
}

void log_err(const char *const message)
{
	fprintf(stderr, "%s%s%s%s\n", color_codes[RED], "[ ERROR ]\t",
		color_codes[DEFAULT], message);
}

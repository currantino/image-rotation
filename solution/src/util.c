#include <stdio.h>

#include "util.h"

void err(char *message, enum color color)
{
	switch (color) {
	case RED: {
		fprintf(stderr, "\x1B[31m");
		fprintf(stderr, "[ ERROR ]");
		break;
	}
	case GREEN: {
		fprintf(stderr, "\x1B[32m");
		fprintf(stderr, "[ OK ]");
		break;
	}
	}
	fprintf(stderr, "\x1B[0m");
	fprintf(stderr, "%s\n", message);
}

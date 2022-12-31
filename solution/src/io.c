#include "io.h"

static const char *file_open_msg[] = {
    [OPEN_SUCCESS] = "File was successfully opened.",
    [OPEN_FAILURE] = "File could not be opened."};

static const char *file_close_msg[] = {
    [CLOSE_SUCCESS] = "File was successfully closed.",
    [CLOSE_FAILURE] = "File could not be closed."};

const char *get_file_open_msg(enum file_open_status file_open_status)
{
	return file_open_msg[file_open_status];
}
const char *get_file_close_msg(enum file_close_status file_close_status)
{
	return file_close_msg[file_close_status];
}

static const char *const file_open_modes[] = {
    [WRITE_BINARY] = "wb", [READ_BINARY] = "rb"};

enum file_open_status image_open_stream(const char *path,
					enum file_open_mode mode, FILE *stream)
{
	const char *mode_string = file_open_modes[mode];
	FILE *file = fopen(path, mode_string);
	if (file) {
		stream = file;
		return OPEN_SUCCESS;
	} else {
		return OPEN_FAILURE;
	}
}

enum file_close_status image_close_stream(FILE *stream)
{
	if (fclose(stream) == 0) {
		return CLOSE_SUCCESS;
	} else {
		return CLOSE_FAILURE;
	}
}

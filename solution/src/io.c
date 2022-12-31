#include "io.h"

static const char *stream_open_msg[] = {
    [OPEN_SUCCESS] = "File was successfully opened.",
    [OPEN_FAILURE] = "File could not be opened."};

static const char *stream_close_msg[] = {
    [CLOSE_SUCCESS] = "File was successfully closed.",
    [CLOSE_FAILURE] = "File could not be closed."};

const char *get_stream_open_msg(enum stream_open_status stream_open_status)
{
	return stream_open_msg[stream_open_status];
}
const char *get_stream_close_msg(enum stream_close_status stream_close_status)
{
	return stream_close_msg[stream_close_status];
}

static const char *const stream_open_modes[] = {
    [WRITE_BINARY] = "wb", [READ_BINARY] = "rb"};

enum stream_open_status
stream_open(const char *path, enum stream_open_mode mode, FILE **stream_ptr)
{
	const char *mode_string = stream_open_modes[mode];
	*stream_ptr = fopen(path, mode_string);
	if (*stream_ptr) {
		return OPEN_SUCCESS;
	} else {
		return OPEN_FAILURE;
	}
}

enum stream_close_status stream_close(FILE *stream)
{
	if (fclose(stream) == 0) {
		return CLOSE_SUCCESS;
	} else {
		return CLOSE_FAILURE;
	}
}

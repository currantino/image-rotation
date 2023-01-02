#include "io.h"

static const char *stream_open_msg[] = {
    [OPEN_SUCCESS] = "File was successfully opened",
    [OPEN_FAILURE] = "File could not be opened"};

static const char *stream_close_msg[] = {
    [CLOSE_SUCCESS] = "File was successfully closed",
    [CLOSE_FAILURE] = "File could not be closed"};

static const char *const read_status_msg[] = {
    [READ_OK] = "File read successfully",
    [READ_HEADER_ERROR] = "File header could not be read",
    [READ_ERROR] = "File could not be read",
    [READ_UNEXPECTED_EOF] = "Unexpected EOF"};

static const char *const write_status_msg[] = {
    [WRITE_OK] = "File written successfully",
    [WRITE_HEADER_ERROR] = "File header could not be read",
    [WRITE_ERROR] = "File could not be written"};

const char *get_stream_open_msg(enum stream_open_status stream_open_status)
{
	return stream_open_msg[stream_open_status];
}

const char *get_stream_close_msg(enum stream_close_status stream_close_status)
{
	return stream_close_msg[stream_close_status];
}

const char *get_read_status_msg(enum read_status read_status)
{
	return read_status_msg[read_status];
}

const char *get_write_status_msg(enum write_status write_status)
{
	return write_status_msg[write_status];
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

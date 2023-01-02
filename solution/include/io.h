#ifndef IO_H
#define IO_H

#include <stdio.h>

enum stream_open_status { OPEN_SUCCESS = 0, OPEN_FAILURE };

enum stream_close_status { CLOSE_SUCCESS = 0, CLOSE_FAILURE };

enum read_status {
	READ_OK = 0,
	READ_HEADER_ERROR,
	READ_ERROR,
	READ_UNEXPECTED_EOF
};

enum write_status { WRITE_OK = 0, WRITE_HEADER_ERROR, WRITE_ERROR };

enum stream_open_mode { READ_BINARY, WRITE_BINARY };

enum stream_open_status stream_open(const char *path,
				    enum stream_open_mode mode, FILE **stream);

enum stream_close_status stream_close(FILE *stream);

const char *get_stream_open_msg(enum stream_open_status stream_open_status);

const char *get_stream_close_msg(enum stream_close_status stream_close_status);

#endif

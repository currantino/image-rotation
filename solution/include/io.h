#ifndef IO_H
#define IO_H

#include <stdio.h>

enum stream_open_status { OPEN_SUCCESS, OPEN_FAILURE };

enum stream_close_status { CLOSE_SUCCESS, CLOSE_FAILURE };

enum stream_open_mode { READ_BINARY, WRITE_BINARY };

enum stream_open_status stream_open(const char *path,
				    enum stream_open_mode mode, FILE **stream);

enum stream_close_status stream_close(FILE *stream);

const char *get_stream_open_msg(enum stream_open_status stream_open_status);

const char *get_stream_close_msg(enum stream_close_status stream_close_status);

#endif

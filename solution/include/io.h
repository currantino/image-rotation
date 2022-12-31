#ifndef IO_H
#define IO_H

#include <stdio.h>

enum file_open_status { OPEN_SUCCESS, OPEN_FAILURE };

enum file_close_status { CLOSE_SUCCESS, CLOSE_FAILURE };

enum file_open_mode { READ_BINARY, WRITE_BINARY };

enum file_open_status image_open_stream(const char *path,
					enum file_open_mode mode, FILE *stream);

enum file_close_status image_close_stream(FILE *stream);

const char *get_file_open_msg(enum file_open_status file_open_status);

const char *get_file_close_msg(enum file_close_status file_close_status);

#endif

#ifndef BIT_IO_H
#define BIT_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    FILE *file;
    unsigned buffer;
    unsigned char buffer_mask;
}bit_file_handler;


bit_file_handler* write_bit_init(const char *filename);

void write_bit(bit_file_handler *handler, bool bit);

void flush_write_bit(bit_file_handler *handler);

bit_file_handler* read_bit_init(const char *filename);

bool read_bit(bit_file_handler *handler);

bool has_next_bit(bit_file_handler *handler);

void bit_file_handler_close(bit_file_handler *handler);

#endif //BIT_IO_H
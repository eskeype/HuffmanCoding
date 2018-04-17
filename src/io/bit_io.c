#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bit_io.h"

bit_file_handler* write_bit_init(const char *filename){
	bit_file_handler* handler = (bit_file_handler*) malloc(sizeof(bit_file_handler));
	
	handler -> file = fopen(filename, "wb");
	handler -> buffer = 0;
	handler -> buffer_mask = 0x80;

	return handler;

}

void write_bit(bit_file_handler *handler, bool bit){
	if(bit){
		handler -> buffer |= handler -> buffer_mask;
	}

	handler -> buffer_mask = (handler -> buffer_mask) >> 1;

	if((handler -> buffer_mask) == 0){
		fputc(handler -> buffer, handler -> file);
	
		handler -> buffer = 0;
		handler -> buffer_mask = 0x80;
	}
}

void flush_write_bit(bit_file_handler *handler){
	for(int i = 0; i < (8*sizeof(char) - 1); i++){
		write_bit(handler, false);
	}
}

bit_file_handler* read_bit_init(const char *filename){
	bit_file_handler* handler = (bit_file_handler*) malloc(sizeof(bit_file_handler));
	
	handler -> file = fopen(filename, "rb");
	handler -> buffer = fgetc(handler -> file);
	handler -> buffer_mask = 0x80;

	return handler;
}

bool read_bit(bit_file_handler *handler){

	bool out = (handler -> buffer_mask & handler -> buffer) != 0;
	handler -> buffer_mask = handler -> buffer_mask >> 1;

	if((handler -> buffer_mask) == 0){
		handler -> buffer = fgetc(handler -> file);
		handler -> buffer_mask = 0x80;
	}

	return out;
}

bool has_next_bit(bit_file_handler *handler){
	return handler -> buffer != EOF;
}

void bit_file_handler_close(bit_file_handler *handler){
	fclose(handler -> file);
	free(handler);
}

#ifndef MAIN
#define MAIN
int main(){

	//Very basic test - input 10 1's into file text.txt - check that we get 10 1's padded by 0's
	char* filename = "test.txt";

	bit_file_handler* handler = write_bit_init(filename);
	for(int i = 0; i<10; i++){
		write_bit(handler, true);
	}

	flush_write_bit(handler);
	bit_file_handler_close(handler);

	handler = read_bit_init(filename);
	while(has_next_bit(handler)){
		printf("%d\n", read_bit(handler)?1:0);
	}
	bit_file_handler_close(handler);
	return 0;
}
#endif //MAIN
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int open_file(char* filename, char* op);

int write_output_files(char* regout_file, char* memout_file, char* cycles_file);

void append_trace(void);

void load_mem(void);

void init(void);

#endif
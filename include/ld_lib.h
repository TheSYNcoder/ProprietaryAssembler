#ifndef LD_LIB_H
#define LD_LIB_H

#include <main.h>
#include <object_code.h>
#include <fcntl.h>
#include <unistd.h>

#define CODE_OFFSET 12
#define START 0x100

/*
 * main linker function
 * args: input file, output file
 * returns: 0 on SUCCESS
 * returns: -1 on ERROR
 */
int link(const char *input_file, const char *output_file);

#endif

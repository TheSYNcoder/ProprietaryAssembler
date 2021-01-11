#ifndef SECOND_PASS_PARSE_H
#define SECOND_PASS_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* O - Opcode,
	R - Register
	S - Symbol
	L - Direct Addressing
	DB - comes with value, hence token: type - DB, value - value with DB token
	DW
	DD
*/
enum TOKEN_TYPES
{
	O,
	R,
	S,
	L,
	DB,
	DW,
	DD
} TOKEN_TYPES;

typedef struct token
{
	int type;
	int value; // value in decimal
} second_pass_token;

typedef struct l
{
	int len;
	second_pass_token *tokens;
} line;

/*
 * Replace main in second_pass_parse.c with this function
 * args : const char *filename
 * returns: line (all tokens for the file, not line wise)
 */
line parse_intermediate_file(const char *filename);

#endif

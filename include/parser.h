#ifndef PARSER_H
#define PARSER_H
#include <main.h>

typedef struct Token
{
    int length;    // how many character in the word
    char word[10]; // actual opcode or operand
} Token;

typedef struct Line
{
    int length; // how many Token exists in a line
    Token tokens[3];
} Line;

void parse(char *);
extern void validate_and_find(Line *);

#endif

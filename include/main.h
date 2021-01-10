#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
Necessary structs defined here
*/
#define ASSEMBLY_FILE_EXTENSION ".pasm"

typedef struct op_tab_node{

    int sl_no; /* serial number of opcode */
    char *symbol; /* The mnemonic such as ADD, SUB */
    char *opcode; /* The opcode referring to the mnemonic */
    int length; /* The length of the instruction */
    char *add_mode; /* the addressing mode - relative, absolute etc */

}op_tab_node;



typedef struct sym_tab_node{

    int sl_no;     /* serial number of opcode */
    char *label;   /* The mnemonic such as ADD, SUB */
    int defined;    /* The Label is defined  */
    int LC;    /* The current LC */
    
}sym_tab_node;


int current_lc;

sym_tab_node symbol_table[1000];
int num_symbols;

typedef struct Token
{
    int length; // how many character in the word
    char word[10]; // actual opcode or operand
}Token;

typedef struct Line
{
    int length; // how many Token exists in a line
    Token tokens[3];
}Line;



#endif
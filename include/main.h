#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
Necessary structs defined here
*/

typedef struct op_tab_node{

    int32_t sl_no; /* serial number of opcode */
    char *symbol; /* The mnemonic such as ADD, SUB */
    char *opcode; /* The opcode referring to the mnemonic */
    int32_t length; /* The length of the instruction */
    char *add_mode; /* the addressing mode - relative, absolute etc */

}op_tab_node;


typedef struct sym_tab_node{

    int32_t sl_no;     /* serial number of opcode */
    char *label;   /* The mnemonic such as ADD, SUB */
    int defined;    /* The Label is defined  */
    int32_t LC;    /* The current LC */
    
}sym_tab_node;


extern int current_lc;

extern sym_tab_node symbol_table[1000];
extern int num_symbols;

#endif
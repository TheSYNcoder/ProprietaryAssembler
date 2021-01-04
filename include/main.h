#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
/*
Necessary structs defined here
*/

typedef struct op_tab_node{

    int32_t sl_no; /* serial number of opcode */
    char symbol[10]; /* The mnemonic such as ADD, SUB */
    char opcode[5]; /* The opcode referring to the mnemonic */
    int32_t length; /* The length of the instruction */
    char add_mode[20]; /* the addressing mode - relative, absolute etc */

}op_tab_node;


#endif
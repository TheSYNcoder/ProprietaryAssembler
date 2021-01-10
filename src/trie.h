#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/main.h"
#define CHAR_SIZE 44 //letters(26)+numbers(10)+ / +$ + () + []   + ' ' +  ; 


struct Trie
{
    int isLeaf;
    op_tab_node *pointer;
    struct Trie *character[CHAR_SIZE];
};



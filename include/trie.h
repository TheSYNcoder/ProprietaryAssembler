#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define CHAR_SIZE 44 //letters(26)+numbers(10)+ / +$ + () + []   + ' ' +  ; 


struct Trie
{
    int isLeaf;
    op_tab_node *pointer;
    struct Trie *character[CHAR_SIZE];
};

struct Trie *head;
struct Trie *makeTrie(int col, char *filename);
op_tab_node *def_search(struct Trie *head, char *str);

#endif



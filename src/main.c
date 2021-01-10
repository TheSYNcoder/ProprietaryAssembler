#include "main.h"
#include "trie.h"
#include "parser.h"


int32_t main(int argc , char *argv[]){


    if ( argc < 2) {
        printf("Filename not entered\n");
        return 0;
    }
    if ( argc > 2){
        printf("Usage : pasm <filename.asm>\n");
        return 0;
    }
    // parse the opcodes
    head = makeTrie( 4, "./opcodes.csv");

    // op_tab_node *node = def_search(head, "ADDR/M8; REG8");
    // if ( node == NULL){
    //     printf("Opcode not found");
    // }
    // else
    // printf("%s" , node->opcode);

    // write to intermediate file
    parse(argv[1]);

    






}

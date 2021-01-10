#include "main.h"


int32_t main(){
    op_tab_node node;
    node.sl_no= 1;
    node.length = 3;
    strcpy(node.opcode,"ADD");
    strcpy(node.add_mode,"something");

    printf("%s", node.opcode);
}

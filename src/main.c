#include "main.h"
#include "trie.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    current_lc = 0;
    if (argc != 3)
    {
        printf("Usage: ./pasm <in.pasm>  <out.obj>\n");
        return 0;
    }
    // parse the opcodes
    head = makeTrie(4, "./opcodes.csv");

    // write to intermediate file
    parse(argv[1]);

    // generate object code
    generate_object_code(INTERMEDIATE_FILE, argv[2]);

    return 0;
}

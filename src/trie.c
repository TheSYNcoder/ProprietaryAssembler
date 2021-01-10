#include "trie.h"

struct Trie *getNewTrieNode()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }
    node->pointer = NULL;
    return node;
}


int indexTrie(char ch)
{
    //returns index of a character in the character array in trie
    if (ch >= 65 && ch <= 90)
    {
        return (ch - 65);
    }
    else if (ch >= 48 && ch < 58)
    {
        return (ch - 48 + 26);
    }
    else if (ch == '$')
    {
        return 36;
    }
    else if (ch == '/')
    {
        return 37;
    }
    else if (ch == '(')
    {
        return 38;
    }
    else if (ch == ')')
    {
        return 39;
    }
    else if (ch == '[')
    {
        return 40;
    }
    else if (ch == ']')
    {
        return 41;
    }
    else if (ch == ' ')
    {
        return 42;
    }
    else if (ch == ';')
    {
        return 43;
    }
}
void insert(struct Trie *head, char *str, op_tab_node *n)
{
    //basic trie insert
    struct Trie *curr = head;
    while (*str)
    {
        if (curr->character[indexTrie(*str)] == NULL)
        {
            curr->character[indexTrie(*str)] = getNewTrieNode();
        }
        curr = curr->character[indexTrie(*str)];
        str++;
    }
    curr->isLeaf = 1;
    curr->pointer = n;
}



op_tab_node *search(struct Trie *head, char *str)
{
    //basic trie search
    if (head == NULL)
        return 0;

    struct Trie *curr = head;
    while (*str)
    {
        curr = curr->character[indexTrie(*str)];
        if (curr == NULL)
            return NULL;

        str++;
    }



struct Trie *makeTrie(int col, char *filename)
{
    
    head = getNewTrieNode();
    FILE *file = fopen(filename, "r");
    char line[100];
    int i = 0;
    while (fgets(line, 100, file))
    {
        //parses csv line by line
        int j = 0;
        const char *tok;
        op_tab_node* new_node = (op_tab_node*)malloc(sizeof(op_tab_node));
        new_node->sl_no = i;
        char *tmp = strdup(line);
        tok = strtok(line, ",");// tok is the first token
        while (tok != NULL)
        {
            if (j == 0)
            {//first column element
                strcpy(new_node->symbol, tok);
            }
            else if (j == 1)
            {//second column element
                strcpy(new_node->opcode, tok);
            }
            else if (j == 2)
            {//third column element
                strcpy(new_node->add_mode, tok);
            }
            else if (j == 3)
            {//fourth column element
                new_node->length = tok[0] - 48;
            }
            else if (j == col)
            {//breaks because no more columns 
                break;
            }
            tok = strtok(NULL, ",");//updates tok to the next token
            j++;
        }
        char key[30] = "";//creates a key which is opcode+addressing mode
        strcat(key, new_node->opcode);
        strcat(key, new_node->add_mode);
        //printf("%s\n", key);
        insert(head, key, new_node);//inserts into trie
        //char newkey[30] = "PORT[DX]; AL"
       
        free(tmp);
        i++;
    }
    return head;//returns head of the trie
}




int main(int argc, char const *argv[])
{
    //struct Trie *tree = makeTrie(134, 4, "input3");
    /*if(argc < 3){
        printf("Please specify the CSV file as an input\n");
        exit(0);
    }

    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    char fname[256];
    strcpy(fname, argv[3]);

    struct Trie* tree = makeTrie(row, col, fname);
    */

   //how to use
   struct Trie* tree = makeTrie(4, "../opcodes.csv");
    op_tab_node* n = search(tree, "$C216BIT POP");
    if(n != NULL){
        printf("%s %s %s %d\n", n->symbol, n->opcode, n->add_mode, n->length);
    }
  
}



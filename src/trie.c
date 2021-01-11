#include <trie.h>

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

op_tab_node *def_search(struct Trie *head, char *str)
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
    return curr->pointer;
}

struct Trie *makeTrie(int col, char *filename)
{

    head = getNewTrieNode();
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        exit(0);
    }
    char line[100];
    int i = 0;
    while (fgets(line, 100, file))
    {
        //parses csv line by line
        int j = 0;
        char *tok;
        op_tab_node *new_node = (op_tab_node *)malloc(sizeof(op_tab_node));
        if (new_node == NULL)
        {
            printf("Malloc failed\n");
        }
        // printf("2\n");
        new_node->sl_no = i;
        char *tmp = strdup(line);
        char *rnd;
        tok = strtok_r(line, ",", &rnd); // tok is the first token

        while (tok != NULL)
        {

            if (j == 0)
            { //first column element
                // strcpy(new_node->symbol, tok);
                char *buff = malloc(30);
                strcpy(buff, tok);
                new_node->symbol = buff;
            }
            else if (j == 1)
            { //second column element
                // strcpy(new_node->opcode, tok);
                char *buff = malloc(30);
                strcpy(buff, tok + 1);
                new_node->opcode = buff;
            }
            else if (j == 2)
            { //third column element
                // strcpy(new_node->add_mode, tok);
                char *buff = malloc(30);
                strcpy(buff, tok);
                new_node->add_mode = buff;
            }
            else if (j == 3)
            { //fourth column element
                new_node->length = tok[0] - 48;
            }
            else if (j == col)
            { //breaks because no more columns
                break;
            }
            // printf("148\n");
            tok = strtok_r(NULL, ",", &rnd); //updates tok to the next token
            // printf("150\n");
            j++;
        }

        char key[30] = ""; //creates a key which is opcode+addressing mode
        strcat(key, new_node->symbol);
        strcat(key, new_node->add_mode);
        // printf("%s\n", key);
        insert(head, key, new_node); //inserts into trie
        //char newkey[30] = "PORT[DX]; AL"

        free(tmp);
        i++;
    }
    return head; //returns head of the trie
}

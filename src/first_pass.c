#include <first_pass.h>

int get_code_for_register(char *reg_name)
{

    int len = strlen(reg_name);
    int i;
    for (i = 0; i < len; i++)
    {
        reg_name[i] = toupper(reg_name[i]);
    }

    if (strcmp(reg_name, "AL") == 0)
    {
        return 0;
    }
    if (strcmp(reg_name, "CL") == 0)
    {
        return 1;
    }
    if (strcmp(reg_name, "DL") == 0)
    {
        return 2;
    }
    if (strcmp(reg_name, "BL") == 0)
    {
        return 3;
    }
    if (strcmp(reg_name, "AH") == 0)
    {
        return 4;
    }
    if (strcmp(reg_name, "CH") == 0)
    {
        return 5;
    }
    if (strcmp(reg_name, "DH") == 0)
    {
        return 6;
    }
    if (strcmp(reg_name, "BH") == 0)
    {
        return 7;
    }
    if (strcmp(reg_name, "AX") == 0)
    {
        return 8;
    }
    if (strcmp(reg_name, "CX") == 0)
    {
        return 9;
    }
    if (strcmp(reg_name, "DX") == 0)
    {
        return 10;
    }
    if (strcmp(reg_name, "BX") == 0)
    {
        return 11;
    }
    if (strcmp(reg_name, "SP") == 0)
    {
        return 12;
    }
    if (strcmp(reg_name, "BP") == 0)
    {
        return 13;
    }
    if (strcmp(reg_name, "SI") == 0)
    {
        return 14;
    }
    if (strcmp(reg_name, "DI") == 0)
    {
        return 15;
    }
    if (strcmp(reg_name, "ES") == 0)
    {
        return 16;
    }
    if (strcmp(reg_name, "CS") == 0)
    {
        return 17;
    }
    if (strcmp(reg_name, "SS") == 0)
    {
        return 18;
    }
    if (strcmp(reg_name, "SS") == 0)
    {
        return 19;
    }

    return -1;
}

int symtable_function(char *token, int define)
{
    int pos;
    for (pos = 0; pos < num_symbols; pos++)
        if (strcmp(token, symbol_table[pos].label) == 0)
            break;

    if (pos == num_symbols)
    {
        sym_tab_node node;
        node.defined = 0;
        node.label = malloc(100);
        strcpy(node.label, token);
        node.sl_no = num_symbols;
        symbol_table[num_symbols++] = node;
        pos = num_symbols - 1;
    }

    if (define)
    {

        if (!symbol_table[pos].defined)
        {
            symbol_table[pos].defined = 1;
            symbol_table[pos].LC = current_lc;
            // printf("%s %d %d\n", symbol_table[pos].label, symbol_table[pos].LC, __LINE__);
        }
        else
        {
            printf("MULTIPLE SYMBOL DEFINITON  %s \n", token);
            exit(0);
        }
    }
    return 0;
}

void dfs(struct Trie *tmp, int *current_opcodes, int *size, op_tab_node **opcodes)
{
    if (tmp == NULL)
        return;

    if (tmp->isLeaf)
    {
        opcodes[*current_opcodes] = (tmp->pointer);
        *current_opcodes = *current_opcodes + 1;
    }

    int i;
    for (i = 0; i < CHAR_SIZE; i++)
    {
        dfs(tmp->character[i], current_opcodes, size, opcodes);
    }
}

op_tab_node **search(struct Trie *head, char *opcode, int *current_opcodes)
{
    // opcode is ADD
    if (head == NULL)
        return NULL;

    struct Trie *temp = head;

    int size_optabs = 40;
    op_tab_node **opcode_tabs = (op_tab_node **)malloc(size_optabs * sizeof(op_tab_node *));

    int len = strlen(opcode);

    int i;

    for (i = 0; i < len; i++)
    {
        if (temp->character[indexTrie(toupper(opcode[i]))] == NULL)
        {
            printf("Opcode not found\n");
            return NULL;
        }
        temp = temp->character[indexTrie(opcode[i])];
    }

    dfs(temp, current_opcodes, &size_optabs, opcode_tabs);
    // opcode_tabs = (op_tab_node **) realloc(opcode_tabs , (*current_opcodes) * sizeof(op_tab_node *));

    return opcode_tabs;
}

char *strip(char *line)
{
    char *s = strdup(line);
    int len = strlen(s);
    char *back = s + len;
    while (*back == ' ')
        back--;
    *(back + 1) = '\0';
    while (*s == ' ')
        s++;
    return s;
}

int check_number(char *s)
{
    int d = atoi(s);
    // not a number
    if (d == 0)
        return 0;

    /**
     * Accepted numbers of typed 00123 or 1234H
     * 0x1223 not supported 
     */
    int num_digs = 0, num_chars = 0;

    for (; *s; s++)
    {
        if (isxdigit(*s))
            num_digs++;
        else
            num_chars++;
    }

    if (num_chars <= 1)
    {
        if (num_chars == 0)
            return 1;
        if (tolower(s[strlen(s) - 1]) == 'h')
            return 1;
    }

    return 0;
}

char *upper_token(char *s)
{
    char *ret = malloc(sizeof(char) * strlen(s));
    int i;
    for (i = 0; i < strlen(s); i++)
        ret[i] = toupper(s[i]);
    ret[i] = 0;
    return ret;
}

int check_reg_var_pair(char *operand, char *token)
{
    if (strcmp("AX", operand) == 0)
    {
        return strcmp(upper_token(token), "AX") == 0;
    }
    if (strcmp("REG16(AX)", operand) == 0)
    {
        return strcmp(upper_token(token), "AX") == 0;
    }
    if (strcmp("REG16(BP)", operand) == 0)
    {
        return strcmp(upper_token(token), "BP") == 0;
    }
    if (strcmp("REG16(CX)", operand) == 0)
    {
        return strcmp(upper_token(token), "CX") == 0;
    }
    if (strcmp("REG16(BX)", operand) == 0)
    {
        return strcmp(upper_token(token), "BX") == 0;
    }
    if (strcmp("REG16(DI)", operand) == 0)
    {
        return strcmp(upper_token(token), "DI") == 0;
    }
    if (strcmp("REG16(DX)", operand) == 0)
    {
        // printf("%d %d\n", strcmp(upper_token(token), "DX"), __LINE__);
        return strcmp(upper_token(token), "DX") == 0;
    }
    if (strcmp("REG16(SI)", operand) == 0)
    {
        return strcmp(upper_token(token), "SI") == 0;
    }
    if (strcmp("REG16(SP)", operand) == 0)
    {
        return strcmp(upper_token(token), "SP") == 0;
    }
    if (strcmp("REG8(AH)", operand) == 0)
    {
        return strcmp(upper_token(token), "AH") == 0;
    }
    if (strcmp("REG8(AL)", operand) == 0)
    {
        return strcmp(upper_token(token), "AL") == 0;
    }
    if (strcmp("REG8(BH)", operand) == 0)
    {
        return strcmp(upper_token(token), "BH") == 0;
    }
    if (strcmp("REG8(BL)", operand) == 0)
    {
        return strcmp(upper_token(token), "BL") == 0;
    }
    if (strcmp("REG8(CH)", operand) == 0)
    {
        return strcmp(upper_token(token), "CH") == 0;
    }
    if (strcmp("REG8(CL)", operand) == 0)
    {
        return strcmp(upper_token(token), "CL") == 0;
    }
    if (strcmp("REG8(DH)", operand) == 0)
    {
        return strcmp(upper_token(token), "DH") == 0;
    }
    if (strcmp("REG8(DL)", operand) == 0)
    {
        return strcmp(upper_token(token), "DL") == 0;
    }

    if (strcmp("AL", operand) == 0)
    {
        return strcmp(upper_token(token), "AL") == 0;
    }
    if (strcmp("AH", operand) == 0)
    {
        return strcmp(upper_token(token), "AH") == 0;
    }
    if (strcmp("CS", operand) == 0)
    {
        return strcmp(upper_token(token), "CS") == 0;
    }
    if (strcmp("DS", operand) == 0)
    {
        return strcmp(upper_token(token), "DS") == 0;
    }
    if (strcmp("ES", operand) == 0)
    {
        return strcmp(upper_token(token), "ES") == 0;
    }
    /*
    if (strcmp("MEM16", operand) == 0 || strcmp(operand, "MEM8") == 0)
    {
        return !check_number(token);
    }
    */

    if (strcmp("REG8", operand) == 0)
    {
        int code = get_code_for_register(token);
        if (code >= 0 && code < 8)
            return 1;
        // if (strcmp("R/M8", operand) == 0)
        //     return !check_number(token);
        return 0;
    }
    if (strcmp("REG16", operand) == 0)
    {
        int code = get_code_for_register(token);
        if (code >= 8 && code < 12)
            return 1;
        // if (strcmp("R/M16", operand) == 0)
        //     return !check_number(token);
        return 0;
    }
    if (strcmp("IMM16", operand) == 0 || strcmp(operand, "IMM8") == 0)
    {
        return 1;
    }

    return 0;
}

void validate_and_find(Line *line)
{

    // char **tokens , int num_tokens
    //
    // line->token[0]->word
    int num_tokens = line->length;
    char **tokens = malloc(num_tokens * sizeof(char *));
    int i, j, flag = 1, start_token = 0, temp, current_token = 0;

    for (i = 0; i < num_tokens; i++)
    {
        tokens[i] = malloc((line->tokens[i].length) * sizeof(char));
        tokens[i] = line->tokens[i].word;
        // printf("%s ", tokens[i]);
    }
    // printf("\n");

    op_tab_node *node = NULL;
    if (num_tokens == 0)
        return;

    FILE *fp;
    fp = fopen(INTERMEDIATE_FILE, "a");
    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        exit(0);
    }

    char *identifier, buffer[4];
    if (tokens[0][strlen(tokens[0]) - 1] == ':')
    {
        start_token++;
    }

    if (!(strcmp(tokens[start_token], "DB") && strcmp(tokens[start_token], "DW") && strcmp(tokens[start_token], "DQ")))
    {
        if (tokens[start_token + 1][0] == '"')
        {
            int ptr = 1;
            while (tokens[start_token + 1][ptr] != '"')
            {
                int val = tokens[start_token + 1][ptr];

                long int remainder, quotient;
                int i = 1, j, temp;
                char hexadecimalNumber[100];

                quotient = val;
                // printf("%d\n", val);
                while (quotient != 0)
                {
                    temp = quotient % 16;
                    //To convert integer into character
                    if (temp < 10)
                        temp = temp + 48;
                    else
                        temp = temp + 55;
                    hexadecimalNumber[i++] = temp;
                    quotient = quotient / 16;
                }
                fprintf(fp, "%s", tokens[start_token]);
                for (j = i - 1; j < 4; j++)
                    fprintf(fp, "%c", '0');
                for (j = i - 1; j > 0; j--)
                    fprintf(fp, "%c", hexadecimalNumber[j]);
                fprintf(fp, "\n");
                // fprintf(fp, "%s%04d\n", tokens[start_token], val);
                ptr++;
            }
        }
        else
        {
            fprintf(fp, "%s", tokens[start_token]);
            int len = 4 - strlen(tokens[start_token + 1]);

            for (i = 0; i < len; i++)
                fprintf(fp, "%s", "0");
            fprintf(fp, "%s\n", tokens[start_token + 1]);
            // temp = symtable_function(identifier, 1);
        }
        char *identifier = malloc(sizeof(char) * strlen(tokens[0]));
        for (i = 0; i < strlen(tokens[0]) - 1; i++)
            identifier[i] = tokens[0][i];
        identifier[strlen(tokens[0]) - 1] = '\0';
        identifier = upper_token(identifier);
        temp = symtable_function(identifier, 1);

        if (strcmp(tokens[start_token], "DB") == 0)
        {
            current_lc++;
        }
        if (strcmp(tokens[start_token], "DW") == 0)
        {
            current_lc += 2;
        }
        if (strcmp(tokens[start_token], "DQ") == 0)
        {
            current_lc += 4;
        }
    }
    else
    {

        char *opcode = tokens[start_token++];
        int num_opcodes = 0;

        // check in opcode trie
        op_tab_node **opcodes = search(head, opcode, &num_opcodes);

        if (opcodes == NULL || num_opcodes == 0)
        {
            printf("Error no opcodes %d\n", __LINE__);
            return;
        }

        for (i = 0; i < num_opcodes; i++)
        {
            flag = 1;

            char *add_mode = opcodes[i]->add_mode;
            char *modes[2];
            int c = 0;

            char *tmp = strdup(add_mode);
            char *t = NULL, *tok = tmp;
            char *s;
            while ((t = strtok(tok, ";")) != NULL)
            {
                tok = NULL;
                s = strip(t);
                modes[c++] = s;
            }

            if (num_tokens - start_token < c)
            {
                printf("Wrong syntax %d\n", __LINE__);
                return;
            }

            for (j = 0; j < c; j++)
            {
                if (!check_reg_var_pair(modes[j], tokens[start_token + j]))
                {
                    flag = 0;
                }
            }

            if (flag)
                break;
        }
        temp = (i < num_opcodes - 1 ? i : num_opcodes - 1);

        if (temp != num_opcodes)
        {

            fprintf(fp, "%s", "O");
            int len = strlen(opcodes[temp]->opcode);

            for (i = 0; i < 4 - len; i++)
                fprintf(fp, "%c", '0');

            fprintf(fp, "%s ", opcodes[temp]->opcode);

            for (i = start_token; i < num_tokens; i++)
            {

                int reg_code = get_code_for_register(tokens[i]);

                if (reg_code == -1)
                {
                    if (check_number(tokens[i]))
                    {
                        int len_l = strlen(tokens[i]);
                        if (tokens[i][len_l - 1] == 'H')
                        {
                            tokens[i][--len_l] = 0;
                        }
                        fprintf(fp, "L");
                        for (int pp = 0; pp < 4 - len_l; pp++)
                            fprintf(fp, "%c", '0');
                        fprintf(fp, "%s", tokens[i]);
                    }
                    else
                    {

                        temp = symtable_function(tokens[i], 0);

                        fprintf(fp, "%s%04d", "S", num_symbols - 1);
                    }
                }
                else
                {
                    fprintf(fp, "%s%04d", "R", reg_code);
                }
                if (i != num_tokens - 1)
                    fprintf(fp, " ");
                else
                    fprintf(fp, "\n");
            }
            current_lc += opcodes[temp]->length;
        }
    }

    fclose(fp);
}

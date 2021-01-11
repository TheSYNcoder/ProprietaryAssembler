#include <second_pass_parse.h>

void print_line(line line)
{
    for (int i = 0; i < line.len; i++)
    {
        printf("%d %d\t", line.tokens[i].type, line.tokens[i].value);
    }
    printf("\n");
}

int begins_with(const char *s, const char c)
{
    if (s[0] == c)
        return 1;
    return 0;
}

char *strip_newline(char *s)
{
    if (s[strlen(s) - 1] == '\n')
        s[strlen(s) - 1] = '\0';
    return s;
}

int hex_to_dec(char *hex)
{
    // printf("%s\n", hex);
    int len = strlen(hex);
    int base = 1;

    int dec = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            dec += (hex[i] - 48) * base;
            base *= 16;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            dec += (hex[i] - 55) * base;
            base *= 16;
        }
        // printf("%d\n", dec);
    }

    return dec;
}

char *substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char *)malloc(sizeof(char) * (len + 1));
    strncpy(dest, (src + m), len);
    dest[len] = 0;
    // printf("%s\n", dest);
    return dest;
}

second_pass_token make_token(char *str)
{
    second_pass_token t;
    t.type = 0;
    t.value = 0;

    if (begins_with(str, 'O'))
    {
        t.type = O;
        // printf("%s\n", str);
        char *rem = substr(str, 1, strlen(str));
        if (strlen(rem) != 4)
        {
            printf("%s %d\n", rem, __LINE__);
            fprintf(stderr, "Invalid format of data.\n");
            exit(EXIT_FAILURE);
        }
        t.value = hex_to_dec(rem);
    }
    else if (begins_with(str, 'R'))
    {
        t.type = R;
        char *rem = substr(str, 1, strlen(str));
        if (strlen(rem) != 4)
        {
            printf("%d\n", __LINE__);
            fprintf(stderr, "Invalid format of data.\n");
            exit(EXIT_FAILURE);
        }
        t.value = hex_to_dec(rem);
    }
    else if (begins_with(str, 'S'))
    {
        t.type = S;
        char *rem = substr(str, 1, strlen(str));
        if (strlen(rem) != 4)
        {
            printf("%d\n", __LINE__);
            fprintf(stderr, "Invalid format of data.\n");
            exit(EXIT_FAILURE);
        }
        int val = hex_to_dec(rem); // ? query about value following S, is it a decimal or hex value
        if (val < 0 || val > 99)
        {
            printf("%d\n", __LINE__);
            fprintf(stderr, "Symbol value range [00 - 99]\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            t.value = val;
        }
    }
    else if (begins_with(str, 'L'))
    {
        t.type = L;
        char *rem = substr(str, 1, strlen(str));
        if (strlen(rem) != 4)
        {
            printf("%d\n", __LINE__);
            fprintf(stderr, "Invalid format of data.\n");
            exit(EXIT_FAILURE);
        }
        int val = hex_to_dec(rem);
        if (val < 0 || val > 65535)
        {
            printf("%d\n", __LINE__);
            fprintf(stderr, "Direct addressing value range [0000 - FFFF]\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            t.value = val;
        }
    }
    else
    {
        char *start = substr(str, 0, 2);
        if (strcmp(start, "DB") == 0)
        {
            t.type = DB;
            char *rem = substr(str, 2, strlen(str));
            if (strlen(rem) != 4)
            {
                printf("%d\n", __LINE__);
                fprintf(stderr, "Invalid format of data.\n");
                exit(EXIT_FAILURE);
            }
            t.value = hex_to_dec(rem);
        }
        else if (strcmp(start, "DW") == 0)
        {
            t.type = DW;
            char *rem = substr(str, 2, strlen(str));
            if (strlen(rem) != 4)
            {
                printf("%d\n", __LINE__);
                fprintf(stderr, "Invalid format of data.\n");
                exit(EXIT_FAILURE);
            }
            t.value = hex_to_dec(rem);
        }
        else if (strcmp(start, "DD") == 0)
        {
            t.type = DD;
            char *rem = substr(str, 2, strlen(str));
            if (strlen(rem) != 4)
            {
                printf("%d\n", __LINE__);
                fprintf(stderr, "Invalid format of data.\n");
                exit(EXIT_FAILURE);
            }
            t.value = hex_to_dec(rem);
        }
        else
        {
            printf("%d\n", __LINE__);
            fprintf(stderr, "Invalid token\n");
            exit(EXIT_FAILURE);
        }
    }
    return t;
}

line parse_intermediate_file(const char *filename)
{
    FILE *fp;

    char *rest = NULL;
    char *token = NULL;

    second_pass_token *tokens = NULL;
    int num_tokens = 0;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error while opening file.\n");
        exit(EXIT_FAILURE);
    }

    size_t buf_size = 80;
    char *buffer = malloc(buf_size * sizeof(char));

    num_tokens = 0;

    tokens = malloc(num_tokens * sizeof(second_pass_token));

    while (getline(&buffer, &buf_size, fp) != -1)
    {
        rest = buffer;

        while (token = strtok_r(rest, " ", &rest))
        {
            void *temp = NULL;
            if (temp = realloc(tokens, (++num_tokens * sizeof(second_pass_token))))
            {
                tokens = temp;
            }
            else
            {
                fprintf(stderr, "realloc error.\n");
                exit(EXIT_FAILURE);
            }

            char *str = malloc(strlen(token) * sizeof(char));
            str = strip_newline(token);
            // printf("%s\n", str);
            second_pass_token t = make_token(str);

            tokens[num_tokens - 1] = t;
        }

        free(token);
    }

    line line;
    line.len = num_tokens;
    line.tokens = malloc(line.len * sizeof(second_pass_token));
    for (int i = 0; i < line.len; i++)
    {
        line.tokens[i] = tokens[i];
    }

    free(tokens);

    return line;
}

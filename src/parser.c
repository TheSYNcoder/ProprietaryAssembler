
#include <parser.h>

/*check if the filename and the file extension is correct*/
void checkValidFileName(char *fileName)
{
    /*the extension is of length 5(.pasm)..the filename needs to be atleast 6*/
    if (strlen(fileName) < 6)
    {
        fprintf(stderr, "ERROR: file %s is too short\n", fileName);
        exit(2);
    }
    else
    {
        char *fileExtention = &fileName[strlen(fileName) - 5];
        if (strcmp(fileExtention, ASSEMBLY_FILE_EXTENSION) != 0)
        {
            fprintf(stderr, "ERROR: file %s has not the right extension (%s)\n", fileName, fileExtention);
            exit(2);
        }
    }

    /**check the file has read permission*/
    FILE *fd;
    if (!(fd = fopen(fileName, "r")))
    {
        fprintf(stderr, "ERROR: There is no such file %s or you don't have read permission on it\n", fileName);
        exit(2);
    }
    else
    {
        fclose(fd);
    }
}

int validate(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == ':') || (ch == ';') || (ch == '\n') || (ch == ' ') || (ch == '$') || (ch == '\'') || (ch == ',') || (ch == '"') || (ch >= 'A' && ch <= 'Z') || (ch == '\t'))
    {
        return 1; // validated character
    }
    else
    {
        return 0;
    }
}
void add_and_reset_lines(Token *temp, Line *line)
{
    line->tokens[line->length] = *temp;
    line->length++;

    //printLine(line);

    /*call here suvyan and aritra*/
    //if(line->length > 0 && line->tokens[0].length > 0) validate_and_find(line);

    if (line->length > 0 && line->tokens[0].length > 0)
        validate_and_find(line);

    temp->length = 0;
    for (int k = 0; k < 10; k++)
        temp->word[k] = '\0';

    for (int k = 0; k < line->length; k++)
    {
        line->tokens[k] = *temp;
    }
    line->length = 0;
}

void parse(char *fileName)
{
    checkValidFileName(fileName);
    FILE *fp;
    fp = fopen(INTERMEDIATE_FILE, "w");
    if (!fp)
    {
        perror("open");
        exit(0);
    }
    fclose(fp);

    FILE *fptr = fopen(fileName, "r");
    char buffer;

    // token will have 10 char and each line will have 3 tokens
    int counter = 0;

    Token temp;
    temp.length = 0;
    for (int k = 0; k < 10; k++)
        temp.word[k] = '\0';
    // initially 10 bytes of data allocated to temp.word

    Line currentLine;
    currentLine.length = 0;
    //currentLine.tokens = (Token*)malloc(3*sizeof(temp));

    while (fread(&buffer, sizeof(char), 1, fptr) > 0)
    {
        /* buffer contains the actual generic char*/
        char ch = buffer;

        if (validate(ch))
        {
            /*if the ch is not '\n' or space....add it to the Token*/
            // printf("%c\n",ch);
            if (ch != '\n' && ch != ' ' && ch != ';' && ch != '\t')
            {
                temp.word[temp.length] = ch;
                temp.length++;
            }
            else
            {
                if (ch == ' ' || ch == ',' || ch == '\t')
                {
                    /*ignore all the white space untill you get a char*/
                    while (fread(&ch, sizeof(char), 1, fptr))
                    {
                        if (ch != '\n' && ch != ' ' && ch != ';' && ch != '\t')
                        {
                            fseek(fptr, -sizeof(char), SEEK_CUR);
                            /*add the token to line and set Token temp to initial value*/
                            currentLine.tokens[currentLine.length] = temp;
                            currentLine.length++;

                            /*set temp to original value*/
                            temp.length = 0;
                            for (int k = 0; k < 10; k++)
                                temp.word[k] = '\0';
                            break;
                        }
                        /* but if you get a newline or comment*/
                        /*add your current Token to Line and call fucking Shuvyan*/
                        else if (ch == '\n')
                        {
                            /*add the token to line*/
                            add_and_reset_lines(&temp, &currentLine);
                            break;
                        }
                        else if (ch == ';')
                        {
                            /*ignore untill you get a newline*/
                            while (fread(&ch, sizeof(char), 1, fptr))
                            {
                                if (ch == '\n')
                                {
                                    fseek(fptr, -sizeof(char), SEEK_CUR);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                else if (ch == '\n')
                {
                    add_and_reset_lines(&temp, &currentLine);
                }
                else if (ch == ';')
                {
                    /*ignore untill you get a newline*/
                    while (fread(&ch, sizeof(char), 1, fptr))
                    {
                        if (ch == '\n')
                        {
                            fseek(fptr, -sizeof(char), SEEK_CUR);
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            /*invalid character*/
            fprintf(stderr, "The character %c is not accepted!", ch);
            exit(3);
        }
    }
    fclose(fptr);
}

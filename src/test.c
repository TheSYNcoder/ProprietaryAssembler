#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Necessary structs defined here
*/
#define ASSEMBLY_FILE_EXTENSION ".pasm"

// typedef struct op_tab_node{

//     int32_t sl_no; /* serial number of opcode */
//     char symbol[10]; /* The mnemonic such as ADD, SUB */
//     char opcode[5]; /* The opcode referring to the mnemonic */
//     int32_t length; /* The length of the instruction */
//     char add_mode[20]; /* the addressing mode - relative, absolute etc */

// }op_tab_node;


typedef struct Token
{
    int length; // how many character in the word
    char word[10]; // actual opcode or operand
}Token;

typedef struct Line
{
    int length; // how many Token exists in a line
    Token tokens[3];
}Line;


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


void checkValidFileName(char* fileName)
{   
    /*the extension is of length 5(.pasm)..the filename needs to be atleast 6*/
    if(strlen(fileName) < 6)
    {
        fprintf(stderr, "ERROR: file %s is too short\n", fileName);
        exit(2);
    }
    else
    {
        char* fileExtention = &fileName[strlen(fileName)-5];
        if(strcmp(fileExtention, ASSEMBLY_FILE_EXTENSION) != 0)
        {
            fprintf(stderr, "ERROR: file %s has not the right extension (%s)\n", fileName, fileExtention);
            exit(2);
        }
    }

    /**check the file has read permission*/
    FILE* fd;
    if(!(fd = fopen(fileName, "r")))
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
    if((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == ':') || (ch == ';') 
                || (ch == '\n') || (ch == ' ') || (ch == '$') || (ch == '\'') || (ch ==',')
                || (ch >= 'A' && ch <= 'Z' || ch == '\t')
                )
    {
        return 1; // validated character
    }
    else
    {
        return 0;
    }
    
}
void printToken(Token* token)
{
    printf("Token is: ");
    for(int i=0;i<token->length; i++)
    {
        printf("%c", token->word[i]);
    }
    printf("\n");
}

void printLine(Line* line)
{
    Token token ;
    //printf("Boom2\n");
    printf("currentLine length: %d\n", line->length);
    for(int i=0; i<line->length; i++)
    {
        printToken(& line->tokens[i]);
        //token = (line->tokens[i]);
        // printf("Printing Token.................: \n");
        // //printToken(&token);
        // //printf("Boom3\n");
        // for(int j=0; j < token.length; j++)
        // {
        //     printf("%c", token.word[j]);
        //     //printf("Boom4\n");
        // }
        // printf("\n");
    }
    //printf("Boom5\n");
}

void add_and_reset_lines(Token* temp, Line* line)
{
    line->tokens[line->length] = *temp;
    line->length++;

    printLine(line);

    /*call here suvyan and aritra*/
    //op_tab_node* op_tab = call_fucking_shuvyan(line);
    //hello_aritra_samanta(op_tab);

    temp->length = 0;
    for(int k=0;k<10;k++) temp->word[k] = '\0';
    // free(temp.word);
    // temp.word = (char*)malloc(10*sizeof(char));

    for (int k=0;k<line->length;k++)
    {
        line->tokens[k] = *temp;
    }
    line->length = 0;
}


void parse(char* fileName)
{
    //checkValidFileName(fileName);
    checkValidFileName(fileName);
    FILE* fptr = fopen(fileName, "r");
    char buffer;

    // token will have 10 char and each line will have 3 tokens
    int counter = 0;

    Token temp;
    temp.length = 0;
    for(int k=0;k<10;k++) temp.word[k] = '\0';
    // initially 10 bytes of data allocated to temp.word

    Line currentLine;
    currentLine.length = 0;
    
    while(fread(&buffer, sizeof(char), 1, fptr) > 0)
    {
        /* buffer contains the actual generic char*/
        char ch = buffer;
        
        if(validate(ch))
        {
            /*if the ch is not '\n' or space....add it to the Token*/
            counter++;
            if(ch != '\n' && ch != ' ' && ch != ';')
            {
                if(temp.length >= 10)
                {
                    fprintf(stderr, "PARSER ERROR: Plz give names less than 10 chars!\n");
                    exit(2);
                }
                temp.word[temp.length] = ch;
                temp.length++;
            }
            else
            {
                if(ch == ' ' || ch == ',' || ch == '\t')
                {
                    /*ignore all the white space untill you get a char*/
                    while(fread(&buffer,sizeof(char),1,fptr))
                    {
                        if(buffer != '\n' && buffer != ' ' && buffer != ';' && buffer != '\t')
                        
                        {
                            fseek(fptr, -sizeof(char), SEEK_CUR);
                            /*add the token to line and set Token temp to initial value*/
                            currentLine.tokens[currentLine.length] = temp;
                            currentLine.length++;

                            /*set temp to original value*/
                            temp.length = 0;
                            for(int k=0;k<10;k++) temp.word[k] = '\0';
                            break;
                        }
                        /* but if you get a newline or comment*/
                        /*add your current Token to Line and call fucking Shuvyan*/
                        else if(buffer == '\n' || buffer == ';')
                        {  
                            while(fread(&buffer, sizeof(char), 1, fptr))
                            {
                                /*ignore all the white newlines*/
                                if(buffer == '\n') continue;
                                else if(buffer == ';')
                                {
                                    /*ignore all the character untill a newline encountered*/
                                    char ch;
                                    while(fread(&ch, sizeof(char), 1, fptr))
                                    {
                                        if(ch == '\n') break; 
                                        else continue;
                                    }
                                }
                                else
                                {
                                    fseek(fptr, -sizeof(char), SEEK_CUR);
                                    break;
                                }    
                            }
                            add_and_reset_lines(&temp, &currentLine);
                            break;
                            
                        }
                        else
                        {
                            continue;
                        }  
                    }
                }
                else if(buffer == '\n' || buffer == ';')
                {
                        add_and_reset_lines(&temp, &currentLine);
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

void printFile(char* filename)
{
    char buffer;
    FILE* fptr = fopen(filename, "r");
    while(fread(&buffer, sizeof(char), 1, fptr))
    {
        printf("%d\n",buffer);
    }
    fclose(fptr);
}

int main()
{
    //printf("Boom!");
    char* file = "test.pasm";
    parse(file);
    //printf("%d\n", name);
    return 0;
}
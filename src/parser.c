
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "main.h"
#include "parser.h"

/*check if the filename and the file extension is correct*/
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
                || (ch >= 'A' && ch <= 'Z') || (ch == '\t')
                )
    {
        return 1; // validated character
    }
    else
    {
        return 0;
    }
   

void parse(char* fileName)
{
    checkValidFileName(fileName);

    FILE* fptr = fopen(fileName, "r");
    char buffer;

    // token will have 10 char and each line will have 3 tokens
    int counter = 0;

    Token temp;
    temp.length = 0;
    for(int k=0;k<10;k++) temp.word[k] = '\0';
    //temp.word = (char*)malloc(10*sizeof(char));
    // initially 10 bytes of data allocated to temp.word

    Line currentLine;
    currentLine.length = 0;
    //currentLine.tokens = (Token*)malloc(3*sizeof(temp));
    
    while(fread(&buffer, sizeof(char), 1, fptr) > 0)
    {
        /* buffer contains the actual generic char*/
        char ch = buffer;
        
        if(validate(ch))
        {
            /*if the ch is not '\n' or space....add it to the Token*/
            // printf("%c\n",ch);
            if(ch != '\n' && ch != ' ' && ch != ';' && ch != '\t')
            {
                if(temp.length >= 10)
                {
                    //temp.word = (char*)realloc(temp.word, (temp.length+1)*sizeof(char));
                    /*error not handled here*/
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
                        if(buffer != '\n' && buffer != ' ' && buffer != ';')
                        {
                            fseek(fptr, -sizeof(char), SEEK_CUR);
                            /*add the token to line and set Token temp to initial value*/
                            //if(currentLine.length >= 3) currentLine.tokens = (Token*)realloc(currentLine.tokens, sizeof(currentLine)+sizeof(temp));
                            currentLine.tokens[currentLine.length] = temp;
                            /**upto this working*/
                            currentLine.length++;

                            printf("Boom1space\n");
                            printLine(&currentLine);
                            printf("Boom2space\n");

                            /*set temp to original value*/
                            temp.length = 0;
                            for(int k=0;k<10;k++) temp.word[k] = '\0';
                            break;
                        }
                        /* but if you get a newline or comment*/
                        /*add your current Token to Line and call fucking Shuvyan*/
                        else if(buffer == '\n' || buffer == ';')
                        {  
                            /*add the token to line*/ 
                            if(currentLine.length == 3)
                            {
                                fprintf(stderr,"Parser error! Too much argumnet in a line!!");
                                exit(2);
                            }
                            currentLine.tokens[currentLine.length] = temp;
                           
                           
                            currentLine.length++;
                            
                            /*sending ref of Line...receiving ref of op_tab_node*/
                            // op_tab_node* op_tab = call_fucking_shuvyan(&currentLine);
                            // hello_aritra(op_tab); 


                            /*set temp and currentLine to to original value*/
                            temp.length = 0;
                            for(int k=0;k<10;k++) temp.word[k] = '\0';


                            for (int k=0;k<currentLine.length;k++)
                            {
                                currentLine.tokens[k] = temp;
                            }
                            currentLine.length = 0;
                            
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
                        /*add the token to line*/ 
                        //printf("BOOM BABY!\n");
                        //if(currentLine.length >= 3) currentLine.tokens = (Token*)realloc(currentLine.tokens, sizeof(currentLine)+sizeof(temp));
                        currentLine.tokens[currentLine.length] = temp;
                        currentLine.length++;

                        /*sending ref of Line...receiving ref of op_tab_node*/
                        // op_tab_node* op_tab = call_fucking_shuvyan(&currentLine);
                        // hello_aritra(op_tab);


                        /*set temp and currentLine to to original value*/
                        temp.length = 0;
                        for(int k=0;k<10;k++) temp.word[k] = '\0';
                        // free(temp.word);
                        // temp.word = (char*)malloc(10*sizeof(char));

                        for (int k=0;k<currentLine.length;k++)
                        {
                            currentLine.tokens[k] = temp;
                        }
                        currentLine.length = 0;
                        // free(currentLine.tokens);
                        // currentLine.tokens =  (Token*)malloc(3*sizeof(Token));
                        break;
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

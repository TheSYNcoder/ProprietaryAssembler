
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "main.h"
#include "parser.h"

/*check if the filename and the file extension is correct*/
void checkValidFileName(char* fileName)
{   
    /*the extension is of length 3..the filename needs to be atleast 4*/
    if(strlen(fileName) < 4)
    {
        fprintf(stderr, "ERROR: file %s is too short\n", fileName);
        exit(2);
    }
    else
    {
        char* fileExtention = &fileName[strlen(fileName)-3];
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


Token* parser(char* fileName)
{
    checkValidFileName(fileName);
}
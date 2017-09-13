#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include "dun_utils.h"

int main (int argc, char * argv[])
{
    int flag_save = 0;
    int flag_load = 0;
    int arguement_index = 1;
    char *home  = getenv("HOME");
    FILE *f;

    if(argc < 1)
    {
        printf("Incorrect amount of arguements\n");
        return 1;
    }

    while  (arguement_index < argc)
    {
        printf("%s\n", argv [arguement_index]);

        if(!strcmp(argv[arguement_index], "--load"))
        {
            flag_load = 1;
        }
        else if(!strcmp(argv[arguement_index], "--save"))
        {
            flag_save = 1;
        }
        else
        {
            printf("Incorrect parameter detected: %s\n", argv[arguement_index]);
            return 1;
        }
        
        arguement_index++;
    }
    
    if(flag_load && flag_save)
    {
        //TODO
        printf("Program will load & save\n");
    }
    else if(flag_load)
    {
        //TODO
        printf("Program will only load\n");
        int length = strlen(home) + strlen("/.rlg327/dungeon") + 1;
        char * path;
        char * buffer;
        int f_size;
        size_t result;

        path = malloc(length);
        strcpy (path, home);
        strcat(path, "/.rlg327/dungeon");
        f = fopen(path, "rb");

        if (f == NULL)
        {
            fputs("File Error", stderr);
            exit(1) ;
        }

        //Get file size
        fseek(f, 0, SEEK_END);
        f_size = ftell(f);
        rewind(f);

        //allocate memory to contain whole file
        buffer = (char*) malloc (sizeof(char)*f_size);
        if(buffer == NULL)
        {
            fputs("Memory error", stderr);
            exit (2);
        }

        //copy file to buffer
        result = fread(buffer, 1, f_size, f);
        if(result != f_size)
        {
            fputs ("Reading error", stderr);
            exit (3);
        }
        
        
        printf("size of file: %d & calc size: %d\n", f_size, num);
        free(path);
        free(buffer);
        fclose(f);
    }
    else if(flag_save)
    {
        //TODO
        printf("Program will only save\n");
        int length = strlen(home) + strlen("/.rlg327/dungeon") + 1;
        char * path;
        path = malloc(length);
        strcpy (path, home);
        strcpy(path, "/.rlg327/dungeon");
        f = fopen(path, "rw");
        free(path);
        fclose(f);
        
    }
    else 
    {
        //Execute the default behavior
        //Gen a dungeon, display & exit
        gen_dun();
        return 0;
    }

    return 0;
}
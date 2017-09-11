#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dun_utils.h"

int main (int argc, char * argv[])
{
    int flag_save = 0;
    int flag_load = 0;
    int arguement_index = 1;
    char *filePath;

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
        filePath = getenv("HOME");
        strcat(filePath, ".rlg327/dungeon");
        printf("filepath: %s\n", filePath);
        printf("Program will only load\n");
    }
    else if(flag_save)
    {
        //TODO

        filePath = getenv("HOME");
        strcat(filePath, ".rlg327/dungeon");
        printf("filepath: %s\n", filePath);
        printf("Program will only save\n");
    }
    else 
    {
        //Execute the default behavior
        //Gen a dungeon, display & exit
        gen_dun();

    }

    return 0;
}
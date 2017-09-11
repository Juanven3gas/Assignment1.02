#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[])
{
    int flag_save = 0;
    int flag_load = 0;
    int arguement_index = 1;

    if(argc <= 1)
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
        printf("Program will only load\n");
    }
    else if(flag_save)
    {
        //TODO
        printf("Program will only save\n");
    }
    else 
    {
        //TODO
        printf("Incorrect parameters. Program exitting\n");
        return 1;   
    }

    return 0;
}
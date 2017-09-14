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
        int length = strlen(home) + strlen("/.rlg327/dungeon") + 1;
        char * path;
        unsigned char * buffer;
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
        buffer = (unsigned char*) malloc (sizeof(unsigned char)*f_size);
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
        
        free(path);
        
        printf("size of file: %d\n", f_size);
        printf("byte[10]: %u, byte[11]: %u, byte[12]: %u, byte[13]: %u\n", (unsigned int)buffer[10], (unsigned int)buffer[11], (unsigned int)buffer[12], (unsigned int)buffer[13]);
        unsigned int b4 = (buffer[10] << 24) + (buffer[11] << 12) + (buffer[12] << 8) + (buffer[13]);
        printf("num : %u\n", b4);
        
        //figure out how to do hardness in order to find corridors

        //figure out the rooms
        int start;
        int i, j;        
        char dungeon[21][80];
        

        for(i = 0; i < 21; i++)
        {
            for(j = 0; j < 80; j++)
            {
                dungeon[i][j] = ' ';
            }
        }

        for(start = 1694; start < f_size; start++)
        {

            unsigned int roomy = (unsigned int)buffer[start];
            unsigned int roomx = (unsigned int)buffer[++start];
            unsigned int roomRow = (unsigned int)buffer[++start];
            unsigned int roomCol = (unsigned int)buffer[++start];

            printf("room y position: %2u,room x position: %2u, room rows: %2u, room cols: %2u\n", roomy, roomx, roomRow, roomCol);
            
            int row, col;
            for(row = roomy; row < (roomy + roomCol); row++)
            {
                for(col = roomx; col < (roomx + roomRow); col++)
                {
                    dungeon[row][col] = '.';
                }
            }
        }


        for(i = 0; i < 21; i++)
        {
            for(j = 0; j < 80; j++)
            {
                printf("%c", dungeon[i][j]);
            }

            printf("\n");
        }

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
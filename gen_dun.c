#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dun_utils.h"

#define dungeon_rows 21
#define dungeon_columns 80
#define num_rooms 6

char dungeon[dungeon_rows][dungeon_columns];
int rooms[num_rooms][4];

int check_rooms(int rows, int columns, int start_row, int start_column);
void sort_rooms(void);
void add_rooms(void);
void add_corridors(void);
void init_dungeon(void);
void print_dungeon(void);

int gen_dun(void)
{
    init_dungeon();
    add_rooms();
    add_corridors();
    print_dungeon();

    return 0;
}

void sort_rooms(void)
{
    int i, j;

    for(i = 0; i < num_rooms - 1; i++)
    {
        int min_indx = i;

        for(j = i+1; j < num_rooms; j++)
        {
            int room1_start_y = rooms[min_indx][3];
            int room2_start_y = rooms[j][3];

            if(room2_start_y < room1_start_y)
            {
                min_indx = j;
            }

        }

        int temp_rows = rooms[min_indx][0];
        int temp_cols = rooms[min_indx][1];
        int temp_start_row = rooms[min_indx][2];
        int temp_start_cols = rooms[min_indx][3];

        rooms[min_indx][0] = rooms[i][0];
        rooms[min_indx][1] = rooms[i][1];
        rooms[min_indx][2] = rooms[i][2];
        rooms[min_indx][3] = rooms[i][3];

        rooms[i][0] = temp_rows;
        rooms[i][1] = temp_cols;
        rooms[i][2] = temp_start_row;
        rooms[i][3] = temp_start_cols;
    }
}

void add_corridors(void)
{
    int i, j, room;

    for(room = 0; room < num_rooms-1; room++)
    {
        int room1_rows = rooms[room][0];
        int room1_columns = rooms[room][1];
        int room1_start_row = rooms[room][2];
        int room1_start_column = rooms[room][3];

        int room2_rows = rooms[room+1][0];
        int room2_columns = rooms[room+1][1];
        int room2_start_row = rooms[room+1][2];
        int room2_start_column = rooms[room+1][3];

        int room1_mid_x = (room1_rows/2) + room1_start_row;
        int room1_mid_y = (room1_columns/2) + room1_start_column;

        //printf("room 1 mid x: %d, room 1 mid y: %d\n", room1_mid_x, room1_mid_y);

        int room2_mid_x = (room2_rows/2) + room2_start_row;
        int room2_mid_y = (room2_columns/2) + room2_start_column;

        //printf("room 2 mid x: %d, room 2 mid y: %d\n", room2_mid_x, room2_mid_y);

        if((room2_mid_x - room1_mid_x) < 0)
        {
            for(i =  room1_mid_x; i > room2_mid_x - 1; i --)
            {
	      if(dungeon[i][room1_start_column + room1_columns] != '.')
		{
		  dungeon[i][room1_start_column + room1_columns] = '#';
		}
                
            }
        }
        else
        {
            for(i = room1_mid_x; i < room2_mid_x + 1; i++)
            {
	      if(dungeon[i][room1_start_column + room1_columns] != '.')
		{
		   dungeon[i][room1_start_column + room1_columns] = '#';
		}
               
            }
        }

        if((room2_mid_y - room1_mid_y) < 0)
        {
            for(j = (room1_start_column + room1_columns); j > (room2_start_column) ; j--)
            {
	      if(dungeon[room2_mid_x][j] != '.')
		{
		   dungeon[room2_mid_x][j] = '#';
		}
               
            }
        }
        else
        {
            for(j = (room1_start_column + room1_columns); j < room2_start_column; j++)
            {
	      if(dungeon[room2_mid_x][j]  != '.')
		{
		  dungeon[room2_mid_x][j] = '#';
		}
                
            }
        }

    }

}

void add_rooms(void)
{
    int room_counter;
    int start_row, start_column;
    int rows, columns;
    int i, j;

    room_counter = 0;

    srand(time(NULL));

    while(room_counter < num_rooms)
    {
        int success = 1;

        //random row from 3 - 9
        rows = (rand() % 7) + 3;


        //random col from 3 - 9
        columns = (rand() % 7) + 3;

        //random row from 1 - 12
        start_row = (rand() % 11) + 1;

        //random col from 1 - 71
        start_column = (rand() % 70) + 1;

        success = check_rooms(rows, columns, start_row, start_column);

        /*
         * Add room to the dungeon & then increment the room counter
         */
        if(success)
        {
            for(i = start_row; i < (start_row + rows); i++)
            {
                for(j = start_column; j < (start_column + columns); j++)
                {
                    dungeon[i][j] = '.';
                }
            }

            rooms[room_counter][0] = rows;
            rooms[room_counter][1] = columns;
            rooms[room_counter][2] = start_row;
            rooms[room_counter][3] = start_column;

            room_counter++;
        }

    }

    sort_rooms();
    
}

int check_rooms(int rows, int columns, int start_row, int start_column)
{
    int i = 0;
    int j = 0;

    //checks to see if there is nothing above room
    for(i = (start_row - 3); i < start_row; i++)
    {
        for(j = start_column; j < (start_column + columns); j++)
        {
            if(dungeon[i][j] == '.')
            {
                return 0;
            }
        }
    }


    //checks to see if there is nothing below room

    for(i = (start_row + rows); i < (start_row + rows + 3); i++)
    {
        for(j = start_column; j < (start_column + columns); j ++)
        {
            if(dungeon[i][j] == '.')
            {
                return 0;
            }
        }
    }


    //checks to see if there is nothing to the right
    for(i = start_row; i < (start_row + rows); i++)
    {
        for(j = (start_column + columns); j < (start_column + columns + 3); j++)
        {
            if(dungeon[i][j] == '.')
            {
                return 0;
            }
        }
    }

    //checks to see if there is nothing to the left
    for(i = start_row; i < (start_row + rows); i++)
    {
        for(j = (start_column - columns); j < start_column; j++)
        {
            if(dungeon[i][j] == '.')
            {
                return 0;
            }
        }
    }


    return 1;
}

void init_dungeon(void)
{
    int i, j;

    for(i = 0; i < dungeon_rows; i++)
    {
        for(j = 0; j < dungeon_columns; j++)
        {
            dungeon[i][j] = ' ';
            dungeon[0][j] = '-';
            dungeon[dungeon_rows - 1][j] = '-';
        }

        dungeon[i][0] = '|';
        dungeon[i][dungeon_columns - 1] = '|';
    }
}

void print_dungeon(void)
{
    int i, j;

    for(i = 0; i < dungeon_rows; i++)
    {
        for(j = 0; j < dungeon_columns; j++)
        {
            printf("%c", dungeon[i][j]);
        }

        printf("\n");
    }

}

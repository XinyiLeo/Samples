#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "simulation.h"
#include "world_type.h"


void printState(grid_t &grid)
{  
    int i,j;
    string tempOne, tempTwo , tempThree;
    string print[grid.height][grid.width];
    for(j = 0; j < (int) grid.height; j++)
    {
        for(i = 0; i < (int) grid.width; i++)
        {
            if(grid.squares[j][i] == NULL)
            {
                print[j][i]= "____ ";
            }    
            else
            {
                tempOne = grid.squares[j][i]->species->name[0];
                tempThree = grid.squares[j][i]->species->name[1]; 
                tempTwo = directShortName[grid.squares[j][i]->direction];
                print[j][i]= tempOne + tempThree + "_" + tempTwo + " ";
            }
        }
    } 
    for(j = 0; j < (int)grid.height; j++)
    {
        for(i = 0; i < (int)grid.width; i++)
        {
            cout << print[j][i] ;      
        }
        cout << "" <<endl;
    } 
}


grid_t hop(creature_t &creature, grid_t &grid)
{
    point_t tempLocation = creature.location;
    switch (creature.direction)
        {
        case EAST:
            tempLocation.c++;
            break;
        case SOUTH:
            tempLocation.r++;
            break;
        case WEST:
            tempLocation.c--;
            break;
        case NORTH:
            tempLocation.r--;
            break;
        }
    if(tempLocation.r < (int)grid.height && tempLocation.r >= 0 &&
             tempLocation.c < (int)grid.width && tempLocation.c >= 0)
    {
         if(grid.squares[tempLocation.r][tempLocation.c] == NULL)
         {   
             grid.squares[creature.location.r][creature.location.c] = NULL; 
             creature.location.r = tempLocation.r ;
             creature.location.c = tempLocation.c ;
         }
    }
    creature.programID++;
    grid.squares[creature.location.r][creature.location.c] = &creature; 
    return grid;
}

grid_t left(creature_t &creature, grid_t &grid)
{
     switch (creature.direction)
        {
        case EAST:
            creature.direction = NORTH;
            break;
        case SOUTH:
            creature.direction = EAST;
            break;
        case WEST:
            creature.direction = SOUTH;
            break;
        case NORTH:
            creature.direction = WEST;
            break;
        }
     creature.programID++;
     return grid;
}

grid_t right(creature_t &creature, grid_t &grid)
{
     switch (creature.direction)
        {
        case EAST:
            creature.direction = SOUTH;
            break;
        case SOUTH:
            creature.direction = WEST;
            break;
        case WEST:
            creature.direction = NORTH;
            break;
        case NORTH:
            creature.direction = EAST;
            break;
        }
     creature.programID++;
     return grid;
}

grid_t infect(creature_t &creature, grid_t &grid)
{
    point_t tempLocation = creature.location;
    switch (creature.direction)
        {
        case EAST:
            tempLocation.c++;
            break;
        case SOUTH:
            tempLocation.r++;
            break;
        case WEST:
            tempLocation.c--;
            break;
        case NORTH:
            tempLocation.r--;
            break;
        }
    if(tempLocation.r < (int)grid.height && tempLocation.r >= 0 && tempLocation.c < (int)grid.width && tempLocation.c >= 0)
    { 
        if(grid.squares[tempLocation.r][tempLocation.c] != NULL)
        {  
            if(grid.squares[tempLocation.r][tempLocation.c]->species != grid.squares[creature.location.r][creature.location.c]->species) 
            {
                grid.squares[tempLocation.r][tempLocation.c]->species = grid.squares[creature.location.r][creature.location.c]->species ; 
                grid.squares[tempLocation.r][tempLocation.c]->programID = 1;
            }
        } 
    }
    creature.programID++;
    return grid;
}

creature_t ifempty(creature_t &creature, grid_t &grid, int step)
{
    point_t tempLocation = creature.location;
    switch (creature.direction)
        {
        case EAST:
            tempLocation.c++;
            break;
        case SOUTH:
            tempLocation.r++;
            break;
        case WEST:
            tempLocation.c--;
            break;
        case NORTH:
            tempLocation.r--;
            break;
        }
    if(tempLocation.r < (int)grid.height && tempLocation.r >= 0 && tempLocation.c < (int)grid.width && tempLocation.c >= 0)
    { 
        if(grid.squares[tempLocation.r][tempLocation.c] == NULL)
        {   
            creature.programID = step - 1 ;    
        }
    }
    creature.programID++;
    return creature;
}

creature_t ifwall(creature_t &creature, grid_t &grid, int step)
{
    point_t tempLocation = creature.location;
    switch (creature.direction)
        {
        case EAST:
            tempLocation.c++;
            break;
        case SOUTH:
            tempLocation.r++;
            break;
        case WEST:
            tempLocation.c--;
            break;
        case NORTH:
            tempLocation.r--;
            break;
        }
    if(tempLocation.r >= (int)grid.height || tempLocation.r < 0 || tempLocation.c >= (int)grid.width || tempLocation.c < 0)
    {   
         creature.programID = step;    
    }
    else
    {
         creature.programID++;
    }
    return creature;
}

creature_t ifsame(creature_t &creature, grid_t &grid, int step)
{
    point_t tempLocation = creature.location;
    switch (creature.direction)
        {
        case EAST:
            tempLocation.c++;
            break;
        case SOUTH:
            tempLocation.r++;
            break;
        case WEST:
            tempLocation.c--;
            break;
        case NORTH:
            tempLocation.r--;
            break;
        }
    if(tempLocation.r < (int)grid.height && tempLocation.r >= 0 && tempLocation.c < (int)grid.width && tempLocation.c >= 0) 
    {
        if(grid.squares[tempLocation.r][tempLocation.c] != NULL)
        {    
            if(grid.squares[tempLocation.r][tempLocation.c]->species == grid.squares[creature.location.r][creature.location.c]->species)
            {
                creature.programID = step - 1;
            }    
        }
    }
    creature.programID++;
    return creature;
}

creature_t ifenemy(creature_t &creature, grid_t &grid, int step)
{
    point_t tempLocation = creature.location;
    switch (creature.direction)
        {
        case EAST:
            tempLocation.c++;
            break;
        case SOUTH:
            tempLocation.r++;
            break;
        case WEST:
            tempLocation.c--;
            break;
        case NORTH:
            tempLocation.r--;
            break;  
        }
    if(tempLocation.r < (int)grid.height && tempLocation.r >= 0 && tempLocation.c < (int)grid.width && tempLocation.c >= 0) 
    {
        if(grid.squares[tempLocation.r][tempLocation.c] != NULL)
        {    
            if(grid.squares[tempLocation.r][tempLocation.c]->species != grid.squares[creature.location.r][creature.location.c]->species)
            {
                creature.programID = step -1 ;
            }    
        }
    }
    creature.programID++;
    return creature;
}

creature_t go(creature_t &creature, int step)
{
    creature.programID = step;
    return creature;
}




#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "simulation.h"
#include "world_type.h"

using namespace std;

int main(int argc, char *argv[])
{
//Read the informations of the files
    if(argc < 4)
    {
        cout << "Error: Missing arguments!"<< endl;
        cout << "Usage: ./p4 <species-summary> <world-file> <rounds> [v|verbose]"<< endl;
        return 0;
    }
    int round= atoi(argv[3]);
    if(round < 0)
    {
        cout << "Error: Number of simulation rounds is negative!" <<endl;
        return 0;
    }
    ifstream speciesFile;
    ifstream worldFile;
    speciesFile.open(argv[1]);
    if(!speciesFile)
    {
        cout << "Error: Cannot open file " << argv[1] <<"!" << endl;
        return 0;
    }
    worldFile.open(argv[2]);
    if(!worldFile)
    {
        cout << "Error: Cannot open file " << argv[2] <<"!" << endl;
        return 0;
    }
//Read the world grid size
    struct world_t world;
     int i ,j, k;
     string creaturesRef ,line, speciesType, direction, opnametemp;
     istringstream iStream;
     getline(worldFile, line);
     iStream.str(line);
     iStream >> world.grid.height ; 
     iStream.clear();
     if(world.grid.height < 1 || world.grid.height > MAXHEIGHT)
     {
         cout << "Error: The grid height is illegal!" << endl;
         return 0;
     }
     getline(worldFile, line);
     iStream.str(line);
     iStream >> world.grid.width ; 
     iStream.clear();
     if(world.grid.width < 1 || world.grid.width > MAXWIDTH)
     {
         cout << "Error: The grid width is illegal!" << endl;
         return 0;
     }
     for(i = 0; i < (int)MAXHEIGHT; i++)
     {
         for(j = 0; j < (int)MAXWIDTH; j++)
         {
             world.grid.squares[i][j] = NULL;
         }
     }

//Read the information of species and create species
     ifstream creaturesFile;
     getline(speciesFile, creaturesRef);
     creaturesFile.open(creaturesRef.c_str());
     if(!creaturesFile)
     {
         cout << "Error: Cannot open file " << creaturesRef <<"!" << endl;
         return 0;
     }
     creaturesFile.close();
     string tempstring, speciesname; 
     i=0;
     for(i = 0; i < (int) MAXSPECIES + 1; i++)
     {
          getline(speciesFile, line);
          if(line == "")
          {
              world.numSpecies = i;
              break;
          }
          else if(i == MAXSPECIES)
          {
              cout << "Error: Too many species!" <<endl;
              cout << "Maximal number of species is " << MAXSPECIES << "." <<endl;
              return 0;
          }
          else
          {
              speciesname = line;
              tempstring = creaturesRef+"/"+speciesname;
              creaturesFile.open(tempstring.c_str());
              if(!creaturesFile)
              {
                  cout << "Error: Cannot open file " << tempstring <<"!" << endl;
                  return 0;
              }
              world.species[i].name = speciesname;
              for(j = 0; j < (int)MAXPROGRAM + 1; j++)
              {  
                      getline(creaturesFile, line);
                      if(line == "")
                      {   
                          world.species[i].programSize = j;
                          break;
                      }
                      else if(j == MAXPROGRAM)
                      {
                          cout << "Error: Too many instructions for species " << speciesname << "!" << endl;
                          cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
                          return 0;
                      }
                      else
                      {
                          iStream.str(line);
                          iStream >> opnametemp ;
                          for(k = 0; k < 9; k++)
                          {
                              if(opnametemp == opName[k])
                              {
                                  switch (k) 
                                  {
                                      case 0:
                                          world.species[i].program[j].op = HOP ;
                                          //For the purpose of siplifying the later procedures, we set the address to 0  
                                          world.species[i].program[j].address = 0;
                                          break;
                                      case 1:
                                          world.species[i].program[j].op = LEFT ;
                                          world.species[i].program[j].address = 0;
                                          break;
                                      case 2:
                                          world.species[i].program[j].op = RIGHT ;
                                          world.species[i].program[j].address = 0;
                                          break;
                                      case 3:
                                          world.species[i].program[j].op = INFECT ;
                                          world.species[i].program[j].address = 0;
                                          break;
                                      case 4:
                                          world.species[i].program[j].op = IFEMPTY ;
                                          iStream >> world.species[i].program[j].address;
                                          break;
                                      case 5:
                                          world.species[i].program[j].op = IFENEMY ;
                                          iStream >> world.species[i].program[j].address;
                                          break;
                                      case 6:
                                          world.species[i].program[j].op = IFSAME ;
                                          iStream >> world.species[i].program[j].address;
                                          break;
                                      case 7:
                                          world.species[i].program[j].op = IFWALL ;
                                          iStream >> world.species[i].program[j].address;
                                          break;
                                      case 8:
                                          world.species[i].program[j].op = GO ;
                                          iStream >> world.species[i].program[j].address;
                                          break;
                                  }
                                  break;
                              }
                              if(k == 8)
                              {
                                  cout << "Error: Instruction "<< opnametemp <<" is not recognized!" << endl;
                                  return 0;
                              }
                          }
                          iStream.clear();
                      }
              }
              creaturesFile.close();
          }
     }

    
    //Create the creatures
     //struct creature_t creatures[MAXCREATURES];
     for(j = 0; j < (int) MAXCREATURES + 1; j++)
     { 
        getline(worldFile, line);
        if(line == "")
        {
            world.numCreatures = j;
            break;
        }
        else if(j == MAXCREATURES)
        {
            cout << "Error: Too many creatures!" << endl;
            cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
            return 0;
        }
        else
        {
        iStream.str(line);
        iStream >> speciesType >> direction >> world.creatures[j].location.r >> world.creatures[j].location.c ; 
        if(world.creatures[j].location.r >= (int)world.grid.height || world.creatures[j].location.r < 0 ||
                 world.creatures[j].location.c >= (int)world.grid.width || world.creatures[j].location.c < 0)
        {
            cout << "Error: Creature (" << speciesType << " " << direction << " " << world.creatures[j].location.r << " " <<
                     world.creatures[j].location.c << ") is out of bound!" << endl;
            cout << "The grid size is " << world.grid.height << "-by-" << world.grid.width << "." << endl;
            return 0;
        }
        for(i = 0; i < 4; i++)
        {
            if(direction == directName[i])
            { 
                switch (i)
                {
                    case 0:
                        world.creatures[j].direction = EAST;
                        break;
                    case 1:
                        world.creatures[j].direction = SOUTH;
                        break;
                    case 2:
                        world.creatures[j].direction = WEST;
                        break;
                    case 3:
                        world.creatures[j].direction = NORTH;
                        break;
                }
                break;
            }
            if(i == 3)
            {
                cout << "Error: Direction " << direction << " is not recognized!" << endl; 
                exit(1);
            }
        }
        world.creatures[j].programID = 1;
        for(k = 0; k < (int) world.numSpecies; k++)
        {
            if(speciesType == world.species[k].name)
            {
                world.creatures[j].species = & world.species[k];
                break;
            }
            if(k == (int) world.numSpecies - 1)
            {
                cout << "Error: Species " << speciesType << " not found!" << endl;
                exit(1);
            }
        }
        if(world.grid.squares[world.creatures[j].location.r][world.creatures[j].location.c] != NULL)
        {
             cout << "Error: Creature ("<< world.creatures[j].species->name << " " << direction << " " << world.creatures[j].location.r << " " << world.creatures[j].location.c << ") overlaps with creature (" << world.grid.squares[world.creatures[j].location.r][world.creatures[j].location.c]->species->name << " " << directName[world.grid.squares[world.creatures[j].location.r][world.creatures[j].location.c]->direction] << " " << world.creatures[j].location.r << " " << world.creatures[j].location.c << ")!" <<endl;
             return 0;
        }
        world.grid.squares[world.creatures[j].location.r][world.creatures[j].location.c] = &world.creatures[j]; 
        iStream.clear();
        }
    }
    speciesFile.close();
    worldFile.close();
    //Finally we read all the input from the files and made a complete world_t structure
    // And we finished implementing the error checking mechanisms (also
    //it's convenient to check whether we read the input correctly)
    //So it's time to start simulating!
  
    //First, the verbose mode

            
   

    if(argc == 5)
    {
        string verbose;
        verbose = argv[4]; 
        if(verbose == "v" || verbose == "verbose")
        { 
            cout << "Initial state" << endl;
            printState(world.grid);
            for(i = 0; i < round; i++)
            {
                cout << "Round " << i+1 << endl;
                for(j = 0; j < (int) world.numCreatures; j++)
                {
                    cout << "Creature (" << world.creatures[j].species->name << " " << directName[world.creatures[j].direction]
                         << " " << world.creatures[j].location.r << " " << world.creatures[j].location.c << ") takes action:" << endl;
                    next:
                    if(world.creatures[j].species->program[world.creatures[j].programID - 1].address == 0)
                    {
                        cout << "Instruction " << world.creatures[j].programID << ": " 
                             << opName[world.creatures[j].species->program[world.creatures[j].programID - 1].op] << endl;
                    }
                    else
                    {
                        cout << "Instruction " << world.creatures[j].programID << ": " 
                             << opName[world.creatures[j].species->program[world.creatures[j].programID - 1].op] 
                             << " " << world.creatures[j].species->program[world.creatures[j].programID - 1].address << endl;
                    }
                    switch(world.creatures[j].species->program[world.creatures[j].programID - 1].op)
                    {
                        case HOP:
                            hop(world.creatures[j], world.grid);
                            break;
                        case LEFT:
                            left(world.creatures[j], world.grid);
                            break;
                        case RIGHT:
                            right(world.creatures[j], world.grid);
                            break;
                        case INFECT:
                            infect(world.creatures[j], world.grid);
                            break;
                        case IFEMPTY:
                            ifempty(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto next;
                        case IFENEMY:
                            ifenemy(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto next;
                        case IFSAME:
                            ifsame(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto next;
                        case IFWALL:
                            ifwall(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto next;
                        case GO:
                            go(world.creatures[j], 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto next;
                    }
                    printState(world.grid);
                }
            }
        }
    }

    else if(argc == 4)
    {
            string tempOutput;
            direction_t tempDirection;
            point_t tempPoint;
            cout << "Initial state" << endl;
            printState(world.grid);
            for(i = 0; i < round; i++)
            {
                cout << "Round " << i+1 << endl;
                for(j = 0; j < (int)world.numCreatures; j++)
                {
                    tempDirection = world.creatures[j].direction;
                    tempPoint = world.creatures[j].location;
                    nextTwo:
                    switch(world.creatures[j].species->program[world.creatures[j].programID - 1].op)
                    {
                        case HOP:
                            hop(world.creatures[j], world.grid);
                            tempOutput = opName[HOP];
                            break;
                        case LEFT:
                            left(world.creatures[j], world.grid);
                            tempOutput = opName[LEFT];
                            break;
                        case RIGHT:
                            right(world.creatures[j], world.grid);
                            tempOutput = opName[RIGHT];
                            break;
                        case INFECT:
                            infect(world.creatures[j], world.grid);
                            tempOutput = opName[INFECT];
                            break;
                        case IFEMPTY:
                            ifempty(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto nextTwo;
                        case IFENEMY:
                            ifenemy(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto nextTwo;
                        case IFSAME:
                            ifsame(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto nextTwo;
                        case IFWALL:
                            ifwall(world.creatures[j], world.grid, 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto nextTwo;
                        case GO:
                            go(world.creatures[j], 
                                    world.creatures[j].species->program[world.creatures[j].programID - 1].address);
                            goto nextTwo;
                    }   
                    cout << "Creature (" << world.creatures[j].species->name << " " << directName[tempDirection]
                         << " " << tempPoint.r << " " << tempPoint.c << ") takes action:" 
                         << " " << tempOutput << endl;
                }
                printState(world.grid);
            }
    }
    return 0;
}

#ifndef __SIMULATION_H__
#define __SIMULATION_H__
#include <iostream>
#include "world_type.h"

void printState(grid_t &grid);
//MODIFY: cout
//EFFECT: print the state diagram.

grid_t hop(creature_t &creature, grid_t &grid);
//EFFECT: Make a creature do the "hop" action
//REQUIRE: The grid should have an origin pointer to the creature.

grid_t left(creature_t &creature, grid_t &grid);
//EFFECT: Make a creature do the "turn left" action
//REQUIRE: The grid should have an origin pointer to the creature.

grid_t right(creature_t &creature, grid_t &grid);
//EFFECT: Make a creature do the "turn right" action
//REQUIRE: The grid should have an origin pointer to the creature.

grid_t infect(creature_t &creature, grid_t &grid);
//EFFECT: Make a creature do the "infect" action
//REQUIRE: The grid should have an origin pointer to the creature.

creature_t ifempty(creature_t &creature, grid_t &grid, int step);
//EFFECT: Judge "if it is empty" and change correspondingly

creature_t ifwall(creature_t &creature, grid_t &grid, int step);
//EFFECT: Judge "if it is empty" and change correspondingly

creature_t ifsame(creature_t &creature, grid_t &grid, int step);
//EFFECT: Judge "if it is empty" and change correspondingly

creature_t ifenemy(creature_t &creature, grid_t &grid, int step);
//EFFECT: Judge "if it is empty" and change correspondingly

creature_t go(creature_t &creature, int step);
//EFFECT: Just go and change

#endif /* __SIMULATION_H__ */

#include <iostream>
#include "binary_heap.h"
#include "unsorted_heap.h"

using namespace std;

const int MAXITEM = 10000;

enum direction_t { RIGHT, DOWN, LEFT, UP };
/*
// Type: direction_t
// ----------------
// This type is used to represent direction, which can take on
// one of the four values: East, South, West, and North.
*/


struct point_t
{
	int x;
	int y;
	int value;
	int pathcost;
	point_t* prev;
	bool ifReached;
};

struct compare_t
{
	bool operator()(point_t* a, point_t* b) const
	{
		if (a->pathcost < b->pathcost) return 1;
		else if (a->pathcost == b->pathcost)
		{
			if (a->x < b->x)  return 1;
			else if (a->x == b->x)
			{
				if (a->y < b->y) return 1;
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
};



struct grid_t
{
	int height;
	int width;
};



bool ifValid(point_t** a, int x_temp, int y_temp, direction_t direction, int width, int height)
{
	if (direction == RIGHT) x_temp++;
	else if (direction == DOWN) y_temp++;
	else if (direction == LEFT) x_temp--;
	else if ((direction == UP)) y_temp--;
	else;
	if (x_temp < 0 || x_temp >= width || y_temp < 0 || y_temp > height)
	{
		return false;
	}
	else if (a[x_temp][y_temp].ifReached) return false;
	else return true;
}



void deal(point_t *N, point_t *C)
{
	N->ifReached = true;
	N->pathcost = C->pathcost + N->value;
	cout << "Cell (" << N->x << ", " << N->y << ") with accumulated length " 
		 << N->pathcost << " is added into the queue." << endl;
	N->prev = C;
}



void trace_back_path(point_t* N, point_t *start, point_t* end)
{
	cout << "The shortest path from (" << start->x << ", " << start->y << ") to ("
		<< end->x << ", " << end->y << ") is " << N->pathcost << "." << endl;
	cout << "Path:" << endl;
	std::vector<point_t*> temp;
	point_t* temp_elt;
	while (N)
	{
		temp.push_back(N);
		N = N->prev;
	}
	while (!temp.empty())
	{
		temp_elt = temp[temp.size() - 1];
		temp.pop_back();
		cout << "(" << temp_elt->x << ", " << temp_elt->y << ")" << endl;
	}
}
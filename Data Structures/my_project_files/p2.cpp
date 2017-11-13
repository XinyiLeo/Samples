#define NORMAL
#ifdef NORMAL
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "functions.h"
using namespace std;


int main(int argc, char *argv[])
{
	string line;
	ifstream inputFile;
	istringstream iStream;
	grid_t grid;
	inputFile.open(argv[1]);
	if (!inputFile)
	{
		cout << "Error: Cannot open file " << argv[1] << "!" << endl;
		return 0;
	}
	//Read the width of the grid from the file
	getline(inputFile, line);
	iStream.str(line);
	iStream >> grid.width;
	iStream.clear();

	//Read the height of the grid from the file
	getline(inputFile, line);
	iStream.str(line);
	iStream >> grid.height;
	iStream.clear();

    //Dynamically construct the point_t pointers
	point_t **a;
	a = new point_t *[grid.width];
	for (int i = 0; i < grid.width; i++)
		a[i] = new point_t[grid.height];

	point_t startPoint, endPoint;
	getline(inputFile, line);
	iStream.str(line);
	iStream >> startPoint.x >> startPoint.y;
	iStream.clear();
	getline(inputFile, line);
	iStream.str(line);
	iStream >> endPoint.x >> endPoint.y;
	iStream.clear();
    

	for (int j = 0; j < grid.height; j++)
	{
		getline(inputFile, line);
		iStream.str(line);
		for (int i = 0; i < grid.width; i++)
		{
			//Initialize all the dynamic blocks
			iStream >> a[i][j].value;
			a[i][j].x = i;
		    a[i][j].y = j;
			a[i][j].pathcost = 0;
			a[i][j].ifReached = false;
			a[i][j].prev = NULL;
		}
		iStream.clear();
	}
    //#define TESTINPUT
    #ifdef TESTINPUT
	cout << "The height is: " << grid.height << endl;
	cout << "The width is: " << grid.width << endl;
	cout << "The start point is: (" << startPoint.x << " ," << startPoint.y << " )" << endl;
	cout << "The start point is: (" << endPoint.x << " ," << endPoint.y << " )" << endl;

	for (int i = 0; i < grid.width; i++)
	{
		for (int j = 0; j < grid.height; j++)
		{
			cout << "The value of point (" << a[i][j].x << " ," << a[i][j].y << " ) is " << a[i][j].value << endl;
		}
	}
    #endif

	priority_queue<point_t*, compare_t> *pql = new binary_heap<point_t*, compare_t>;
	point_t* C_temp, *N_temp;
	C_temp = &a[startPoint.x][startPoint.y];
	int round = 0;
	C_temp->pathcost = C_temp->value;
	C_temp->ifReached = true;
	pql->enqueue(C_temp);

	while (!pql->empty()) 
	{

//#define SEE_QUEUE
#ifdef SEE_QUEUE
		//See what's in the queue when debuging
		point_t** array = new point_t*[pql->size()];
		cout << "Now let's see what's in the queue:" << endl;
		int tempo = pql->size();
		for (int i = 0; i < tempo; i++)
		{
			array[i] = pql->dequeue_min();
			cout << i << " order: (" << array[i]->x << ", " << array[i]->y << ") with value " << array[i]->pathcost << endl;
		}
		for (int i = 0; i < tempo; i++)
		{
		    pql->enqueue(array[i]);
		}
		delete []array;
#endif
		C_temp = pql->dequeue_min();
		cout << "Step " << round << endl;
		cout << "Choose cell (" << C_temp->x << ", " << C_temp->y
			<< ") with accumulated length " << C_temp->pathcost << "." << endl;

		if (ifValid(a, C_temp->x, C_temp->y, RIGHT, grid.width, grid.height))
		{
			N_temp = &a[C_temp->x + 1][C_temp->y];
			deal(N_temp, C_temp);
			if (N_temp->x == endPoint.x && N_temp->y == endPoint.y)
			{
				trace_back_path(N_temp, &startPoint, &endPoint);
				return 0;
			}
			else
			{
				pql->enqueue(N_temp);
			}
		}

		if (ifValid(a, C_temp->x, C_temp->y, DOWN, grid.width, grid.height))
		{
			N_temp = &a[C_temp->x][C_temp->y + 1];
			deal(N_temp, C_temp);
			if (N_temp->x == endPoint.x && N_temp->y == endPoint.y)
			{
				trace_back_path(N_temp, &startPoint, &endPoint);
				return 0;
			}
			else
			{
				pql->enqueue(N_temp);
			}
		}

		if (ifValid(a, C_temp->x, C_temp->y, LEFT, grid.width, grid.height))
		{
			N_temp = &a[C_temp->x - 1][C_temp->y];
			deal(N_temp, C_temp);
			if (N_temp->x == endPoint.x && N_temp->y == endPoint.y)
			{
				trace_back_path(N_temp, &startPoint, &endPoint);
				return 0;
			}
			else
			{
				pql->enqueue(N_temp);
			}
		}
		if (ifValid(a, C_temp->x, C_temp->y, UP, grid.width, grid.height))
		{
			N_temp = &a[C_temp->x][C_temp->y - 1];
			deal(N_temp, C_temp);
			if (N_temp->x == endPoint.x && N_temp->y == endPoint.y)
			{
				trace_back_path(N_temp, &startPoint, &endPoint);
				return 0;
			}
			else
			{
				pql->enqueue(N_temp);
			}
		}
		round++;
	}

	//delete the pointer and close the file
	for (int i = 0; i < grid.height; i++)
		delete[] a[i];
	delete pql;
	iStream.clear();
	inputFile.close();
	return 0;
}

#endif
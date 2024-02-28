#pragma once

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Cell.h"
#include <math.h>
#include <time.h>
#include <iostream>
#include "glut.h"

using namespace std;

const int W = 500; // window Width
const int H = 500; // window Height
const int MSZ = 100;

enum State {
	SPACE,
	WALL,
	START,
	TARGET,
	BLACK,
	GRAY,
	PATH
};

class Maze {
private:
	int maze[MSZ][MSZ] = { 0 };
	int startR, startC, targetR, targetC;
public: 
	Maze() { InitMaze(); }
	int (*getMaze())[MSZ] { return maze; }

	void InitMaze();
	void DrawMaze();
	void RestorePath(Cell* pc);
	bool CheckNeighbor(int row, int col, Cell* pcurrent, vector<Cell*> &grays);
	double getDistanceFromCellToTarget(Cell* cur);
	double getDistanceFromCellToStart(Cell* cur);
	int getRowStart() { return startR; }
	int getColStart() { return startC; }
};

#endif
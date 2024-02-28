#pragma once

#ifndef AStar_H
#define AStar_H

#include "Maze.h"
#include <algorithm>

class AStar
{
private:
	Maze* pm;
	bool runAStar = false;
	vector <Cell*> grays;
public:
	AStar(Maze* maze) : pm(maze) {
		Cell* pc = new Cell(maze->getRowStart(), maze->getColStart(), nullptr);
		grays.push_back(pc);
	}
	void RunAStarIteration();
	Cell* getClosestOptionToAStar();
	bool getRunAStar() { return runAStar; }
	void setRunAStarTrue() { runAStar = true; }
};


#endif 
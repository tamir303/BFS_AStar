#pragma once

#ifndef BFS_H
#define BFS_H

#include "Maze.h"
#include <algorithm>

class BFS
{
private: 
	Maze* pm;
	bool runBestFirstSearch = false;
	bool isFinish = false;
	vector <Cell*> grays;
public:
	BFS(Maze* maze) : pm(maze) { 
		Cell* pc = new Cell(maze->getRowStart(), maze->getColStart(), nullptr);
		grays.push_back(pc);
	}
	void RunBestFirstSearchIteration();
	Cell* getClosestOptionToBestFirstSearch();
	bool getRunBestFirstSearch() { return runBestFirstSearch; }
	void setRunBestFirstSearchTrue() { runBestFirstSearch = true; }
	bool getIsFinish() { return isFinish; }
};


#endif 
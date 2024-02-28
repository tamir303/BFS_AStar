#include "BFS.h"
#include <iostream>

void BFS::RunBestFirstSearchIteration()
{
	Cell* pcurrent;
	int r, c;
	bool res = false;
	if (grays.empty()) // no solution exists
	{
		runBestFirstSearch = false; // stop running BFS
		cout << "No solution\n";
		return;
	}
	else // grays is not empty
	{
		pcurrent = getClosestOptionToBestFirstSearch(); // get the closest cell to target & pop it from grays vector.
		r = pcurrent->getRow();
		c = pcurrent->getColumn();
		pm->getMaze()[r][c] = BLACK; // paint it black
		// add all white neighbors of pcurrent to grays
		// UP
		if (runBestFirstSearch && (pm->getMaze()[r + 1][c] == SPACE || pm->getMaze()[r + 1][c] == TARGET))
			res = pm->CheckNeighbor(r + 1, c, pcurrent, grays) || res;
		// DOWN
		if (runBestFirstSearch && (pm->getMaze()[r - 1][c] == SPACE || pm->getMaze()[r - 1][c] == TARGET))
			res = pm->CheckNeighbor(r - 1, c, pcurrent, grays) || res;
		// LEFT
		if (runBestFirstSearch && (pm->getMaze()[r][c - 1] == SPACE || pm->getMaze()[r][c - 1] == TARGET))
			res = pm->CheckNeighbor(r, c - 1, pcurrent, grays) || res;
		// RIGHT
		if (runBestFirstSearch && (pm->getMaze()[r][c + 1] == SPACE || pm->getMaze()[r][c + 1] == TARGET))
			res = pm->CheckNeighbor(r, c + 1, pcurrent, grays) || res;

		if (res) // solution has been found
		{ 
			runBestFirstSearch = false; // stop running BFS
			isFinish = true;
		}
	}
}


// find the closest cell to TARGET from grays vector & erase it.
Cell* BFS::getClosestOptionToBestFirstSearch() {
	Cell* toRet = *grays.begin();
	double minDistance = 10000000, tempDistance = 1;
	int i = 0, remove = 0;
	for (Cell* cell : grays)// Find cell closest to target
	{
		tempDistance = pm->getDistanceFromCellToTarget(cell);
		if (tempDistance < minDistance)
		{
			minDistance = tempDistance;
			toRet = cell;
			remove = i;
		}
		i++;
	}

	if (remove >= 0 && remove < grays.size())
		grays.erase(grays.begin() + remove);
	return toRet;
}



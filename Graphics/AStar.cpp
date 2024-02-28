#include "AStar.h"

void AStar::RunAStarIteration()
{
	Cell* pcurrent;
	int r, c;
	bool res = false;
	if (grays.empty()) // no solution exists
	{
		runAStar = false; // stop running BFS
		cout << "No solution\n";
		return;
	}
	else // grays is not empty
	{
		pcurrent = getClosestOptionToAStar(); // get the closest cell to target + start & pop it from grays vector.
		r = pcurrent->getRow();
		c = pcurrent->getColumn();
		pm->getMaze()[r][c] = BLACK; // paint it black
		// add all white neighbors of pcurrent to grays
		// UP
		if (runAStar && (pm->getMaze()[r + 1][c] == SPACE || pm->getMaze()[r + 1][c] == TARGET))
			res = pm->CheckNeighbor(r + 1, c, pcurrent, grays);
		// DOWN
		if (runAStar && (pm->getMaze()[r - 1][c] == SPACE || pm->getMaze()[r - 1][c] == TARGET))
			res = res || pm->CheckNeighbor(r - 1, c, pcurrent, grays);
		// LEFT
		if (runAStar && (pm->getMaze()[r][c - 1] == SPACE || pm->getMaze()[r][c - 1] == TARGET))
			res = res || pm->CheckNeighbor(r, c - 1, pcurrent, grays);
		// RIGHT
		if (runAStar && (pm->getMaze()[r][c + 1] == SPACE || pm->getMaze()[r][c + 1] == TARGET))
			res = res || pm->CheckNeighbor(r, c + 1, pcurrent, grays);

		if (res) // solution has been found
			runAStar = false; // stop running BFS
	}
}

// find the closest cell to TARGET + START from grays vector & erase it.
Cell* AStar::getClosestOptionToAStar() {
	Cell* toRet = *grays.begin();
	double minHCost = INT_MAX, minGCost = INT_MAX, minTotalCost = INT_MAX, HCost, GCost, totalCost;
	int i = 0, remove = 0; // i = index, remove = index remember to use with vector.erase function.
	for (Cell* cell : grays)// Find cell closest to (target + start)
	{
		HCost = pm->getDistanceFromCellToTarget(cell); // distance of cell from target
		GCost = pm->getDistanceFromCellToStart(cell); // distance of cell from start
		totalCost = HCost + GCost; // total cost of cell
		if (totalCost < minTotalCost) // if total cost of cell is minimal -> save it's properties & cell to return
		{
			minTotalCost = totalCost;
			minHCost = HCost;
			minGCost = GCost;
			toRet = cell;
			remove = i; // to execute grays.erase(grays.begin() + remove)
		}
		else if (totalCost == minTotalCost) // if we have 2 cells with the same total cost - we choose to move on with the one that closer to the target -> lower HCost
		{
			if (HCost < minHCost)
			{
				minHCost = HCost;
				minGCost = GCost;
				toRet = cell;
				remove = i; // to execute grays.erase(grays.begin() + remove)
			}
		}
		i++;
	}
	grays.erase(grays.begin() + remove); // remove the cell that closest to (target + start) from grays vector
	return toRet;

	return nullptr;
}

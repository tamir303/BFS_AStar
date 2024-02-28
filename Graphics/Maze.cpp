#include "Maze.h"

using namespace std;

void Maze::InitMaze()
{
	int i, j;

	// the frame of maze is made of walls
	for (i = 0; i < MSZ; i++)
	{
		maze[0][i] = WALL;
		maze[MSZ - 1][i] = WALL;
		maze[i][0] = WALL;
		maze[i][MSZ - 1] = WALL;
	}
	for (i = 1; i < MSZ - 1; i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			if (i % 2 == 0) // mostly SPACES
			{
				if (rand() % 100 < 80)
					maze[i][j] = SPACE;
				else
					maze[i][j] = WALL;
			}
			else //  mostly walls
			{
				if (rand() % 100 < 60)
					maze[i][j] = WALL;
				else
					maze[i][j] = SPACE;
			}
		}
	// set START and TARGET
	startR = MSZ / 2;
	startC = MSZ / 2;
	targetR = rand() % MSZ;
	targetC = rand() % MSZ;
	maze[startR][startC] = START;
	maze[targetR][targetC] = TARGET;
}

void Maze::DrawMaze()
{
	int i, j;

	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			switch (maze[i][j])
			{
			case SPACE:
				glColor3d(0.9, 0.9, 0.9); // light gray
				break;
			case WALL:
				glColor3d(0.3, 0.3, 0.3); // dark gray
				break;
			case START:
				glColor3d(0.5, 0.5, 0.9); // blue
				break;
			case TARGET:
				glColor3d(0, 1, 0); // green
				break;
			case BLACK:
				glColor3d(0.7, 1, 0.7); // light green
				break;
			case GRAY:
				glColor3d(1, 0.3, 0); // orange
				break;
			case PATH:
				glColor3d(0.8, 0.5, 1); // purple
				break;
			}
			// draw square
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j + 1, i);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j, i + 1);
			glEnd();
		}

}

void Maze::RestorePath(Cell* pc)
{
	while (pc->getParent() != nullptr)
	{
		maze[pc->getRow()][pc->getColumn()] = PATH;
		pc = pc->getParent();
	}
}

bool Maze::CheckNeighbor(int row, int column, Cell* pcurrent, vector<Cell*> &grays)
{
	if (maze[row][column] == TARGET)
	{
		cout << "The solution has been found\n";
		RestorePath(pcurrent);
		return true;
	}
	else // maze[row][column] is WHITE
	{
		Cell* pn = new Cell(row, column, pcurrent);
		// paint this neighbor gray
		grays.push_back(pn);
		maze[row][column] = GRAY;
		return false;
	}
}

// get distance of given cell to target.
double Maze::getDistanceFromCellToTarget(Cell* cur)
{
	return sqrt(abs(pow(targetR - cur->getRow(), 2) + pow(targetC - cur->getColumn(), 2)));
}

// get distance of given cell from Start.
double Maze::getDistanceFromCellToStart(Cell* cur)
{
	return sqrt(abs(pow(startR - cur->getRow(), 2) + pow(startC - cur->getColumn(), 2)));
}


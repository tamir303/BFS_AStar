#include <stdlib.h>
#include "Maze.h"
#include "BFS.h"
#include "AStar.h"
#include <iostream>
#include "glut.h"
#include <time.h>

using namespace std;

Maze* pm;
BFS* pbfs;
AStar* paStar;

void init()
{
	srand(time(0));
	glClearColor(0,0.3,0.0,0);// color of window background
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system

	pm = new Maze();
	pbfs = new BFS(pm);
	paStar = new AStar(pm);
	pm->InitMaze();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	pm->DrawMaze();
	glutSwapBuffers(); // show all
}

void idle() 
{
	if (pbfs->getRunBestFirstSearch())
		pbfs->RunBestFirstSearchIteration();
	else if (paStar->getRunAStar())
		paStar->RunAStarIteration();

	glutPostRedisplay(); // indirect call to display
}

void menu(int choice) {
	switch (choice) {
	case 1: // Best First Search
		cout << "Ruuning Best First Search\n";
		pbfs->setRunBestFirstSearchTrue();
		break;
	case 2: // A*
		cout << "Ruuning A*\n";
		paStar->setRunAStarTrue();
		break;
	}
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Maze");

	glutDisplayFunc(display); // display is the refresh function
	glutIdleFunc(idle);

	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Run Best-First-Search", 1);
	glutAddMenuEntry("Run A*", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutMainLoop();
}
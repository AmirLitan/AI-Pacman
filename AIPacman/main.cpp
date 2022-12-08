#include "glut.h"
#include "Data.h"
#include "GameController.h"
#include <Windows.h>

GameController* controller;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	controller->moveEntitys();
	controller->showMap();
	controller->checkWinLoseScenario();
	Sleep(200);

	glutSwapBuffers(); // show all
}

void idle()
{
	glutPostRedisplay();
}

void main(int argc, char* argv[])
{
	controller = new GameController(argc, argv);

	glutDisplayFunc(display); //refersh function
	glutIdleFunc(idle); // Run all the time in the background

	glutMainLoop();
}
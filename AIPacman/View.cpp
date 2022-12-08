#include "View.h"

View::View()
{
}

View::View(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow(WINDOW_NAME);
}

View::~View()
{
}

void View::setBackGroundColor()
{
	glClearColor(0.2, 0.2, 0.2, 0);
}

void View::drawRoom(const int& i, const int& j,const int& tag)
{

			switch (tag)
			{
			case BLANK: //blank
				glColor3d(0.2, 0.2, 0.2);
				break;
			case WALL: //wall
				glColor3d(0, 0, 1);
				break;
			case ROOM:	//room
				glColor3d(0, 0, 1);
				break;
			case CORRIDOR: //corridor
				glColor3d(0, 0, 1);
				break;
			case CHECK: //check
				glColor3d(0.7, 1, 0.7);
				break;
			case TARGET: //target
				glColor3d(1, 1, 1);
				break;
			case START: //start
				glColor3d(0, 1, 0);
				break;
			case SEARCH: 
				glColor3d(0, 0.5, 0);
				break;
			case SEARCH_TARGET:
				glColor3d(1, 0, 1);
				break;
			case SEARCH_WALL:
				glColor3d(0, 0.8, 0);
				break;
			case CHECK_WALL:
				glColor3d(0.7, 0.7, 0.7);
				break;
			case PACMAN:
				glColor3d(1, 1, 0);
				break;
			case ENEMY:
				glColor3d(1, 0, 0.6);
				break;
			case TOKEN:
				glColor3d(1, 1, 1);
				break;
			case SWITCH_TOKEN:
				glColor3d(0, 1, 0);
				break;
			default:
				break;
			}
			if (tag == CORRIDOR || tag == PACMAN || tag == ENEMY)
			{
				glBegin(GL_POLYGON);
				glVertex2d(j, i);
				glVertex2d(j, 1 + i);
				glVertex2d(1 + j, 1 + i);
				glVertex2d(1 + j, i);
				glEnd();
			}
			else if (tag == SWITCH_TOKEN)
			{
				glBegin(GL_POLYGON);
				glVertex2d(j, i);
				glVertex2d(j, 1 + i);
				glVertex2d(1 + j, 1 + i);
				glVertex2d(1 + j, i);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
				glVertex2d(j, i);
				glVertex2d(j, 1 + i);
				glVertex2d(1 + j, 1 + i);
				glVertex2d(1 + j, i);
				glEnd();
			}
}





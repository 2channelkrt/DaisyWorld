
#include "base.h"
#include "patch.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

patch** world;

void randomPlace(float percentage, string color)
{
	srand(time(NULL));
	for(int i=0;i<CELL_X_NUM*CELL_Y_NUM*percentage;i++)
	{
		if (world[rand() % CELL_X_NUM][rand() % CELL_Y_NUM].allocDaisy(color) == false) i--;
	}
}

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	
	world = (patch**)malloc(sizeof(patch*)*CELL_X_NUM);
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		world[x] = (patch*)malloc(sizeof(patch)*CELL_Y_NUM);
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			world[x][y] = patch(BOARD_OFFSET_X + x * CELL_SIZE - 1, BOARD_OFFSET_Y + y * CELL_SIZE - 1, false, INIT_GLOBAL_TEMP);
		}
	}

	randomPlace(INIT_WHITE_DAISY_PERCENTAGE, "White");
	randomPlace(INIT_BLACK_DAISY_PERCENTAGE, "Black");

	/*for (int x = 0; x < CELL_X_NUM; x++)
	{
		for (int y = 0; y < CELL_Y_NUM; y++)
		{

		}
	}*/
}

void DrawBorder()
{
	glLineWidth(1);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	//when using dot, bracket each x, y
	dot(BOARD_OFFSET_X, BOARD_OFFSET_Y);
	dot((BOARD_OFFSET_X + CELL_SIZE * CELL_X_NUM + 1), BOARD_OFFSET_Y);
	dot(BOARD_OFFSET_X, BOARD_OFFSET_Y);
	dot(BOARD_OFFSET_X, (BOARD_OFFSET_Y + CELL_SIZE * CELL_X_NUM + 1));
	
	dot((BOARD_OFFSET_X + CELL_SIZE * CELL_X_NUM + 1), BOARD_OFFSET_Y);
	dot((BOARD_OFFSET_X + CELL_SIZE * CELL_X_NUM + 1), (BOARD_OFFSET_Y + CELL_SIZE * CELL_X_NUM + 1));

	dot(BOARD_OFFSET_X, (BOARD_OFFSET_Y + CELL_SIZE * CELL_X_NUM + 1));
	dot((BOARD_OFFSET_X + CELL_SIZE * CELL_X_NUM + 1), (BOARD_OFFSET_Y + CELL_SIZE * CELL_X_NUM + 1));
	glEnd();
}

void DrawPatch()
{
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			world[x][y].draw();
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawBorder();
	DrawPatch();

	glutSwapBuffers();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Hello World");

	init();
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}


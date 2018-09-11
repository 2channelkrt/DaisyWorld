
#include "base.h"
#include "patch.cpp"
#include <stdio.h>
#include <time.h>

patch** world;

void randomPlace(float percentage, int color)
{
	srand(time(NULL));
	int x, y;
	for(int i=0;i<CELL_X_NUM*CELL_Y_NUM*percentage;i++)
	{
		x = rand() % CELL_X_NUM;
		y = rand() % CELL_Y_NUM;
		if (world[x][y].isAlive() == true) i--;
		else world[x][y].AllocDaisy(color);
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
			world[x][y] = patch(BOARD_OFFSET_X + (x+0.5) * CELL_SIZE, BOARD_OFFSET_Y + (y+0.5) * CELL_SIZE, INIT_GLOBAL_TEMP);
		}
	}

	randomPlace(INIT_WHITE_DAISY_PERCENTAGE, 1);
	randomPlace(INIT_BLACK_DAISY_PERCENTAGE, 0);

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
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//DrawBorder();
	DrawPatch();
	glutSwapBuffers();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Daisy World");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	/*for (int x = 0; x < CELL_X_NUM; x++)
		free(world[x]);
	free(world);*/
	
	return 0;
}


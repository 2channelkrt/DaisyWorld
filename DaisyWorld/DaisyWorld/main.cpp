#include "patch.cpp"
#include <time.h>
#include <array>
#include <algorithm>
#include <random>
patch** world;
colorSystem cs;

std::array<int, CELL_X_NUM*CELL_Y_NUM> arr;

void initDaisyGen()
{
	for (int x = 0; x < CELL_X_NUM*CELL_Y_NUM; x++) arr[x] = x;
	shuffle(arr.begin(), arr.end(), std::default_random_engine(rand()));
}

void randomPlace(float percentage, int color)
{
	static int index = 0;
	int x, y;
	for (int i = index; i < index + CELL_X_NUM*CELL_Y_NUM * percentage; i++)
	{
		x = arr[i] / CELL_X_NUM;
		y = arr[i] % CELL_X_NUM;
		world[x][y].AllocDaisy(color);
	}
	index = CELL_X_NUM * CELL_Y_NUM * percentage;

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

	initDaisyGen();

	randomPlace(INIT_WHITE_DAISY_PERCENTAGE, 1);
	randomPlace(INIT_BLACK_DAISY_PERCENTAGE, 0);

	cs_init(&cs);
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
			world[x][y].drawDaisy();
			//world[x][y].drawPatch();
			
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

	srand(time(NULL));

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	/*for (int x = 0; x < CELL_X_NUM; x++)
		
	free(world);*/
	
	return 0;
}


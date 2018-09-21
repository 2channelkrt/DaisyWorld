#include "patch.cpp"
#include <time.h>
#include <Windows.h>
#include <array>
#include <algorithm>
patch** world;
colorSystem cs;
int grow[CELL_X_NUM][CELL_Y_NUM];

std::array<int, CELL_X_NUM*CELL_Y_NUM> arr;
std::array<int, 8> dir;

int world_time = 0;
float avg_temp;
float solar_lum;
float BD_rate;
float WD_rate;
float planet_albedo;

void initDaisyGen()
{
	for (int x = 0; x < CELL_X_NUM*CELL_Y_NUM; x++) arr[x] = x;
	shuffle(arr.begin(), arr.end(), std::default_random_engine(rand()));
	for (int x = 0; x < 8; x++) dir[x] = x;
	shuffle(dir.begin(), dir.end(), std::default_random_engine(rand()));
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

void initVariable()
{
	solar_lum = INIT_SOLAR_LUMINOSITY;
	BD_rate = INIT_BLACK_DAISY_PERCENTAGE;
	WD_rate = INIT_WHITE_DAISY_PERCENTAGE;
	planet_albedo = (BD_rate * BLACK_DAISY_ALBEDO + WD_rate * WHITE_DAISY_ALBEDO) / (BD_rate + WD_rate);
	avg_temp = pow(solar_lum*SOLAR_FLUX_CONSTANT*(1 - planet_albedo) / SB, 0.25) - 273;
	
}
bool spreadGrow(int x, int y,int color)
{
	if (x >= 0 && y >= 0 && x < CELL_X_NUM && CELL_Y_NUM && world[x][y].GetDaisyColor() == -1)
	{
		world[x][y].AllocDaisy(color);
		return true;
	}
	else return false;
}
void dirTrans(int* x, int *y,int dirValue)
{
	switch (dirValue)
	{
	case 0: *x += -1; *y += -1; break;
	case 1: *x += -1; *y += 0; break;
	case 2: *x += -1; *y += 1; break;
	case 3: *x += 0; *y += -1; break;
	case 4: *x += 0; *y += 1; break;
	case 5: *x += 1; *y += -1; break;
	case 6: *x += 1; *y += 0; break;
	case 7: *x += 1; *y += 1; break;
	}
}

void tryGrow(int x, int y, int color)
{
	for (int dirValue = 0; dirValue < 8; dirValue++)
	{
		dirTrans(&x, &y, dir[dirValue]);
		if (spreadGrow(x,y,color))//////////////////work here
		else dirTrans(&x, &y, dir[7 - dirValue]);
	}
}
void worldUpdate()
{
	//updatinv worldwide variable
	
	int Dcolor[2] = { 0,0 };
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			grow[x][y]=world[x][y].timePass();//actual time pass is here
		}
	}
	
	//get list of locations of new daisy. update them
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			if (grow[x][y] != -1)
			{
				shuffle(dir.begin(), dir.end(), std::default_random_engine(rand()));//shuffle spread dir
				tryGrow(x, y, grow[x][y]);
			}
		}
	}
	//
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			if (world[x][y].GetDaisyColor() != -1) Dcolor[world[x][y].GetDaisyColor()]++;
		}
	}
	solar_lum = INIT_SOLAR_LUMINOSITY + world_time * (1.2 / 200);
	BD_rate = Dcolor[0] / (float)(CELL_X_NUM*CELL_Y_NUM);
	WD_rate = Dcolor[1] / (float)(CELL_X_NUM*CELL_Y_NUM);
	planet_albedo = (BD_rate * BLACK_DAISY_ALBEDO + WD_rate * WHITE_DAISY_ALBEDO) / (BD_rate + WD_rate);
	avg_temp = pow(solar_lum*SOLAR_FLUX_CONSTANT*(1 - planet_albedo) / SB, 0.25) - 273;
	printf("avg temp: %f\n", avg_temp);
}
void initGrowArr()
{
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			grow[x][y] = -1;
		}
	}
}
void init()
{
	initVariable();
	initGrowArr();
	world = (patch**)malloc(sizeof(patch*)*CELL_X_NUM);
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		world[x] = (patch*)malloc(sizeof(patch)*CELL_Y_NUM);
		for (int y = 0; y < CELL_Y_NUM; y++)
		{
			world[x][y] = patch(BOARD_OFFSET_X + (x+0.5) * CELL_SIZE, BOARD_OFFSET_Y + (y+0.5) * CELL_SIZE);
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
			//world[x][y].drawDaisy();
			world[x][y].drawPatch();
			
		}
	}
}

void update()
{
	world_time++;
	worldUpdate();
	DrawPatch();
	Sleep(100);
}
void display() {
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	update();
	//printf("%d\n", world_time);
	glutSwapBuffers();
}
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(MAXFPS, TimerFunc, 1);
}
void Reshape(int w, int h)
{

}
void Mouse(int mouse_event, int state, int x, int y)
{

}
void Keyboard(unsigned char key, int x, int y)
{

}
void Motion(int x, int y)
{

}
int main(int argc, char *argv[])
{
	srand(time(NULL));
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Daisy World");
	
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(MAXFPS, TimerFunc, 1);
	glutMainLoop();
}

#include "patch.cpp"
#include <time.h>
#include <Windows.h>
#include <array>
#include <algorithm>

float started;

patch** world;
input* inputs;
colorSystem cs;
int grow[CELL_X_NUM][CELL_Y_NUM];

std::array<int, CELL_X_NUM*CELL_Y_NUM> arr;
std::array<int, 8> dir;

int world_time;
float avg_temp;
float solar_lum;
float BD_rate;
float WD_rate;
float BARREN_rate;
float planet_albedo;

float INIT_WHITE_DAISY_PERCENTAGE = 0.5;
float INIT_BLACK_DAISY_PERCENTAGE = 0.5;
float WHITE_DAISY_ALBEDO = 0.75;
float BLACK_DAISY_ALBEDO = 0.25;
float GROUND_ALBEDO = 0.5;
float DEATH_RATE = 0.3;
float INIT_SOLAR_LUMINOSITY = 0.6;

int randomPlaceIndex = 0;
int highlightedIndex = -1;
bool keyInputPlaceHolder = false;

void initDaisyGen()
{
	for (int x = 0; x < CELL_X_NUM*CELL_Y_NUM; x++) arr[x] = x;
	shuffle(arr.begin(), arr.end(), std::default_random_engine(rand()));
	for (int x = 0; x < 8; x++) dir[x] = x;
	shuffle(dir.begin(), dir.end(), std::default_random_engine(rand()));
}

void randomPlace(float percentage, int color)
{
	int x, y;
	for (int i = randomPlaceIndex; i < randomPlaceIndex + CELL_X_NUM*CELL_Y_NUM * percentage; i++)
	{
		x = arr[i] / CELL_X_NUM;
		y = arr[i] % CELL_X_NUM;
		world[x][y].AllocDaisy(color);
	}
	randomPlaceIndex = CELL_X_NUM * CELL_Y_NUM * percentage;

}

void initVariable()
{
	solar_lum = INIT_SOLAR_LUMINOSITY;
	BD_rate = INIT_BLACK_DAISY_PERCENTAGE;
	WD_rate = INIT_WHITE_DAISY_PERCENTAGE;
	BARREN_rate = 1 - (BD_rate + WD_rate);
	planet_albedo = BD_rate * BLACK_DAISY_ALBEDO + WD_rate * WHITE_DAISY_ALBEDO + BARREN_rate * GROUND_ALBEDO;
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
	int index = 0;
	int dirValue = rand() % 8; //randomizing try_spread direction
	while (index++ < 8)
	{
		dirTrans(&x, &y, dir[dirValue]);
		if (spreadGrow(x, y, color)) break;
		else dirTrans(&x, &y, dir[7 - dirValue]);
		dirValue++;
		dirValue %= 8;
	}
}
void drawInputSlotsMaskted()
{
	for (int i = 1; i < INPUT_NUM; i++)
	{
		inputs[i].draw(0.8, 0.8, 0.8);
	}
}
void drawInputSlots()
{
	for (int i = 0; i < INPUT_NUM; i++)
	{
		inputs[i].draw(1,1,1);
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
	BARREN_rate = 1 - (BD_rate + WD_rate);
	planet_albedo = BD_rate * BLACK_DAISY_ALBEDO + WD_rate * WHITE_DAISY_ALBEDO + BARREN_rate * GROUND_ALBEDO;
	avg_temp = pow(solar_lum*SOLAR_FLUX_CONSTANT*(1 - planet_albedo) / SB, 0.25) - 273;
	//printf("planet_albedo: %f avg temp: %f\n",planet_albedo, avg_temp);
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
void initUserInputSlots()
{
	inputs = (input*)malloc(sizeof(input)*INPUT_NUM);
	int i = 0;
	inputs[i++] = input(&started, "start");
	inputs[i++] = input(&INIT_WHITE_DAISY_PERCENTAGE, "white daisy percentage");
	inputs[i++] = input(&INIT_BLACK_DAISY_PERCENTAGE, "black daisy percentage");
	inputs[i++] = input(&WHITE_DAISY_ALBEDO, "white daisy albedo");
	inputs[i++] = input(&BLACK_DAISY_ALBEDO, "black daisy albedo");
	inputs[i++] = input(&GROUND_ALBEDO, "ground albedo");
	inputs[i++] = input(&DEATH_RATE, "death rate");
	inputs[i++] = input(&INIT_SOLAR_LUMINOSITY, "initial solar luminosity");
}
void freeWorld()
{
	for (int x = 0; x < CELL_X_NUM; x++)
	{
		free(world[x]);
	}
	free(world);
}

void initField()
{
	world_time = 0;
	initGrowArr();
	initVariable();
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
			world[x][y].drawDaisy();
			//world[x][y].drawPatch();
			
		}
	}
}
void ParamEnterAreaUpdate()
{
	drawInputSlots();
	for (int i = 0; i < INPUT_NUM; i++)
	{
		inputs[i].displayName();
		inputs[i].displayValue();
		//inputs[i].printValue();
	}
}
void update()
{
	if (started)
	{
		world_time++;
		worldUpdate();
		DrawPatch();
	}
	
	ParamEnterAreaUpdate();
	
	
	//Sleep(100);
}


void display() {
	glClearColor(0.5, 0.5, 0.5,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	update();
	//printf("%d\n", world_time);
	glutSwapBuffers();
}
void TimerFunc(int value)
{
	
	if(started) glutPostRedisplay();
	glutTimerFunc(MAXFPS, TimerFunc, 1);
}
void manageKeyStream(int newClick)
{
	if (highlightedIndex == newClick) keyInputPlaceHolder = true;
	else keyInputPlaceHolder = false;
	highlightedIndex = newClick;
}
void Reshape(int w, int h)
{

}
void Mouse(int key, int state, int x, int y)
{
	y = WINDOW_HEIGHT - y;
	if (started == 0)
	{//simulation not started
		if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && inputs[0].pressed(x, y))
		{
			initField();
			inputs[0].highlight();
			started = 1;
			manageKeyStream(0);
			inputs[0].changeName("stop");
			
		}
		else
		{
			for (int i = 1; i < INPUT_NUM; i++)
			{
				if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && inputs[i].pressed(x, y))
				{
					inputs[i].highlight();
					manageKeyStream(i);

					break;
				}
			}
		}
	}
	else
	{//simulation already started
		if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && inputs[0].pressed(x, y))
		{
			started = 0;
			freeWorld();
			randomPlaceIndex = 0;
			manageKeyStream(0);
			inputs[0].changeName("start");
		}
	}
	glutPostRedisplay();
	//if stop is clicked, enable start and all other inputs
}
void Keyboard(unsigned char key, int x, int y)
{
	printf("current highlight: %d\n", highlightedIndex);
	if (keyInputPlaceHolder == false)
	{ //new input
		printf("new highlighted slot\n");
		keyInputPlaceHolder = true;
	}
	else
	{//keep stream
		printf("same slot\n");
	}
}
void Motion(int x, int y)
{

}
int main(int argc, char *argv[])
{
	started = 0;
	srand(time(NULL));
	initUserInputSlots();
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

//defining static memebers of classes
char input::selected[30] = "null";
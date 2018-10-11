#include "base.cpp"
#include <freeglut.h>
#include <stdio.h>
class input
{
public:
	input(float* pointer)
	{
		static int index = 0;
		this->pointer = pointer;
		this->x = INPUT_SLOT_INIT_POS_X;
		this->y = INPUT_SLOT_INIT_POS_Y + (INPUT_SLOT_HEIGHT+INPUT_SLOT_SPACING) * index++;
		printf("%d %d %d\n", index, this->x, this->y);
	}
	void updateValue(float val)
	{
		*this->pointer = val;
	}
	void draw()
	{
		glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		dot((x), (y));
		dot((x+INPUT_SLOT_WIDTH), (y));
		dot((x+INPUT_SLOT_WIDTH), (y+INPUT_SLOT_HEIGHT));
		dot((x), (y+INPUT_SLOT_HEIGHT));
		glEnd();
	}
	bool isValid()
	{
		return *pointer <= 1 && *pointer >= 0;
	}
	bool pressed(int px, int py)
	{
		return this->x <= px && px <= (this->x + INPUT_SLOT_WIDTH) &&
			this->y <= py && py <= (this->y + INPUT_SLOT_HEIGHT);
	}
	void display()
	{
		glColor3f(0,0,0);
		glRasterPos3f(this->x,this->y,0);
		char buf[10];
		sprintf_s(buf,"%f",*this->pointer);
		//printf("%s\n", buf);
		for (int i = 0; i < (int)strlen(buf); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
		}
	}
	void printValue()
	{
		printf("%f\n", *this->pointer);
	}
private:
	float* pointer;
	int x;
	int y;
};
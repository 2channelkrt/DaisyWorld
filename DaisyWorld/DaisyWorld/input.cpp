#include "base.cpp"
#include <freeglut.h>
#include <stdio.h>
class input
{
public:
	input(float* pointer,const char* name)
	{
		static int index = 0;
		this->pointer = pointer;
		this->x = INPUT_SLOT_INIT_POS_X;
		this->y = INPUT_SLOT_INIT_POS_Y + (INPUT_SLOT_HEIGHT+INPUT_SLOT_SPACING) * index++;
		//printf("%d %d %d\n", index, this->x, this->y);
		strcpy_s(this->name, sizeof(this->name), name);
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
	void displayValue()
	{
		glColor3f(0, 0, 0);
		glRasterPos2d((this->x + INPUT_VALUE_X_OFFSET) * 2 / (float)WINDOW_WIDTH - 1, (this->y + INPUT_VALUE_Y_OFFSET) * 2 / (float)WINDOW_HEIGHT - 1);
		char buf[10];
		_gcvt_s(buf, 10, *this->pointer, 5);

		for (int i = 0; i < sizeof(buf); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
		}
	}
	void displayName()
	{
		glColor3f(1,0,0);
		//printf("drawing at %d %d\n", this->x, this->y);
		glRasterPos2f((this->x + INPUT_SLOT_WIDTH + 10) * 2 / (float)WINDOW_WIDTH - 1, this->y * 2 / (float)(WINDOW_HEIGHT) - 1);
		
		//printf("%s\n",buf);
		for (int i = 0; i < sizeof(this->name); i++)
		{
			//printf("%c", buf[i]);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this->name[i]);
		}
		//printf("\n");
	}
	void printValue()
	{
		printf("%f\n", *this->pointer);
	}
	void changeName(const char* string)
	{
		strcpy_s(this->name, sizeof(this->name), string);
	}
private:
	float* pointer;
	char name[30];
	int x;
	int y;
};
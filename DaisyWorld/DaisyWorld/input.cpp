#include "base.cpp"
#include "GL/freeglut.h"
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
		//strcpy_s(this->name, strlen(this->name), name);
		//strcpy_s(this->selected, sizeof(this->selected), "null");
	}
	void updateValue(float val)
	{
		*this->pointer = val;
	}
	bool isHighlighted()
	{
		return strcmp(this->name, this->selected) == 0;
	}
	void drawHighlight()
	{
		//printf("highlighted %s\n", this->name);
		glLineWidth(3.0f);
		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		dot((x), (y));
		dot((x + INPUT_SLOT_WIDTH), (y));
		dot((x + INPUT_SLOT_WIDTH), (y + INPUT_SLOT_HEIGHT));
		dot((x), (y + INPUT_SLOT_HEIGHT));
		glEnd();
	}
	void draw(float r,float g,float b)
	{
		glBegin(GL_QUADS);
		glColor3f(r,g,b);
		dot((x), (y));
		dot((x+INPUT_SLOT_WIDTH), (y));
		dot((x+INPUT_SLOT_WIDTH), (y+INPUT_SLOT_HEIGHT));
		dot((x), (y+INPUT_SLOT_HEIGHT));
		glEnd();
		if(this->isHighlighted())
			this->drawHighlight();
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
		if (strcmp(this->name, "start") != 0 && strcmp(this->name, "stop") != 0)
		{
			glColor3f(0, 0, 0);
			glRasterPos2d((this->x + INPUT_VALUE_X_OFFSET) * 2 / (float)WINDOW_WIDTH - 1, (this->y + INPUT_VALUE_Y_OFFSET) * 2 / (float)WINDOW_HEIGHT - 1);
			char buf[10];
			//_gcvt_s(buf, 10, *this->pointer, 5);
			_gcvt(*this->pointer, MAX_DISPLAY_DIGITS, buf);

			for (int i = 0; i < strlen(buf); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
			}
		}
	}
	void displayName()
	{
		glColor3f(1,0,0);
		glRasterPos2f((this->x + INPUT_SLOT_WIDTH + 10) * 2 / (float)WINDOW_WIDTH - 1, this->y * 2 / (float)(WINDOW_HEIGHT) - 1);
		
		for (int i = 0; i < strlen(this->name); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this->name[i]);
		}
	}
	void printValue()
	{
		printf("%f\n", *this->pointer);
	}
	void changeName(const char* string)
	{
		strcpy_s(this->name, sizeof(this->name), string);
	}
	void highlight()
	{
		strcpy_s(this->selected, sizeof(this->selected), this->name);
	}
	void setValue(float val)
	{
		*this->pointer = val;
	}
	float getValue()
	{
		return *this->pointer;
	}
private:
	float* pointer;
	char name[30];
	static char selected[30];
	int x;
	int y;
};


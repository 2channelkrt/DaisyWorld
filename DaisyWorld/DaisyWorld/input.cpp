#include "base.cpp"
#include <freeglut.h>

class input
{
public:
	input(float* pointer)
	{
		static int index = 0;
		this->pointer = pointer;

		this->x = INPUT_SLOT_INIT_POS_X;
		this->y = INPUT_SLOT_INIT_POS_Y + (INPUT_SLOT_HEIGHT+INPUT_SLOT_SPACING) * index++;
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
private:
	float* pointer;
	int x;
	int y;
};
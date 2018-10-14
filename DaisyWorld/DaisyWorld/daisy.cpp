
#include "color.h"
#include "input.cpp"

class Daisy
{
public:
	Daisy()
	{
		this->kill();
	}
	void SetDaisy(int color)
	{
		this->color = color;
		this->age = 0;
		this->alive = true;
	}

	void GetDrawColor()
	{
		if (this->color == 1) glColor3f(1, 1, 1);
		else if (this->color == 0) glColor3f(0, 0, 0);
		else printf("color not found\n");
	}
	float GetDiffuseTemp()
	{
		return 11;
	}
	bool GetAlive() { return this->alive; }
	void kill()
	{
		this->alive = false;
		this->color = -1;
		this->age = -1;
	}
	int GetColor() { return this->color; }
private:
	bool alive;
	int color; //1 is white, 0 is black
	int age;

	
};

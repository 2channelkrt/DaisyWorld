#include <freeglut.h>
#include "base.h"
#include <stdio.h>
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
		if (this->color == 1) this->albedo = WHITE_DAISY_ALBEDO;
		else if(this->color == 0) this->albedo = BLACK_DAISY_ALBEDO;
		else printf("Daisy init function error. Color unknown");
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
private:
	bool alive;
	int color; //1 is white, 0 is black
	float albedo;
	int age;

	void kill()
	{
		this->alive = false;
		this->color = -1;
		this->albedo = -1;
		this->age = -1;
	}
};
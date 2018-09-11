#include <freeglut.h>
#include "base.h"
#include <string>

using namespace std;

class Daisy
{
public:
	Daisy(string color)
	{
		this->color = color;
		this->age = 0;
		if (this->color == "White") this->albedo = WHITE_DAISY_ALBEDO;
		else if(this->color == "Black") this->albedo = BLACK_DAISY_ALBEDO;
		else printf("Daisy init function error. Color unknown");
	}

	void SetDrawColor()
	{
		printf("%s", color);
		printf("hello");
		/*if (this->color.compare("White")) glColor3f(1, 1, 1);
		else if (this->color.compare("Black")) glColor3f(0, 0, 0);
		else printf("SetDrawColor Color exception\n");*/
	}
	float GetDiffuseTemp()
	{
		return 11;
	}
private:
	string color;
	float albedo;
	int age;
};
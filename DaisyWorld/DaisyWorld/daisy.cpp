#include "base.h"
#include "basicDaisy.cpp"

class daisy : basicDaisy
{
public:
	daisy(string color) : basicDaisy(color)
	{
		this->color = color;
		this->age = 0;
	}

	void update() //need to be called after current patch update
	{
		//todo
	}

	float getDiffuseTemp()
	{
		//return temp;
	}

private:
	//does each daisy has to retain its place info?
	int age;

	
};
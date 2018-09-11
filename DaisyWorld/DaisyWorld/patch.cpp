#include "Daisy.cpp"
#include <stdlib.h>
class patch
{
public :
	patch(int windowX, int windowY, float temperature)
	{
		this->windowX = windowX;
		this->windowY = windowY;
		this->daisy = Daisy();
		this->temperature = temperature;
	}

	void setTemp(float temperature)
	{
		this->temperature = temperature;
		this->updateColor();
	}
	void timePass(int solarity)
	{
		//update temperature based on solarity
		this->updateTemperature();
		this->updateColor();
		
	}
	void draw()
	{
		if (this->daisy.GetAlive() == true)
		{
			glBegin(GL_QUADS);
			this->daisy.GetDrawColor();
			dot((this->windowX - (CELL_SIZE / 2)), (this->windowY - (CELL_SIZE / 2)));
			dot((this->windowX - (CELL_SIZE / 2)), (this->windowY + (CELL_SIZE / 2)));
			dot((this->windowX + (CELL_SIZE / 2)), (this->windowY + (CELL_SIZE / 2)));
			dot((this->windowX + (CELL_SIZE / 2)), (this->windowY - (CELL_SIZE / 2)));
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
			glColor3f(0.5, 0.5, 0.5);
			dot((this->windowX - (CELL_SIZE / 2)), (this->windowY - (CELL_SIZE / 2)));
			dot((this->windowX - (CELL_SIZE / 2)), (this->windowY + (CELL_SIZE / 2)));
			dot((this->windowX + (CELL_SIZE / 2)), (this->windowY + (CELL_SIZE / 2)));
			dot((this->windowX + (CELL_SIZE / 2)), (this->windowY - (CELL_SIZE / 2)));
			glEnd();
		}
	}
	bool isAlive() { return this->daisy.GetAlive(); }
	void AllocDaisy(int color)
	{
		this->daisy.SetDaisy(color);
	}
private:
	int windowX, windowY;
	Daisy daisy;
	float temperature;

	void updateColor()
	{

	}
	void updateTemperature()
	{
		float diffuseTemp = this->daisy.GetDiffuseTemp();
	}
};
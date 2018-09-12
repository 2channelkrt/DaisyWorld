#include "Daisy.cpp"
#include <stdlib.h>

extern colorSystem cs;

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
	void drawPatch()
	{
		glBegin(GL_QUADS);
		this->GetDrawColor();
		dot((this->windowX - (CELL_SIZE / 2)), (this->windowY - (CELL_SIZE / 2)));
		dot((this->windowX - (CELL_SIZE / 2)), (this->windowY + (CELL_SIZE / 2)));
		dot((this->windowX + (CELL_SIZE / 2)), (this->windowY + (CELL_SIZE / 2)));
		dot((this->windowX + (CELL_SIZE / 2)), (this->windowY - (CELL_SIZE / 2)));
		glEnd();
	}
	void drawDaisy()
	{
		if (this->daisy.GetAlive())
		{
			glBegin(GL_QUADS);
			//glColor3f(0.5, 0.5, 0);
			this->daisy.GetDrawColor();
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

	void updateTemperature()
	{
		float diffuseTemp = this->daisy.GetDiffuseTemp();
	}

	void GetDrawColor()
	{
		float x, y, z;
		float r, g, b;
		float temp = rand() % 70 - 20; //this is for debug purpose
		float relative = (temp - MIN_TEMP)/ (MAX_TEMP - MIN_TEMP);
		relative = 380 + (680-380)*relative;
		//printf("%f \n", relative);
		spectrum_to_xyz(relative, &x, &y, &z);
		xyz_to_rgb(&cs, x, y, z, &r, &g, &b);
		//printf("%f %f %f\n", r, g, b); 
		norm_rgb(&r, &g, &b);
		
		glColor3f(r, g, b);
		
	}
	void updateColor()
	{

	}
};
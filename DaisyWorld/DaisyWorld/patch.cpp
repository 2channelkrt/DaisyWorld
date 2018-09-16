#include "Daisy.cpp"
#include <stdlib.h>
#include <random>
extern colorSystem cs;

extern float avg_temp;
extern float solar_lum;
extern float BD_rate;
extern float WD_rate;
extern float planet_albedo;

class patch
{
public :
	patch(int windowX, int windowY)
	{
		this->windowX = windowX;
		this->windowY = windowY;
		this->daisy = Daisy();
		this->albedo = GROUND_ALBEDO;
		this->updateTemp();
	}

	void updateTemp()
	{
		if (this->daisy.GetAlive())
		{
			if (this->daisy.GetColor() == 1) this->temperature = HEAT_ABSORB_FACTOR*(planet_albedo - WHITE_DAISY_ALBEDO) + avg_temp;
			else this->temperature = HEAT_ABSORB_FACTOR * (planet_albedo - BLACK_DAISY_ALBEDO) + avg_temp;
		}
		else
		{
			this->temperature = pow(solar_lum*SOLAR_FLUX_CONSTANT*0.5 / SB, 0.25) - 273;
			//printf("%f %f %f\n", solar_lum, solar_lum*SOLAR_FLUX_CONSTANT*0.5, solar_lum*SOLAR_FLUX_CONSTANT*0.5 / SB);
			//printf("patch temp: %f\n", this->temperature);
		}
	}
	int GetDaisyColor() { return this->daisy.GetColor(); }
	void timePass()
	{
		//update daisy status
		int spread = -1;
		int prob;
		if (this->daisy.GetAlive() == true)
		{
			prob = rand() % 100;
			if (prob <= DEATH_RATE * 100) this->killDaisy();
		}
		double growRate = 1 - 0.003265*pow(22.5 - this->temperature, 2);
		prob = rand() % 100;
		if (prob <= growRate * 100)
		{
			if (this->daisy.GetAlive() == true)
			{
				spread = rand() % 8;
				//grow on another patch
			}
			else
			{
				this->AllocDaisy(rand() % 2);
			}
		}
		this->updateTemp();
		
	}
	void drawPatch()
	{
		glBegin(GL_QUADS);
		this->GetDrawTempColor();
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
	void killDaisy()
	{
		if (this->daisy.GetAlive() == false) printf("Daisy already dead\n");
		
		this->daisy.kill();
		this->albedo = GROUND_ALBEDO;
	}
	void AllocDaisy(int color)
	{
		this->daisy.SetDaisy(color);
		if (color == 1) this->albedo = WHITE_DAISY_ALBEDO;
		else if (color == 0) this->albedo = BLACK_DAISY_ALBEDO;
		else printf("AllocDaisy Color invalid\n");
	}
private:
	int windowX, windowY;
	Daisy daisy;
	float temperature;
	float albedo;

	void GetDrawTempColor()
	{
		float x, y, z;
		float r, g, b;
		float input;
		input = this->temperature < MAX_TEMP ? this->temperature : MAX_TEMP;
		input = input > MIN_TEMP ? input : MIN_TEMP;
		float relative = (input - MIN_TEMP)/ (MAX_TEMP - MIN_TEMP);
		relative = 380 + (680-380)*relative;
		//printf("%f \n", relative);
		spectrum_to_xyz(relative, &x, &y, &z);
		xyz_to_rgb(&cs, x, y, z, &r, &g, &b);
		//printf("%f %f %f\n", r, g, b); 
		norm_rgb(&r, &g, &b);
		
		glColor3f(r, g, b);
		
	}
};
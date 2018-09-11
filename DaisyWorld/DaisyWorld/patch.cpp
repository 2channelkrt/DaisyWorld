#include "Daisy.cpp"

class patch
{
public :
	patch(int windowX, int windowY,bool exist, float temperature)
	{
		this->windowX = windowX;
		this->windowY = windowY;

		this->exist = exist;
		this->temperature = temperature;
	}
	bool allocDaisy(string color)
	{
		if (this->exist == true) return false;
		else
		{
			this->daisy = &Daisy(color);
			this->exist = true;
			return true;
		}
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
	bool GetExist() { return this->exist; }
	void draw()
	{
		if (this->exist == false) return;
		glBegin(GL_QUADS);
		this->daisy->SetDrawColor();
		dot(this->windowX - (CELL_SIZE / 2), this->windowY - (CELL_SIZE / 2));
		dot(this->windowX - (CELL_SIZE / 2), this->windowY + (CELL_SIZE / 2));
		dot(this->windowX + (CELL_SIZE / 2), this->windowY + (CELL_SIZE / 2));
		dot(this->windowX + (CELL_SIZE / 2), this->windowY - (CELL_SIZE / 2));
		glEnd();
	}

private:
	int windowX, windowY;
	bool exist;
	Daisy* daisy;
	float temperature;

	void updateColor()
	{

	}
	void updateTemperature()
	{
		float diffuseTemp=this->daisy->GetDiffuseTemp();
	}
};
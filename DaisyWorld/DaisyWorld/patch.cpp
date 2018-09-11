#include "daisy.cpp"

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
	bool allocDaisy(daisy* daisy)
	{
		if (this->exist == false) return false;
		else
		{
			this->daisy = daisy;
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
	bool exist() { return exist; }

private:
	int windowX, windowY;
	bool exist;
	daisy* daisy;
	float temperature;

	void updateColor()
	{

	}
	void updateTemperature()
	{
		int diffuseTemp=this->daisy->getDiffuseTemp();
	}
};
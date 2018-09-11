#include "base.h"
#include <string>
using namespace std;

class basicDaisy
{
public:
	basicDaisy(string color)
	{
		if (color == "White")
		{
			this->color = color;
			this->albedo = WHITE_DAISY_ALBEDO;

		}
		if (color == "Black")
		{
			this->albedo = BLACK_DAISY_ALBEDO;
		}
	}
private:
	

protected:
	float albedo;
	string color;
};
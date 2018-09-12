typedef struct colourSystem
{
	float xRed;
	float yRed;
	float xGreen;
	float yGreen;
	float xBlue;
	float yBlue;
	float xWhite;
	float yWhite;
	float gamma;
}colorSystem;

//float bbTemp = 2000;

void cs_init(colorSystem* cs);

void xyz_to_rgb(struct colourSystem *cs,
	float xc, float yc, float zc,
	float *r, float *g, float *b);

void spectrum_to_xyz(float wavelength,
	float *x, float *y, float *z);

float bb_spectrum(float wavelength);

void norm_rgb(float *r, float *g, float *b);
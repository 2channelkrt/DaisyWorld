#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 650
#define CELL_X_NUM 200
#define CELL_Y_NUM 200
#define BOARD_OFFSET_X 10
#define BOARD_OFFSET_Y 10
#define CELL_SIZE 3

#define MAX_TEMP 40
#define MIN_TEMP 5

#define INPUT_SLOT_INIT_POS_X 800
#define INPUT_SLOT_INIT_POS_Y 50
#define INPUT_SLOT_SPACING 10
#define INPUT_SLOT_WIDTH 80
#define INPUT_SLOT_HEIGHT 40


#define SB 0.00000005669

#define MIX_COEFFICIENT 20
#define HEAT_ABSORB_FACTOR 20

#define INPUT_NUM 8
///////////////////////////////////////////
extern float INIT_WHITE_DAISY_PERCENTAGE;
extern float INIT_BLACK_DAISY_PERCENTAGE;
extern float WHITE_DAISY_ALBEDO;  //reflective portion. between 0~1
extern float BLACK_DAISY_ALBEDO;
extern float GROUND_ALBEDO;
extern float DEATH_RATE;
extern float INIT_SOLAR_LUMINOSITY;

/////////////////////////////////////above is user-changable////////////////
#define SOLAR_FLUX_CONSTANT 917

#define dot(x,y) glVertex2f((x/(float)WINDOW_WIDTH-0.5f)*2,(y/(float)WINDOW_HEIGHT-0.5f)*2)
#define COLOR_NUM 79
#define MAXFPS 60
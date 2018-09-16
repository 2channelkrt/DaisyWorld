#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define CELL_X_NUM 200
#define CELL_Y_NUM 200
#define BOARD_OFFSET_X 10
#define BOARD_OFFSET_Y 10
#define CELL_SIZE 3
#define INIT_WHITE_DAISY_PERCENTAGE 0.5  //0~1
#define INIT_BLACK_DAISY_PERCENTAGE 0.5  //0~1

#define MAX_TEMP 40
#define MIN_TEMP 5

#define SOLAR_FLUX_CONSTANT 917
#define SB 0.00000005669

#define WHITE_DAISY_ALBEDO 0.75  //reflective portion. between 0~1
#define BLACK_DAISY_ALBEDO 0.25
#define GROUND_ALBEDO 0.5
#define DEATH_RATE 0.3
#define MIX_COEFFICIENT 20
#define INIT_SOLAR_LUMINOSITY 0.6
#define HEAT_ABSORB_FACTOR 20

/////////////////////////////////////above is user-changable////////////////


#define dot(x,y) glVertex2f((x/(float)WINDOW_WIDTH-0.5f)*2,(y/(float)WINDOW_HEIGHT-0.5f)*2)
#define COLOR_NUM 79
#define MAXFPS 60
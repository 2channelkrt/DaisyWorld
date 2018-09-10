#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 720
#define CELL_X_NUM 200
#define CELL_Y_NUM 200
#define BOARD_OFFSET_X 10
#define BOARD_OFFSET_Y 10
#define CELL_SIZE 3

#define dot(x,y) glVertex2f((x/(float)WINDOW_WIDTH-0.5f)*2,(y/(float)WINDOW_HEIGHT-0.5f)*2)
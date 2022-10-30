#include <stdint.h>
#include <colors.h>
#include <libvid.h>

typedef struct {
    uint8_t posX;
    uint8_t posY;
    uint8_t direction;
    Color color;    
} Player;

/*
	Color white = {0xFF, 0xFF, 0xFF};
	Color black = {0x00, 0x00, 0x00};
	Color grey = {0x7F, 0x7F, 0x7F};
	Color blue = {0xFF, 0x00, 0x00};
	Color green = {0x00, 0xFF, 0x00};
	Color red = {0x00, 0x00, 0xFF};
	Color yellow = {0x00, 0xFF, 0xFF};
	Color cyan = {0xFF, 0xFF, 0x00};
	Color orange = {0x00, 0xA5, 0xFF};
	Color pink = {0xCB, 0xC0, 0xFF};
*/

static Player player1;
static Player player2;

enum DIRECTIONS {
    up = 0, 
    down, 
    left, 
    right
}Dirs;



//ejecuta el tron
void play_tron(){
    //seteamos pantalla -> players -> lectura para teclado (wasd player1 y flechas player2) -> 
    uint64_t screen[] = getScreenData(); //syscall que nos da los datos de la pantalla -> por el momento 0 = width y 1 = height
    setScreen(screen[0], screen[1]);
    setPlayers();
    
}

//hace la ventana en donde se juega al tron
void setScreen(uint64_t width, uint64_t height){
    Color bg_color = {0x3C, 0xA6, 0x03};
    do_clearScreen(bg_color);
    //paint bordes y no tomarlos
    int board[width][height]; //chequear cto sacamos (ESTA EN TAM PIXEL)
}

uint64_t * getScreenData(){ 
    return sys_getScreenData();
}

void setPlayers(){
    player1->posX = ;
    player1->posY = y;
    player1->direction = RIGHT; //hacemos un enum con UP, DOWN, LEFT, RIGHT
    player2->posX = ;
    player2->posY = y;
    player2->direction = LEFT;
}


#include <stdint.h>
#include <colors.h>
#include <libvid.h>
#include <syscalls.h>

#define SIZE 8

typedef struct {
    uint64_t posX;
    uint64_t posY;
    uint8_t direction;
    uint8_t state;
    Color color;    
} Player;

const Color tronColor1 = {0x40, 0x3C, 0x19};
const Color tronColor2 = {0x02, 0x59, 0x2E};
const Color tronColor3 = {0x01, 0x40, 0x21};
const Color tronColor4 = {0x41, 0x69, 0xD9};
const Color tronColor5 = {0x1F, 0x2B, 0xA6};


const Color white = {0xFF, 0xFF, 0xFF};
const Color black = {0x00, 0x00, 0x00};
const Color grey = {0x7F, 0x7F, 0x7F};
const Color blue = {0xFF, 0x00, 0x00};
const Color green = {0x00, 0xFF, 0x00};
const Color red = {0x00, 0x00, 0xFF};
const Color yellow = {0x00, 0xFF, 0xFF};
const Color cyan = {0xFF, 0xFF, 0x00};
const Color orange = {0x00, 0xA5, 0xFF};
const Color pink = {0xCB, 0xC0, 0xFF};

Player player1;
Player player2;

enum DIRECTIONS {
    up = 0, 
    down, 
    left, 
    right
}Dirs;


void getScreenData(uint64_t * data){ 
    return sys_getScreenData(data);
}

void do_paintRect(uint64_t fromX, uint64_t fromY, uint64_t width, uint64_t height, Color color){
    return sys_paint_rect(fromX, fromY, height, width, color);
}

//ESTAMOS PONIENDO BOARD COMO B[Y][X] 
//BOARD NO TIENE LOS BORDES EN CUENTA 
static int isAlive(Player  p, uint16_t width, uint16_t height, uint8_t ** board) {
    return p.posX < height && p.posX > 0 && p.posY < width && p.posY > 0 && !board[p.posY][p.posX]; //chequeo rango
}

static void updatePosition(uint64_t keypressed){
    switch (keypressed)
            {
            // caso default no existe ya q tiene q hacer algo siempre
            case 'w':
                if (player1.direction != 's'){ //opposite 
                    player1.posY--;
                    player1.direction = 'w';
                }
                break;
            case 'a':
                if(player1.direction != 'd'){
                    player1.posX++;
                    player1.direction = 'a';
                }
                break;
            case 's':
                if(player1.direction != 'w'){
                    player1.posY++;   
                    player1.direction = 's';
                }
                break;
            case 'd':
                if (player1.direction != 'a'){
                    player1.posX++;
                    player1.direction = 'd';
                }
                break;
            //Player 2
            case 'U': //up
                if (player2.direction != 'D'){ //opp opp?
                    player2.posY--;
                    player2.direction = 'U';
                }
                break;
            case 'L': //left
                if(player2.direction != 'R'){
                    player2.posX--;
                    player2.direction = 'L';
                }
                break;
            case 'D': //down
                if(player2.direction != 'U'){
                    player2.posY++;   
                    player2.direction = 'D';
                }
                break;
            case 'R': //right
                if (player2.direction != 'L'){
                    player2.posX++;
                    player2.direction = 'R';
                }
                break;
            }
}



//ejecuta el tron
void play_tron(){
//recordar d bloquear el resto tel teclado
    //seteamos pantalla -> players -> lectura para teclado (wasd player1 y flechas player2) -> 
    uint64_t screen[2] = {0}; //syscall que nos da los datos de la pantalla . por el momento 0 = width y 1 = height
    getScreenData(screen);
    setScreen(screen[0], screen[1]);
    setPlayers(screen[0],screen[1]);
    
    const int8_t width = (screen[0]-16)/8;
    const uint8_t height = (screen[1]-16)/8;
    uint8_t board[width][height]; //me pa q 
    for(int i = 0; i < width;i++) for(int j = 0; j< height; j++)  board[i][j]=0; 
    //uint8_t alive1 = 1, alive2 = 1;
    uint64_t speed = 3;
    uint64_t ticks = sys_getTicks();
    uint64_t lastTicks = 0;
    while(player1.state /*= isAlive(player1, screen[0], screen[1], board)*/ && player2.state){
        char c = getChar();
        updatePosition(c);
        if (lastTicks != ticks && ticks % speed == 0){ 
             //este getchar espera enter 
            //desps lo vemos pq usa el sys_read y eso tiene para esperar enter
            //haces el switch y player1.posY += SIZE ponele
            //board[player1.posY / SIZE][player1.posX / SIZE] = 1;
            //board[player2.posY / SIZE][player2.posX / SIZE] = 1; check q /size da bien!
            updatePosition(player1.direction);
            updatePosition(player2.direction);
            do_paintRect((player1.posX)*SIZE, (player1.posY) *SIZE, SIZE, SIZE, player1.color);
            do_paintRect((player2.posX)*SIZE, (player2.posY)*SIZE, SIZE, SIZE, player2.color);
            board[player1.posY][player1.posX]=1;
            board[player2.posY][player2.posX]=1;
            lastTicks = ticks;
        }
        ticks = sys_getTicks();
        //hacer syscall que espere n segundos o n ticks para ir imprimiendo
    }
    
    /*
    const int8_t width = (screen[0]-16)/8;
    const uint8_t height = (screen[1]-16)/8;
    uint8_t board[width][height];
    for (int i = 0; i < width; ++i) for (int j = 0; i < height; ++j) board[i][j] = 0;
    setPlayers(screen[0], screen[1]);
    uint16_t end = 0;
    while (1){
        //lectura d ambos jugadores . pinto posicion
        //si no choca => pinto
        // RECORDAR Q SI CHOCA => MUERE
        // No puede volver hacia atras, el cambio UP.DOWN y LEFT.RIGHT no se pueden hacer
        if (isAlive(player1, width, height, board) && isAlive(player2, width, height, board) ){ //dentro d parametros y no estaba pintado ya
            board[(player1.posX/8)-1][(player1.posY/8)-1] = 1;
            board[(player2.posX/8)-1][(player2.posY/8)-1] = 1;
            do_paintRect(player1.posX,player1.posY,player1.posX + SIZE, player1.posY + SIZE, player1.color); //xs ys xi yi color
            do_paintRect(player2.posX,player2.posY,player2.posX + SIZE, player2.posY + SIZE, player2.color);
        }
        else{
            end=0;
        }
    }
    //cdo llegue aca ya termino
    //ruidito
    //mensaje de quien gano
    //clean pantalla
    Color bg_color = {0x3C, 0xA6, 0x03};
    do_clearScreen(bg_color);
    */
    //prompt: want to play again? y/n => n vuelve al menu

}


static void paintBorders(uint16_t width, uint16_t height, Color color) {
    do_paintRect(0, 0, width, SIZE, white);             // top border 
    do_paintRect(0, 0, SIZE, height, white);            // left border
    do_paintRect(width-SIZE, 0, SIZE, height, white);   // right bor
    do_paintRect(0, height-SIZE, width, SIZE, white);   // bottom border
}

//hace la ventana en donde se juega al tron
void setScreen(uint64_t width, uint64_t height){
    Color bg_color = {0x3B, 0x0A, 0x00}; //azul
    do_clearScreen(bg_color); //pintar pantalla d azul
    paintBorders(width, height, tronColor3);
}


void setPlayers(uint16_t width, uint16_t height){

    player1.posX = (width/4)/8;
    player1.posY = (height/2)/8;
    player1.direction = 'd'; //hacemos un enum con UP, DOWN, LEFT, RIGHT
    player1.color = red;
    player1.state = 1;
    //do_paintRect(player1.posX, player1.posY, SIZE, SIZE, green);             
    

    player2.posX = (width - width/4)/8;
    player2.posY = (height/2)/8;
    player2.direction = 'L';
    player2.color = green;
    player2.state = 1;
    //do_paintRect(player2.posX, player2.posY, SIZE, SIZE, orange);            
}


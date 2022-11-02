#include <stdint.h>
#include <inout.h>
#include <syscalls.h>
#include <tron.h>
#include <colors.h>

#define SIZE 8
#define MAX_HEIGHT 1280
#define MAX_WIDTH 1024

typedef struct {
    uint64_t posX;
    uint64_t posY;
    uint8_t direction;
    uint8_t state;
    uint64_t color;    
} Player;

Player player1;
Player player2;



uint16_t board[MAX_WIDTH][MAX_HEIGHT];

static void getScreenData(uint16_t * data){ 
    return sys_getScreenData(data);
}

static void do_paintRect(uint64_t fromX, uint64_t fromY, uint16_t width, uint16_t height, uint64_t color){
    return sys_paint_rect(fromX, fromY, height, width, color);
}

static void do_beep(uint64_t frequency, uint64_t seconds){
    sys_beeper(frequency,seconds);
}
//ESTAMOS PONIENDO BOARD COMO B[Y][X] 
//BOARD NO TIENE LOS BORDES EN CUENTA 
static int isAlive(Player  p, uint16_t width, uint16_t height,uint16_t board[MAX_WIDTH][MAX_HEIGHT]) {
    if (p.posX < width && p.posX > 1 && p.posY < height && p.posY > 1 ){/*&& board[p.posY][p.posX]==0*/ //chequeo rango
        board[p.posX][p.posY]=1;
        return 1;
    }
    return 0;
}

static void updatePosition(uint64_t keypressed){
    switch (keypressed)
            {
            // caso default no existe ya q tiene q hacer algo siempre
            case 'w':
                if (player1.direction != 's' /* && player1.direction != 'w'*/){ //opposite 
                    player1.posY--;
                    player1.direction = 'w';
                    do_paintRect((player1.posX)*SIZE, (player1.posY)*SIZE, SIZE, SIZE, player1.color);
                }
                break;
            case 'a':
                if(player1.direction != 'd' /*&& player1.direction != 'a'*/){
                    player1.posX--;
                    player1.direction = 'a';
                    do_paintRect((player1.posX)*SIZE, (player1.posY)*SIZE, SIZE, SIZE, player1.color);
                }
                break;
            case 's':
                if(player1.direction != 'w' /*&& player1.direction != 's'*/){
                    player1.posY++;   
                    player1.direction = 's';
                    do_paintRect((player1.posX)*SIZE, (player1.posY)*SIZE, SIZE, SIZE, player1.color);
                }
                break;
            case 'd':
                if (player1.direction != 'a' /*&& player1.direction != 'd'*/){
                    player1.posX++;
                    player1.direction = 'd';
                    do_paintRect((player1.posX)*SIZE, (player1.posY)*SIZE, SIZE, SIZE, player1.color);
                }
                break;
            //Player 2
            case 'U': //up
                if (player2.direction != 'D' /*&& player2.direction != 'U'*/){ //opp opp?
                    player2.posY--;
                    player2.direction = 'U';
                    do_paintRect((player2.posX)*SIZE, (player2.posY)*SIZE, SIZE, SIZE, player2.color);
                }
                break;
            case 'L': //left
                if(player2.direction != 'R' /*&& player2.direction != 'L'*/){
                    player2.posX--;
                    player2.direction = 'L';
                    do_paintRect((player2.posX)*SIZE, (player2.posY)*SIZE, SIZE, SIZE, player2.color);
                }
                break;
            case 'D': //down
                if(player2.direction != 'U'/* &&  player2.direction != 'D'*/){
                    player2.posY++;   
                    player2.direction = 'D';
                    do_paintRect((player2.posX)*SIZE, (player2.posY)*SIZE, SIZE, SIZE, player2.color);
                }
                break;
            case 'R': //right
                if (player2.direction != 'L'/* && player2.direction != 'R'*/){
                    player2.posX++;
                    player2.direction = 'R';
                    do_paintRect((player2.posX)*SIZE, (player2.posY)*SIZE, SIZE, SIZE, player2.color);
                }
                break;
            }
}



//ejecuta el tron
void play_tron(){
//recordar d bloquear el resto tel teclado
    //seteamos pantalla -> players -> lectura para teclado (wasd player1 y flechas player2) -> 
    uint16_t screen[2] = {0}; //syscall que nos da los datos de la pantalla . por el momento 0 = width y 1 = height
    getScreenData(screen);
    setScreen(screen[0], screen[1]);
    setPlayers(screen[0],screen[1]);
    
    const uint16_t width = (screen[0]-16)/8 ;
    const uint16_t height = (screen[1]-16)/8;
    for(int i = 0; i < width;i++) for(int j = 0; j< height; j++)  board[i][j]=0; 
    //uint8_t alive1 = 1, alive2 = 1;
    uint64_t speed = 1;
    uint64_t ticks = sys_getTicks();
    uint64_t lastTicks = 0;
    char c;
    char t;
    while(player1.state && player2.state){  
        c = do_getChar();
        t = do_getChar(); 
        if (lastTicks != ticks && ticks % speed == 0){
            
            player1.state = !board[player1.posX][player1.posY] && isAlive(player1, width+1, height+1, board);
            player2.state = !board[player2.posX][player2.posY] && isAlive(player2, width+1, height+1, board);
            if (player1.state && player2.state){
                if(c != player1.direction && c != player2.direction)
                    updatePosition(c);
                if(t != player1.direction && t != player2.direction)
                    updatePosition(t);
                updatePosition(player1.direction);
                updatePosition(player2.direction);
            }
            
            
            
            //desps lo vemos pq usa el sys_read y eso tiene para esperar enter
            //haces el switch y player1.posY += SIZE ponele
            //board[player1.posY / SIZE][player1.posX / SIZE] = 1;
            //board[player2.posY / SIZE][player2.posX / SIZE] = 1; check q /size da bien!
            lastTicks = ticks;
        }
        ticks = sys_getTicks();
        
        //hacer syscall que espere n segundos o n ticks para ir imprimiendo
    }
    //prompt: want to play again? y/n => n vuelve al menu
    do_paintRect(0, 0, screen[0], screen[1]/SIZE*8, BLACK);
    do_changeFontSize(2);

    uint64_t freq = 400;
    uint64_t seconds = 1; // a oido
    do_beep(freq, seconds);
    char d;
   
    if(player1.state==1 || player2.state == 1){
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   THE WINNER IS: \n");
        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        do_changeFontSize(3);
        if(player1.state==1){
            do_printColor("PLAYER PINK!",PINK);
        }
        else if(player2.state==1){
            do_printColor("PLAYER GREEN!",GREEN);
        }
        do_changeFontSize(2);
    }
    else{
        printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  IT'S A TIE!\n");
    }
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tWant to play again? Press y/n \n");
    do_changeFontSize(1);
    while(d != 'y' && d != 'n'){
        d = do_getChar();
    }
    if(d == 'y'){
        play_tron();
        return;
    } else {
        do_clearScreen(BLACK);
    }
    
    return;
}


static void paintBorders(uint16_t width, uint16_t height, uint64_t color) {
    do_paintRect(0, 0, width, SIZE, DARKBLUE);             // top border 
    do_paintRect(0, 0, SIZE, height, DARKBLUE);            // left border
    do_paintRect(width-SIZE, 0, SIZE, height, DARKBLUE);   // right bor
    do_paintRect(0, height-SIZE, width, SIZE, DARKBLUE);   // bottom border
}

//hace la ventana en donde se juega al tron
void setScreen(uint16_t width, uint16_t height){
    
    do_clearScreen(SCREEN_TRON); //pintar pantalla d azul
    paintBorders(width, height, TRON_COLOR_3);
}


void setPlayers(uint16_t width, uint16_t height){

    player1.posX = (width/4)/SIZE;
    player1.posY = (height/2)/SIZE;
    player1.direction = 'd'; //hacemos un enum con UP, DOWN, LEFT, RIGHT
    player1.color = PINK;
    player1.state = 1;
    do_paintRect((player1.posX)*SIZE, (player1.posY)*SIZE, SIZE, SIZE, player1.color);          
    

    player2.posX = (width - width/4)/SIZE;
    player2.posY = (height/2)/SIZE;
    player2.direction = 'L';
    player2.color = GREEN;
    player2.state = 1;
    do_paintRect((player2.posX)*SIZE, (player2.posY)*SIZE, SIZE, SIZE, player2.color); 
}

//
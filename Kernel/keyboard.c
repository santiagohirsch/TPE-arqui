#include <keyboard.h>
#include <naiveGraphicsConsole.h>
#include <stdint.h>

#define MAX_LENGTH 20

static const uint8_t charHexMap[256] = {       
        0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    0x7F,
    '    ', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   'o',  'p',  '[',   ']',  '\n',   
        0,     'a',  's', 'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'',
    0,    0,  '\\',   'z',  'x',     'c', 'v', 'b',  'n',  'm',  ',',  '.',  '/',    0,  
    '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

static uint8_t buffer[MAX_LENGTH] = {0};
static uint8_t bufferLength = 0;
static uint8_t lastChar;

void keyboard_handler(){
    uint64_t i=tKey();
	uint64_t teclahex=i;
    if (teclahex < 0x53){
        ngc_printChar(charHexMap[teclahex]);  
        lastChar = charHexMap[teclahex];
        buffer[bufferLength++] = lastChar;
    }
}

char getLastChar(){
    return lastChar;
}


static void clearBuffer(){
    for ( int i = 0; i < MAX_LENGTH ; i++){
        buffer[i]=0;
    }
    bufferLength = 0;
}

char * getBuffer(){
    char * out = buffer;
    if (getLastChar() == '\n'){
        clearBuffer();
    }
    return out;
}


char read_keyboard(){
    uint64_t i=tKey();
	uint64_t teclahex=i;
    if (teclahex < 0x53){
        return charHexMap[teclahex];
    } else {
        return 'a';
    }
}

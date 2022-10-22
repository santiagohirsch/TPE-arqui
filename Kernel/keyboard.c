#include <keyboard.h>
#include <naiveGraphicsConsole.h>
#include <stdint.h>

static const uint8_t charHexMap[256] = {       
        0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    0x7F,
    '    ', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   'o',  'p',  '[',   ']',  '\n',   
        0,     'a',  's', 'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'',
    0,    0,  '\\',   'z',  'x',     'c', 'v', 'b',  'n',  'm',  ',',  '.',  '/',    0,  
    '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

void keyboard_handler(){
    uint64_t i=tKey();
	uint64_t teclahex=i;
    if (teclahex < 0x53){
        ngc_printChar(charHexMap[teclahex]);
    }
	
}
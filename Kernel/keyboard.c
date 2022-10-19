#include <keyboard.h>
#include <naiveConsole.h>
#include <stdint.h>

static const uint8_t charHexMap[256] = 
    {       
          0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    0x7F,
        '    ', 'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',   
         0,     'A',  'S', 'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',  '\'',
        0,    0,  '\\',   'Z',  'X',     'C', 'V', 'B',  'N',  'M',  ',',  '.',  '/',    0,  
        '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
    };

void keyboard_handler(){
    uint64_t i=tKey();
	uint64_t teclahex=i;
    if (teclahex < 0x53){
        ncPrintChar(charHexMap[teclahex]);
    }
	
}
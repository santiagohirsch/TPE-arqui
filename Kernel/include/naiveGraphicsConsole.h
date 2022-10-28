#ifndef NAIVE_GRAPHICS_CONSOLE_H
#define NAIVE_GRAPHICS_CONSOLE_H

#include <stdint.h>
#define CHAR_WIDTH 18 //18 para imprimir x2
#define CHAR_HEIGHT 16 //32 para imprimir x2

enum Dir {DOWN = 0, UP = 1};

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;


void ngc_printNewline(void);

void ngc_printChar(char c);

void ngc_print(char * s);

#endif
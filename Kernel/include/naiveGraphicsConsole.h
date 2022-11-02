#ifndef NAIVE_GRAPHICS_CONSOLE_H
#define NAIVE_GRAPHICS_CONSOLE_H

#include <stdint.h>
#define CHAR_WIDTH 9 
#define CHAR_HEIGHT 16 

enum Dir {DOWN = 0, UP = 1};

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;


void ngc_printNewline(void);

void ngc_printChar(char c);

void ngc_print(const char * s);

uint16_t ngc_getHeight(); 

uint16_t ngc_getWidth(); 

void ngc_printColor(const char * buffer, uint64_t color);

void changeFontSize(uint64_t newlevel);

void ngc_paint_screen(uint64_t bg_color);

void ngc_print_pixels(uint64_t fromX, uint64_t fromY, uint16_t width, uint16_t height, uint64_t color);

#endif
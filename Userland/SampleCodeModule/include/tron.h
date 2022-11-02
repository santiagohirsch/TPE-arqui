#ifndef TRON_H
#define TRON_H
#include <stdint.h>

#define CYAN        0xEEEE00
#define DARKERCYAN  0xAAAA00
#define WHITE       0xFFFFFF
#define BLACK       0x000000
#define GREY        0x7F7F7F
#define BLUE        0xFF0000
#define GREEN       0x00FF00
#define RED         0x0000FF
#define YELLOW      0x00FFFF
#define ORANGE      0x00A5FF
#define PINK        0xCBC0FF

#define SCREEN_TRON  0x3B0A00
#define TRON_COLOR_1 0x403C19
#define TRON_COLOR_2 0x02592E
#define TRON_COLOR_3 0x014021
#define TRON_COLOR_4 0x4169D9
#define TRON_COLOR_5 0x1F2BA6

void play_tron();
void setPlayers(uint16_t width, uint16_t height);
void setScreen(uint16_t width,uint16_t height);

#endif
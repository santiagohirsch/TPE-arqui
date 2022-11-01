#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <stdint.h>
#include <colors.h>
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define KDBIN 3


void sys_write(uint64_t fd, const char * buffer, uint64_t count);

void sys_read(uint64_t fd, const char * buffer, uint64_t count);

uint64_t sys_time();

uint8_t sys_inforeg(uint64_t regVec[17]);

void sys_changeFontSize();

void sys_printColor(const char * buffer, Color color);

void sys_getScreenData(uint16_t * screen);

void sys_paint_rect(uint16_t fromX, uint16_t fromY, uint16_t width, uint16_t height, Color color);

uint64_t sys_getTicks();
 
void sys_clear_screen(Color color);

#endif
#ifndef INOUT_H
#define INOUT_H

#include <stdint.h>
#include <colors.h>

void bufferAction(char * buffer, uint64_t length);

void printf(const char *format, ...);

void scanf(char* format, ...);

void do_printColor(const char * buffer, Color color);

void do_getTime(char * buffer);

void do_clearScreen(Color color);

void do_divisionByZero();

void do_invalidOpCode();

void do_printInfoReg();

void do_changeFontSize(uint64_t level);

char do_getChar();

void do_putChar(char c);


#endif
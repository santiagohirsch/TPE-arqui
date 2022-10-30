#ifndef LIBVID_H
#define LIBVID_H

#include <stdint.h>
#include <colors.h>

void printf(const char *format, ...);

void scanf(char* format, ...);

void getTime(char * buffer);

void do_clearScreen(Color color);

void do_divisionByZero();

void do_invalidOpCode();

void printInfoReg();

void do_changeFontSize(uint64_t level);

#endif
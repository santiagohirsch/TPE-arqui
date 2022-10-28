#ifndef LIBVID_H
#define LIBVID_H

#include <stdint.h>


void printf(const char *format, ...);

void scanf(char* format, ...);

void getTime(char * buffer);

void do_divisionByZero();

void do_invalidOpCode();

//uint64_t getScreenshot();

#endif
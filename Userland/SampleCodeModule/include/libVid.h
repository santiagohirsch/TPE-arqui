#ifndef LIBVID_H
#define LIBVID_H

#include <stdint.h>
#include <colors.h>

void printf(const char *format, ...);

void scanf(char* buffer, int length);

void getTime(char * buffer);

void do_clearScreen(Color color);

//uint64_t getScreenshot();

#endif
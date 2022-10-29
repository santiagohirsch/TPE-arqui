#ifndef LIBVID_H
#define LIBVID_H

#include <stdint.h>

void printf(const char *format, ...);

void scanf(char* format, ...);

void getTime(char * buffer);

void printInfoReg();

void do_changeFontSize(uint64_t level);

#endif
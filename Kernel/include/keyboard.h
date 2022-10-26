#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdint.h>

extern uint64_t getKey();
extern uint64_t tKey();

void keyboard_handler(uint64_t teclahex);
char getLastChar();
char * getBuffer();
uint64_t getBufferLength();

#endif

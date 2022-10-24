#ifndef STRING_H_
#define STRING_H_

#include <stdint.h>

void _strcpy(char * dest, char * src, int n);

uint64_t _strlen(const char * str);

int _strcmp(char *str1, char *str2);

uint64_t getFormat(uint64_t n);

uint64_t itoa(uint64_t number, char* s);

#endif
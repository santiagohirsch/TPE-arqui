#ifndef STRING_H_
#define STRING_H_

#include <stdint.h>

#define MAX_INT 18

void _strcpy(char * dest, char * src, int n);

uint64_t _strlen(const char  *str);

int _strcmp(char *str1, char *str2);

uint64_t itoa(uint64_t number, char* s);

int strtoi(char * buffer, int * i);

int hexStrToInt(char* s, uint8_t **result);

uint64_t atoi(char S[]);

#endif
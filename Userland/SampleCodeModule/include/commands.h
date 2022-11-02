#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_PARAMETERS 5
#define LENGTH_PARAMETERS 256
#define BUFFER_LENGTH 256
#define COMMANDS_LENGTH 9
#define REGISTERS 17

void help(int argc, char params[MAX_PARAMETERS][LENGTH_PARAMETERS]);

void invalidOPCode(int argc, char  params[][LENGTH_PARAMETERS]);

void divideByZero(int argc, char  params[][LENGTH_PARAMETERS]);

void inforeg(int argc, char params[][LENGTH_PARAMETERS]);

void printMem(int argc, char params[][LENGTH_PARAMETERS]);

void time(int argc, char params[][LENGTH_PARAMETERS]);

void changeFontSize(int argc, char params[][LENGTH_PARAMETERS]);

void tron(int argc, char params[][LENGTH_PARAMETERS]);

void clearScreen(int argc, char params[][LENGTH_PARAMETERS]);

#endif
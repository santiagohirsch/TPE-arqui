#include <syscalls.h>
#include <libVid.h>
#include <stdint.h>
#include <string.h>


void print(const char *buffer){
    //lamo al syswrite 1=stdout
    sys_write(STDOUT, buffer, _strlen(buffer));
}

void scan(char * buffer, uint64_t length){
	sys_read(KDBIN, buffer, length);
}
/*
void scanf(char* buffer, int length){

}


void print(const char *buffer, int count, Color color){

}

void putchar(char c){
    
}

char getChar(){

}
*/
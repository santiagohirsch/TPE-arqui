#include <syscalls.h>
#include <libVid.h>
#include <stdint.h>
#include <stringUtil.h>


void print(const char *buffer){
    //lamo al syswrite 1=stdout
    sys_write(STDOUT, buffer, _strlen(buffer));
}

void scan(char * buffer, uint64_t length){
	sys_read(KDBIN, buffer, length);
}

void getTime(char * buffer){
    char* p = buffer;
	uint64_t time = sys_time();
	itoa(getFormat(time & 0xFF), p);
	p[2] = ':';
	itoa(getFormat((time >> 8) & 0xFF), &p[3]);
	p[5] = ':';
	itoa(getFormat((time >> 16) & 0xFF), &p[6]);
    p[8] = 0;

}
/*
void scanf(char* buffer, int length){

}



void putchar(char c){
    
}

char getChar(){

}
*/
#include <syscalls.h>
#include <libVid.h>
#include <stdint.h>

static int _strlen(const char * str){
	int ans = 0;
	for (int i = 0; str[i] != 0; i++)
	{
		ans++;
	}
	return ans;
}

void print(const char *buffer){
    //lamo al syswrite 1=stdout
    sys_write(STDOUT, buffer, _strlen(buffer));
}

void scan(char * buffer, uint64_t length){
	sys_read(STDIN, buffer, length);
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
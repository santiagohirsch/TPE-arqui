#include <syscalls.h>
#include <libVid.h>
#include <stdint.h>
#include <stringUtil.h>
#include <stdarg.h>

#define MAX_INT 18

void putString(const char *buffer){
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
uint64_t getScreenshot(){
	return sys_screenshot();
}
*/
void scanf(char* buffer, int length){

}

void putChar(char c) {
	sys_write(STDOUT, &c, 1);
}

void putBase(int num, int base){

	int i = 12;
	int j = 0;

	char hex[13];

	putString("0x");
	do{
		hex[i] = "0123456789ABCDEF"[num % base];
		i--;
		num = num/base;
	}while( num > 0 );

	while( ++i < 13){
		hex[j++] = hex[i];
	}

	hex[j] = 0;

	putString(hex);
}


void putInt(int num){
	char strnum[MAX_INT];
	itoa(num,strnum);
	putString(strnum+1);
}


// para una cantidad de argumentos variable usamos la lib stdarg.h
void printf (const char *format, ...)
{
	// point p_arg to first argument
   	va_list p_arg;
   	va_start(p_arg, format); // -> hace apuntar p_arg al primer argumento (no format)


    while (*format != '\0') {
		// loop mientras se impriman char normales
        if (*format != '%') {
            putChar(*format);
            format++;
        } 

		// si hay un %, me fijo el siguiente para imprimir especial
		else {

        format++;

        switch (*format) {
            case 'd':
			case 'D':
                putInt(va_arg(p_arg, int));
                break;
            case 'c':
			case 'C':
                putChar(va_arg(p_arg, int));  // char promociona a int
                break;
            case 's':
			case 'S':
                putString(va_arg(p_arg, char *));
                break;
			case 'x':
            case 'X':
                putBase(va_arg(p_arg, int), 16);
        }

        format++;
		}
    }
	
    va_end(p_arg);
}

char getChar(){

}

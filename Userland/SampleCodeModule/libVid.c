#include <syscalls.h>
#include <libVid.h>
#include <stdint.h>
#include <stringUtil.h>
#include <stdarg.h>

#define MAX_INT 18
#define MAX_BUFFER 255

void do_changeFontSize(uint64_t level){
	sys_changeFontSize(level);
}

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


uint64_t strtoi(char * buffer, int * i){
	char strnum[MAX_INT];
	int numsize=0;
	while(buffer[*i] != ' ' && buffer[*i] != '\n' && buffer[*i] != '\0'){
		strnum[numsize++] = buffer[*i];
		(*i)++;
	}
	uint64_t out = atoi(strnum);
	return out;
}

char * getRestOfString(char string[]){
	return string;
}

int getChar(){
	char out;
	sys_read(KDBIN, &out, 1);
	return out;
}

//en  fmt nos pasa formato ... nos van a mandar las variables a dnd asignar
void scanf(char * format,...){
	char * str = {0};
	int len = 0;
	//lectura del buffer
	char buffer[MAX_BUFFER];
	sys_read(KDBIN, buffer, MAX_BUFFER); //agarra de mas, habria q hacer q lea hasta q termine ??
	//parseamos para poder asignarselo a cada param
	//primer caracter si o si %
	if(*format != '%'){
		printf("uso incorrecto de scanf\n");
		return;
	}

	va_list vl;
	va_start(vl, format);
	int buffIdx = 0;
	while (*format != '\0'){
		if(*format != '%'){ //letra o espacio
			if ( *format != ' '){
				printf("uso incorrecto de scanf\n");
				return;
			}
			else{
				*format++; //deberia tmbn indicar el inicio d un nuevo param
			}
		}
		else{
			*format++;
			switch (*format) { //caso en el q estoy en una letra 
            	case 'd':
				case 'D':
					*(int *)va_arg( vl, int* ) = strtoi(buffer, &buffIdx);	
					//sys_read(d terminal)
					//asignacion a la direccion d memoria pasada  hola que tal
                	//putInt(va_arg(p_arg, int));
                	break;
            	case 'c':
				case 'C':
					*(char *)va_arg( vl, char* ) = buffer[buffIdx++];
                	//putChar(va_arg(p_arg, int));  // char promociona a int
                	break;
            	case 's':
				case 'S':
					while(buffer[buffIdx]!= '\0'){
						str[len++]= buffer[buffIdx++];
					}
					str[len] = buffer[buffIdx];
					*(char *)va_arg( vl, char* ) = str;
                	//putString(va_arg(p_arg, char *));
                	break;
				case ' ':
					printf("uso incorrecto de scanf (Fijese de no dejar espacios luego del porcentaje)\n");
					return;
			}
			
			*format++;	
		}
	}
	va_end(vl);
}

void printInfoReg(){
	uint64_t reg[17];
	uint8_t huboScreenshot = sys_inforeg(reg);
	if (huboScreenshot){
		//rip, rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15 
		printf("rip = %x\n", reg[0]);
		printf("rax = %x\n", reg[1]);
		printf("rbx = %x\n", reg[2]);
		printf("rcx = %x\n", reg[3]);
		printf("rdx = %x\n", reg[4]);
		printf("rsi = %x\n", reg[5]);
		printf("rdi = %x\n", reg[6]);
		printf("rbp = %x\n", reg[7]);
		printf("rsp = %x\n", reg[8]);
		printf("r8  = %x\n", reg[9]);
		printf("r9  = %x\n", reg[10]);
		printf("r10 = %x\n", reg[11]);
		printf("r11 = %x\n", reg[12]);
		printf("r12 = %x\n", reg[13]);
		printf("r13 = %x\n", reg[14]);
		printf("r14 = %x\n", reg[15]);
		printf("r15 = %x\n", reg[16]);
	} else {
		printf("No se ha hecho un screenshot, presione la tecla CTRL e intente de nuevo.\n");
	}
}
/*
void _scanf(char* format , ...){
	va_list vl;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0}, tmp[20], c;
    char *out_loc;
    while(c != '') 
    {
        if (fread(&c, 1, 1, stdin)) 
        {
 	       buff[i] = c;
 	       i++;
 	    }
 	}
 	va_start( vl, format );
 	i = 0;
 	while (format && format[i])
 	{
 	    if (format[i] == '%') 
 	    {
 	       i++;
 	       switch (format[i]) 
 	       {
 	           case 'c': 
 	           {
	 	           *(char *)va_arg( vl, char* ) = buff[j];
	 	           j++;
	 	           ret ++;
	 	           break;
 	           }
 	           case 'd': 
 	           {
	 	           *(int *)va_arg( vl, int* ) = _strtol(&buff[j], &out_loc, 10);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
 	            case 'x': 
 	            {
	 	           *(int *)va_arg( vl, int* ) = _strtol(&buff[j], &out_loc, 16);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
 	        }
 	    } 
 	    else 
 	    {
 	        buff[j] =format[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}*/

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
	putString(strnum);
}

// para una cantidad de argumentos variable usamos la lib stdarg.h
void printf (const char *format, ...) {
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

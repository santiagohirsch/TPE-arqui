#include <inout.h>
#include <commands.h>
#include <stdint.h>
#include <stringUtil.h>
#include <tron.h>
#include <syscalls.h>
#include <colors.h>
//le sacamos const por el momento por el warning
static char* commands[] = {"help", "invalidopcode", "dividebyzero", "inforeg", "printmem", "time", "changefontsize", "tron", "clear"};



/* COMMANDS */

static void (*commands_functions[])(int argc, char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS]) = {
	help, 
	invalidOPCode, 
	divideByZero, 
	inforeg, 
	printMem, 
	time, 
	changeFontSize, 
	tron, 
	clearScreen
};

static int findIdxCommand(char *buff);

static int parseBuffer(char command[BUFFER_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[BUFFER_LENGTH]);


int 
main() {
	do_printColor("WELCOME! Type \"HELP\" for command list\n", WHITE);
	while(1){
			printf("$>");
			char buff_command[BUFFER_LENGTH] = {0};
			// command
			char command[BUFFER_LENGTH] = {0};
			// parametros enviados junto al comando
			char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS] = {{0}};

			bufferAction(buff_command, BUFFER_LENGTH); //sys_read de todo
			int size = parseBuffer(command, parameters, buff_command);
			int idx = findIdxCommand(command);
			if(idx >= 0 ){
				commands_functions[idx](size,parameters);
			}
			else if (idx == -1){
				do_printColor("Command not found: try again\n", RED);
			}
	}
	return 0;
}


static int parseBuffer(char command[BUFFER_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[BUFFER_LENGTH]) {
	int i=0, j;
	//i = bufferidx, commandlength
	//k = paramsidx
	while(i < BUFFER_LENGTH && readbuf[i] == ' '){
		i++;
	}
	for(j = 0; i < BUFFER_LENGTH && readbuf[i] != ' ' && readbuf[i] != '\0'; i++){
			command[j++] = readbuf[i];
	}

	int k=0;
	command[j] = 0;
	while(i < BUFFER_LENGTH && readbuf[i] == ' '){
		i++;
	}
	if (readbuf[i]=='\0'){
		return k;
	}

	k=1;
	for(j=0; i<BUFFER_LENGTH;) {
		if(k>=MAX_PARAMETERS || j >= LENGTH_PARAMETERS)
			return -1;
		//casos: a: estoy en un espacio => aumento k pues termino un param
		//		 b: estoy en una caracter => o es el ultimo o no
		// => si es el ultimo ++k y si no sigo leyendo
		if(readbuf[i]!=' ') { //estoy en un caracter y hay un siguiente
			parameters[k-1][j++] = readbuf[i++];
		}
		else {
			parameters[k-1][j] = 0;
			j=0;
			while(i<BUFFER_LENGTH && readbuf[i]==' '){
				i++;
			}
			if (readbuf[i]=='\0'){
				return k;
			}
			k++;
		}
	}
	return k;
}

static int findIdxCommand(char *buff){

	if (_strlen(buff) == 0) { //Me pasan un enter suelto
		return -2;            //Para diferenciar de command not found
	}
	
	for (int i = 0; i < COMMANDS_LENGTH ; i++){
		if (_strcmp(buff, commands[i]) == 0){
			return i;
		}
	}
	return -1; //command not found
}

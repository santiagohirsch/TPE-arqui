#include <libVid.h>
#include <stdint.h>

#define MAX_PARAMETERS 10
#define LENGTH_PARAMETERS 20
#define BUFFER_LENGTH 20
#define COMMANDS_LENGTH 9

/* COMMANDS */
static void help(){
	
}

static void screenshot(){
	
}

static void invalidOPCode(){

}

static void divideByZero(){ 

}

static void inforeg(){
	
}

static void printMem(uint64_t memDirec){
	
}


static void time(){
	
}


static void changeFontSize(char setting){
	
}

static void tron(){
	
}


//iria aca ?
static int strcmp(char *str1, char *str2){
	while( ( *str1 != '\0' && *str2 != '\0' ) && *str1 == *str2 )
    {
        str1++;
        str2++;
    }

    if(*str1 == *str2)
    {
        return 0; // strings are identical
    }

    else
    {
        return *str1 - *str2;
    }
}
static const char* commands[] = {"help", "screenshot", "invalidopcode", "dividebyzero", "inforeg", "printmem", "time", "changefontsize", "tron"};
static void (*commands_functions[])(char parameters[COMMANDS_LENGTH][LENGTH_PARAMETERS]) = {help, screenshot, invalidOPCode, divideByZero, inforeg, printMem, time, changeFontSize, tron};



static int findIdxCommand(char *buff){
	for (int i = 0; i < COMMANDS_LENGTH ; i++){
		if ( strcmp(buff,commands[i]) == 0 ){
			return i;
		}
	}
	return -1; //command not found
}

int main() {

	//Por ahora nos manejamos con syscalls pero habria que implementar la lib de C
	//Es decir printf, scanf, etc

	print("Welcome: type 'help' for options");
	print("\n");
	print("$>");
	while(1){
		// usuario escribe comando -> paso a idx: lo busco en mi arrays cual es y ejecuto
		
		//buffer para ver q comando me manda
		char buff_command[BUFFER_LENGTH] = {0};
		scan(buff_command, BUFFER_LENGTH);  

		// paso a idx (fun aux)
		int idx = findIdxCommand(buff_command);
		if ( idx != -1){
			//busco en mi array
			// LE PASO PARAMETROS: VER COMO RECIBO
			print("Lo encontro!");
			//char parameters[COMMANDS_LENGTH][LENGTH_PARAMETERS];
			//commands_functions[idx](parameters);
		}
		else{
			print("Command not found: try again");
		}
		  
	}
	return 0;
	
}
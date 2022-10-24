#include <libVid.h>
#include <stdint.h>
#include <string.h>

#define MAX_PARAMETERS 10
#define LENGTH_PARAMETERS 20
#define BUFFER_LENGTH 20
#define COMMANDS_LENGTH 9

/* COMMANDS */
static void help(){
	/*if(parameters[0][0]!=0){
		print("Try help without parameters\n");
		return;
	}*/
	
	const char* helpstring = 
	"HELP                 Provides help information for commands.\n"
	"SCREENSHOT           Register's screenshot.\n"
	"INVALIDOPCODE        Command to verify the operation of the exception routine \"Invalid Opcode\"\n"
	"DIVIDEBYZERO         Command to verify the operation of the exception routine \"Divide by zero\"\n"
	"INFOREG              Prints on screen the value of all registers.\n"
	"PRINTMEM             Receives as argument a pointer and performs a memory dump of 32 bytes from the\n"
	".                    Address received as an argument.\n"
	"TIME                 Command to display the system day and time.\n"
	"CHANGEFONTSIZE       Changes font size.\n"
	"TRON                 Get ready to play Tron!.\n";
	print(helpstring);
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


static const char* commands[] = {"help", "screenshot", "invalidopcode", "dividebyzero", "inforeg", "printmem", "time", "changefontsize", "tron"};
static void (*commands_functions[])(char parameters[COMMANDS_LENGTH][LENGTH_PARAMETERS]) = {help, screenshot, invalidOPCode, divideByZero, inforeg, printMem, time, changeFontSize, tron};

static void printWelcomeMessage() {
	print("WELCOME! Type \"HELP\" for list\n");
}

static int findIdxCommand(char *buff){

	if (_strlen(buff) == 0) {
		return 1;
	}
	
	for (int i = 0; i < COMMANDS_LENGTH ; i++){
		if (_strcmp(buff, commands[i]) == 0){
			return i;
		}
	}
	
	
	print("Command not found: try again\n");
	return -1; //command not found
}

int main() {

	//Por ahora nos manejamos con syscalls pero habria que implementar la lib de C
	//Es decir printf, scanf, etc

	printWelcomeMessage();

	while(1){
		print("$>");
		//recepcion de parametros ???????
		//buffer para ver q comando me manda
		char buff_command[BUFFER_LENGTH] = {0};
		
		scan(buff_command, BUFFER_LENGTH);  
	
		// paso a idx (fun aux)
		int idx = findIdxCommand(buff_command);
		if (idx==0){
			help();
		}
		
		  
	}
	return 0;
}
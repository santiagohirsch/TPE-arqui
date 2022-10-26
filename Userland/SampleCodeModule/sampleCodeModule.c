#include <libVid.h>
#include <stdint.h>
#include <stringUtil.h>

#define MAX_PARAMETERS 5
#define LENGTH_PARAMETERS 20
#define BUFFER_LENGTH 20
#define COMMANDS_LENGTH 9
#define REGISTERS 17


static const char* commands[] = {"help", "screenshot", "invalidopcode", "dividebyzero", "inforeg", "printmem", "time", "changefontsize", "tron"};

static const char* registerNames[REGISTERS] = {
    "rip", "rax", "rbx", "rxc", "rdx", "rsi", "rdi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
};

/* COMMANDS */
static void help(int argc, char params[MAX_PARAMETERS][LENGTH_PARAMETERS]);

static void screenshot(int argc, char params[][LENGTH_PARAMETERS]);

static void invalidOPCode(int argc, char  params[][LENGTH_PARAMETERS]);

static void divideByZero(int argc, char params[][LENGTH_PARAMETERS]);

static void inforeg(int argc, char params[][LENGTH_PARAMETERS]);

static void printMem(int argc, char params[][LENGTH_PARAMETERS]);

static void time(int argc, char params[][LENGTH_PARAMETERS]);

static void changeFontSize(int argc, char params[][LENGTH_PARAMETERS]);

static void tron(int argc, char params[][LENGTH_PARAMETERS]);

static void (*commands_functions[])(int argc, char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS]) = {help, screenshot, invalidOPCode, divideByZero, inforeg, printMem, time, changeFontSize, tron};

static int findIdxCommand(char *buff);
static int parseBuffer(char command[BUFFER_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[BUFFER_LENGTH]);

int 
main() {
	//Por ahora nos manejamos con syscalls pero habria que implementar la lib de C
	//Es decir printf, scanf, etc
	printf("WELCOME! Type \"HELP\" for list\n");

	while(1){
		printf("$>");
		// buffer para ver q comando me manda
		char buff_command[BUFFER_LENGTH] = {0};
		// command
		char command[COMMANDS_LENGTH] = {0};
		// parametros enviados junto al comando
		char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS] = {{0}};
		scan(buff_command, BUFFER_LENGTH); //sys_read de todo
	
		int size = parseBuffer(command, parameters, buff_command);

		int idx = findIdxCommand(command);

		if(idx >= 0 ){
			commands_functions[idx](size,parameters);
		}
		else if (idx == -1){
			printf("Command not found: try again\n");
		}
	}
	return 0;
}


static int parseBuffer(char command[BUFFER_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[BUFFER_LENGTH]) {
	int i=0, j;
	//i = bufferidx, commandlength
	//k = paramsidx
	while(i<BUFFER_LENGTH && readbuf[i]==' '){
		i++;
	}
	for( j=0; i<BUFFER_LENGTH && readbuf[i]!=' ' && readbuf[i] != '\0'; i++){
			command[j++] = readbuf[i];
	}

	int k=0;
	command[j] = 0;
	while(i<BUFFER_LENGTH && readbuf[i]==' '){
		i++;
	}
	if (readbuf[i]=='\0'){
		return k;
	}

	k=1;
	for(j=0; i<BUFFER_LENGTH;) {
		if(k>=MAX_PARAMETERS || j>=LENGTH_PARAMETERS)
			return;
		//casos: a: estoy en un espacio => aumento k pues termino un param
		//		 b: estoy en una caracter => o es el ultimo o no
		// => si es el ultimo ++k y si no sigo leyendo
		if(readbuf[i]!=' ') { //estoy en un caracter y hay un siguiente
			parameters[k-1][j++] = readbuf[i++];
		}
		else{
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
// no params
static void help(int argc, char params[MAX_PARAMETERS][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try help without parameters\n");
		return;
	}
	
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
	printf(helpstring);
}

// 1 param: register
static void screenshot(int argc, char params[][LENGTH_PARAMETERS]){
	if (argc!=0){
		printf("Try screenshot without parameters\n");
		return;
	}
	printf("screenshot\n");
}

//no params
static void invalidOPCode(int argc, char  params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try invalidOpCode without parameters\n");
		return;
	}
	printf("invalidOPcode\n");
}

//no params
static void divideByZero(int argc, char params[][LENGTH_PARAMETERS]){ 
	if(argc!=0){
		printf("Try dividebyzero without parameters\n");
		return;
	}
	printf("divide by zero\n");
}

//no params
static void inforeg(int argc, char params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try inforeg without parameters\n");
		return;
	}
	printf("info reg\n");
}

//1 param: memDirec
static void printMem(int argc, char params[][LENGTH_PARAMETERS]){
	
	if(argc != 1){
		printf("Try printMem with %d parameter (memDir)\n", 1);
		printf("Try printMem with %X parameter (memDir)\n", 16);
		return;
	}
	for (int i= 0; i < REGISTERS;i++){
		if( _strcmp(params[0], registerNames[i]) == 0){
			printf("parametro correct: ");
			printf(params[0]);
			return;
		}
	}
	//si llegue aca no hubo param
	printf("param incorrecto pete\n");
	printf(params[0]);
	printf("\n");
	printf("fin de params\n");
}


//1 param: setting
static void changeFontSize(int argc, char params[][LENGTH_PARAMETERS]){
	/*for(int i=0;i<argc;i++)
		print("a");*/
	if(argc != 1){
		printf("Try change font size with 1 parameter (setting)\n");
		return;
	}
	printf("change font size\n");
}

//no params
static void time(int argc, char params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try time without parameters\n");
		return;
	}
	printf("time\n");
	char timeBuffer[9];
	getTime(timeBuffer);
	printf(timeBuffer);
	printf("\n");
}

//no params
static void tron(int argc, char params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try tron without parameters\n");
		return;
	}
	printf("tron\n");
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
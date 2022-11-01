#include <libVid.h>
#include <stdint.h>
#include <stringUtil.h>
#include <colors.h>
#include <tron.h>

#define MAX_PARAMETERS 5
#define LENGTH_PARAMETERS 256
#define BUFFER_LENGTH 256
#define COMMANDS_LENGTH 9
#define REGISTERS 17

//le sacamos const por el momento por el warning
static char* commands[] = {"help", "invalidopcode", "dividebyzero", "inforeg", "printmem", "time", "changefontsize", "tron", "clear"};

/*static  char* registerNames[REGISTERS] = {
    "rip", "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
};*/


/* COMMANDS */
static void help(int argc, char params[MAX_PARAMETERS][LENGTH_PARAMETERS]);

static void invalidOPCode(int argc, char  params[][LENGTH_PARAMETERS]);

static void divideByZero(int argc, char  params[][LENGTH_PARAMETERS]);

static void inforeg(int argc, char params[][LENGTH_PARAMETERS]);

static void printMem(int argc, char params[][LENGTH_PARAMETERS]);

static void time(int argc, char params[][LENGTH_PARAMETERS]);

static void changeFontSize(int argc, char params[][LENGTH_PARAMETERS]);

static void tron(int argc, char params[][LENGTH_PARAMETERS]);

static void clearScreen(int argc, char params[][LENGTH_PARAMETERS]);

static void (*commands_functions[])(int argc, char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS]) = {
	help, 
	invalidOPCode, 
	divideByZero, 
	inforeg, 
	printMem, 
	time, 
	changeFontSize, 
	tron, 
	clearScreen};

static int findIdxCommand(char *buff);

static int parseBuffer(char command[BUFFER_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[BUFFER_LENGTH]);

int 
main() {
	//Por ahora nos manejamos con syscalls pero habria que implementar la lib de C
	//Es decir printf, scanf, etc
	
	printf("WELCOME! Type \"HELP\" for command list\n");
	while(1){
			printf("$>");
			char buff_command[BUFFER_LENGTH] = {0};
			// command
			char command[BUFFER_LENGTH] = {0};
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
// no params
static void help(int argc, char params[MAX_PARAMETERS][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try help without parameters\n");
		return;
	}
	
	const char* helpstring = 
	"HELP                 Provides help information for commands.\n"
	"INVALIDOPCODE        Command to verify the operation of the exception routine \"Invalid Opcode\"\n"
	"DIVIDEBYZERO         Command to verify the operation of the exception routine \"Divide by zero\"\n"
	"INFOREG              Prints on screen the value of all registers.\n"
	"PRINTMEM             Receives as argument a pointer and performs a memory dump of 32 bytes from the\n"
	".                    Address received as an argument.\n"
	"TIME                 Command to display the system day and time.\n"
	"CHANGEFONTSIZE       Changes font size: insert 1 2 3 for the desired level.\n"
	"TRON                 Get ready to play Tron!.\n";
	printf(helpstring);
}

//no params
static void divideByZero(int argc, char  params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try divideByZero without parameters\n");
		return;
	}
	printf("Divide by Zero\n");
	do_divisionByZero();
}

//no params
static void invalidOPCode(int argc, char  params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try invalidOpCode without parameters\n");
		return;
	}
	printf("Invalid Op Code\n");
	do_invalidOpCode();
}


//no params
static void inforeg(int argc, char params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("Try inforeg without parameters\n");
		return;
	}
	printf("info reg\n");
	printInfoReg();
}

static char byteHexToChar(uint8_t value) {
	return value >= 10 ? (value - 10 + 'A') : (value + '0');
}

//1 param: memDirec
static void printMem(int argc, char params[][LENGTH_PARAMETERS]){
	
	if(argc != 1){
		printf("Try printMem with one parameter (memDir)\n");
		return;
	}

	if (!checkMem(params[0])){
		printf("Parameter is not a valid memory address. It must be a hex number started with 0x\n");
		return;
	}

	// we store in mem the pointer to the first memory we want to print
	uint8_t * mem =0;
	*mem = hexStrToInt(params[0]);
	// we print the 32 bytes that follow *mem
	for (int i = 0; i < 32; i++){
		if (i == 16) {
			printf("\n");
		}
		char  buffer[6] = "0x00 ";
		buffer[2] = byteHexToChar(mem[i] >> 4);	// first hex value
		buffer[3] = byteHexToChar(mem[i] & 0x0F);	
		Color cyan = {0xFF, 0xFF, 0x00};
		Color yellow = {0x00, 0xFF, 0xFF};
		printColor("0x", cyan);
		printColor(buffer + 2, yellow);
	}
	printf("\n");
}

//1 param: setting
static void changeFontSize(int argc, char params[][LENGTH_PARAMETERS]){
	int everythingOk = 1;
	if(argc != 1){
		printf("Try change font size with 1 parameter (setting)\n");
		return;
	}
	if (_strlen(params[0]) > 1){
		printf("Try with 1, 2 or 3\n");
		return;
	}
	if (params[0][0] == '1' || params[0][0] == '2' || params[0][0] == '3' ){
		if (params[0][0] == '3'){
			everythingOk = 0;
			printf("Warning, font size 3 is way too big!\n");
			printf("If you still want to change the font size type 'y', otherwise type 'n'\n");
			char ans ;
			while(ans != 'y' && ans != 'n')
				ans = getChar();
			if(ans == 'y')
				everythingOk = 1;
		}
		if (everythingOk) do_changeFontSize(params[0][0]-'0');
		
	}
	else{
		printf("Invalid parameter, try with 1, 2 or 3\n");
	}
	return;
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
	play_tron();
}


static void clearScreen(int argc, char params[][LENGTH_PARAMETERS]) {
	Color color = {0x00, 0x00, 0x00};
	do_clearScreen(color);
	return;
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

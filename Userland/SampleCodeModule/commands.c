#include <stdint.h>
#include <commands.h>
#include <tron.h>
#include <colors.h>
#include <inout.h>
#include <stringUtil.h>

#define isHexa(a) ( (((a) >= '0' && (a) <= '9') || ((a) >= 'a' && (a) <= 'f') || ((a) >= 'A' && (a) <= 'F')) ? 1 : 0 )

// no params
void help(int argc, char params[MAX_PARAMETERS][LENGTH_PARAMETERS]){
	if(argc!=0){
		do_printColor("\tayayay be more careful... ", RED);
		printf("help does not take any parameters\n");
	}
	// se corre el comando de todas formas
	
	const char* helpstring = 
	"HELP                 Provides help information for commands.\n"
    "DIVIDEBYZERO         Command to verify the operation of the exception routine \"Divide by zero\"\n"
	"INVALIDOPCODE        Command to verify the operation of the exception routine \"Invalid Opcode\"\n"
	"INFOREG              Prints on screen the value of all registers.\n"
	"PRINTMEM             Receives as argument a pointer and performs a memory dump of 32 bytes from the\n"
	"                     Address received as an argument.\n"
	"TIME                 Command to display the system day and time.\n"
	"CHANGEFONTSIZE       Changes font size: insert 1 2 3 for the desired level.\n"
	"TRON                 Get ready to play Tron!.\n"
	"CLEAR                Clear screen\n";
	printf(helpstring);
}

//no params
void divideByZero(int argc, char  params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		do_printColor("\tIf you are already going to divide by zero then try to not commit another error... ", RED);
		printf("'divideByZero' does not take any parameters\n");
		return;
	}
	printf("Divide by Zero\n");
	do_divisionByZero();
}

//no params
void invalidOPCode(int argc, char  params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("\t'invalidopcode' does not take any parameters\n");
		return;
	}
	do_invalidOpCode();
}


//no params
void inforeg(int argc, char params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("\try inforeg without parameters\n");
		return;
	}
	do_printInfoReg();
	return;
}

char byteHexToChar(uint8_t value) {
	return value >= 10 ? (value - 10 + 'A') : (value + '0');
}
 
static uint64_t checkMem(char mem[], uint64_t * len){
    *len = _strlen(mem);
    //0x........ -> if it matches ^0x[a-fA-F0-9]{16}
    if (*len < 2 || mem[0] != '0' || mem[1] != 'x'){
        return 0;
    }

    for (int i = 2; i < *len; i++){
        if (!isHexa(mem[i])){
            return 0;
        }
    }
	return 1;
}

//1 param: memDirec
void printMem(int argc, char params[][LENGTH_PARAMETERS]){
	
	if(argc != 1){
		printf("\tTry printMem with one parameter (memDir)\n");
		return;
	}

	uint64_t len;

	if (!checkMem(params[0], &len)){
		printf("\tRemember that memory addresses go with a ");
		do_printColor("0x ", CYAN);
		printf("in front.\n");
		return;
	}

	if (len == 2) {
		printf("\tWe'll check for memory: ");
		do_printColor("0x", DARKERCYAN);
		do_printColor("00\n", CYAN);
	}

	// we store in mem the pointer to the first memory we want to print
	uint8_t * mem;
	if(!hexStrToInt(params[0],&mem)){
		printf("Parameter is not a valid memory address. Try a smaller number\n");
		return;
	}
	// we print the 32 bytes that follow *mem
	for (int i = 0; i < 32; i++){
		if (i == 16) {
			printf("\n");
		}
		char  buffer[6] = "0x00 ";
		buffer[2] = byteHexToChar(mem[i] >> 4);	// first hex value
		buffer[3] = byteHexToChar(mem[i] & 0x0F);	
		do_printColor("0x", DARKERCYAN);
		do_printColor(buffer+2, CYAN);
	}
	printf("\n");
	return;
}

//1 param: setting
void changeFontSize(int argc, char params[][LENGTH_PARAMETERS]){
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
			printf("\tWarning, font size 3 is way too big!\n");
			printf("\tIf you still want to change the font size type 'y', otherwise type 'n'\n");
			char ans ;
			while(ans != 'y' && ans != 'n')
				ans = do_getChar();
			if(ans == 'y')
				everythingOk = 1;
		}
		if (everythingOk) do_changeFontSize(params[0][0]-'0');
		
	}
	else{
		printf("\tInvalid parameter, try with 1, 2 or 3\n");
	}
	return;
}

//no params
void time(int argc, char params[][LENGTH_PARAMETERS]){
	if(argc!=0){
		printf("\tTry time without parameters\n");
		return;
	}
	printf("\tThis is the current ");
	do_printColor("time ", TURQUOISE);
	printf("in the beautiful city of ");
	do_printColor("GREENWICH: ", HAPPY_MATRIX);
	do_printColor("(UTC+00)\n", CYBER_GRAPE);
	char timeBuffer[9];
	do_getTime(timeBuffer);
	printf("\t\t\t");
	do_printColor(timeBuffer, ICTERINE);
	printf("\n");
	printf("\tBuenos Aires is UTC-03:00\n");

	return;
}

//no params
void tron(int argc, char params[][LENGTH_PARAMETERS]){
	// tron will run even though it has parameters (not a bug, a feature)
	/*if(argc!=0){
		printf("Try tron without parameters\n");
		
	}*/
	play_tron();
	return;
}


void clearScreen(int argc, char params[][LENGTH_PARAMETERS]) {
	do_clearScreen(BLACK);
	return;
}


#include <naiveGraphicsConsole.h>
#include <time.h>
#include <stdint.h>

#define ZERO_EXCEPTION_ID 0
#define INV_OP_EXC 6
#define REGISTERS 18

#define RED 0x0000FF

extern void restart();

static const char* registerNames[REGISTERS] = {
    "rip", "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", "r8 ", "r9 ", "r10", "r11", "r12", "r13", "r14", "r15", "rflags"
};

static const char* errMsg = "The program aborted due to an exception: ";

static const char* errNames[7] = {"Divide by Zero\n", "","","","","","Invalid Operation Code\n"};

//Convertion from int to hex of 16 chars (para que queden todos los registros de la misma longitud)
static void intToHex(uint64_t num, char buffer[17]){
	int i = 16;
	while (i-- != 0){
		int digit = num % 16;
        buffer[i] = (digit < 10 ? '0' : ('A' - 10)) + digit;
        num /= 16;
	}
}

static void printRegisters(uint64_t reg[18]){
	char buf[19];
	buf[0] = '0';
	buf[1] = 'x';
	buf[18] = '\0';
	for (int i = 0; i < REGISTERS; i++){
		ngc_printColor(registerNames[i], RED);
		ngc_printColor(" : ", RED);
		intToHex(reg[i], buf + 2);
		ngc_printColor(buf, RED);
		ngc_printNewline();
	}
	
}

void exceptionDispatcher(uint64_t exception, uint64_t regdata[18]) {
	ngc_printColor(errMsg, RED);
	ngc_printColor(errNames[exception], RED);
	printRegisters(regdata);
	restart();
}
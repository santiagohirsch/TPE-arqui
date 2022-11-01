#include <naiveGraphicsConsole.h>
#include <time.h>
#include <stdint.h>
#define ZERO_EXCEPTION_ID 0
#define INV_OP_EXC 6
#define REGISTERS 18


extern void restart();

static const char* registerNames[REGISTERS] = {
    "rip", "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", "r8 ", "r9 ", "r10", "r11", "r12", "r13", "r14", "r15", "rflags"
};

static const char* errMsg = "The program aborted due to an exception: ";

static const char* errNames[7] = {"Divide by Zero\n", "","","","","","Invalid Operation Code\n"};

static const Color red = {0x00, 0x00, 0xFF};
//Transforma un int a un hexadecimal de 16 char (para que queden todos los registros de la misma longitud)
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
		ngc_printColor(registerNames[i], red);
		ngc_printColor(" : ", red);
		intToHex(reg[i], buf + 2);
		ngc_printColor(buf, red);
		ngc_printNewline();
	}
	
}

void exceptionDispatcher(uint64_t exception, uint64_t regdata[18]) {
	ngc_printColor(errMsg, red);
	ngc_printColor(errNames[exception], red);
	printRegisters(regdata);
	restart();
}
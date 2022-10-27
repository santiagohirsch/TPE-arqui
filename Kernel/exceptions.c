#include <naiveGraphicsConsole.h>
#include <time.h>
#include <stdint.h>
#define ZERO_EXCEPTION_ID 0
#define INV_OP_EXC 6

extern void restart();
static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(uint64_t exception, uint64_t regdata[18]) {
	ngc_print("Dispatcher\n");
	if (exception == ZERO_EXCEPTION_ID) 	zero_division(regdata);
	if (exception == INV_OP_EXC) 	invalid_opcode(regdata);
}

static void zero_division(uint64_t reg[18]){
	ngc_print("zero_division\n");
	restart();
}

static void invalid_opcode(uint64_t reg[18]){
	//rip, rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15, rflags
	/*ngc_print("rip = "); ngc_printHexa(reg[0]);
	ngc_printNewline(); 
	ngc_print("rax = "); ngc_printHexa(reg[1]);
	ngc_printNewline();
	ngc_print("rbx = "); ngc_printHexa(reg[2]);
	ngc_printNewline();
	ngc_print("rcx = "); ngc_printHexa(reg[3]);
	ngc_printNewline();
	ngc_print("rdx = "); ngc_printHexa(reg[4]);
	ngc_printNewline();
	ngc_print("rsi = "); ngc_printHexa(reg[5]);
	ngc_printNewline();
	ngc_print("rdi = "); ngc_printHexa(reg[6]);
	ngc_printNewline();
	ngc_print("rbp = "); ngc_printHexa(reg[7]);
	ngc_printNewline();
	ngc_print("rsp = "); ngc_printHexa(reg[8]);
	ngc_printNewline();
	ngc_print("r8 = "); ngc_printHexa(reg[9]);
	ngc_printNewline();
	ngc_print("r9 = "); ngc_printHexa(reg[10]);
	ngc_printNewline();
	ngc_print("r10 = "); ngc_printHexa(reg[11]);
	ngc_printNewline();
	ngc_print("r11 = "); ngc_printHexa(reg[12]);
	ngc_printNewline();
	ngc_print("r12 = "); ngc_printHexa(reg[13]);
	ngc_printNewline();
	ngc_print("r13 = "); ngc_printHexa(reg[14]);
	ngc_printNewline();
	ngc_print("r14 = "); ngc_printHexa(reg[15]);
	ngc_printNewline();
	ngc_print("r15 = "); ngc_printHexa(reg[16]);
	ngc_printNewline();
	ngc_print("rflags = "); ngc_printHexa(reg[17]);
	ngc_printNewline();*/
	restart();
}
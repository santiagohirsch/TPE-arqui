#include <naiveGraphicsConsole.h>
#include <time.h>
#define ZERO_EXCEPTION_ID 0
#define INV_OP_EXC 1
extern void restart();
static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if (exception == INV_OP_EXC)
		invalid_opcode();
}

static void zero_division(){
	ngc_print("Divide by zero exception");
	while(seconds_elapsed() < 10);
	restart();
}

static void invalid_opcode(){
	return;
}
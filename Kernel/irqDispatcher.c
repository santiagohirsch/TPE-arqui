#include <time.h>
#include <stdint.h>
#include <keyboard.h>
#include <naiveGraphicsConsole.h>

static void int_20();

static void int_21();

static void int_30();

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21();
			break;
		case 10:
			int_30();
	}
	return;
}



void int_20() {
	timer_handler();
}

void int_21(){
	keyboard_handler();
}

void int_30(){
	
}
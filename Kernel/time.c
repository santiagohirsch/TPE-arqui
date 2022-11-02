#include <time.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void wait(uint64_t interval) {
	for (int i=0; i<30000000;i++){
		;
	}/*
	int currentSeconds = seconds_elapsed();
	while (seconds_elapsed() - currentSeconds < interval){;}*/
}

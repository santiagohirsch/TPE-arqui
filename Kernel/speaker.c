#include <stdint.h>
#include <speaker.h>

void beep(uint64_t nFrequency) {
  _beep_start(1193180 / nFrequency);
}

void stopBeep() {
  _beep_stop();
}

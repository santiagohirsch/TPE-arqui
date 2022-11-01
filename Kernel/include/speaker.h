#ifndef SPEAKER_H
#define SPEAKER_H

extern void _beep_start(uint64_t realFrequency);

extern void _beep_stop();

void beep(uint64_t nFrequency);

void stopBeep();

#endif
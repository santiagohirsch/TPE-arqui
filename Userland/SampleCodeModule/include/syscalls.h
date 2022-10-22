#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <stdint.h>
#define STDIN 0
#define STDOUT 1
#define STDERR 2

void sys_write(uint64_t fd, const char * buffer, uint64_t count);

void sys_read(uint64_t fd, const char * buffer, uint64_t count);


#endif
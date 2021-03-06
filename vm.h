#ifndef _BONSAI_H_
#define _BONSAI_H_

#include <stdlib.h>

#define FIXNUM_FLAG 0x01
#define INT2FIX(i) ((VALUE)(i << 1 | FIXNUM_FLAG))

typedef unsigned long VALUE;

void vm_init();
void vm_destroy();
VALUE bonsai_func_call(const char *, size_t, ...);

#endif

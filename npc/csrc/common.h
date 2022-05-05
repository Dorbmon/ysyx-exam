#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "macro.h"
#include <assert.h>
#include <stdlib.h>

typedef uint64_t word_t;
typedef int64_t  sword_t;
#define FMT_WORD MUXDEF(CONFIG_ISA64, "0x%016lx", "0x%08x")

typedef word_t vaddr_t;
typedef uint64_t paddr_t;
#define FMT_PADDR "0x%016lx"
typedef uint16_t ioaddr_t;

#include "debug.h"

#endif

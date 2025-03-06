/*
 * Copyright (C) 2007-2023 Yasuhiro Ohara. All rights reserved.
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdint.h>

#include <zcmdsh/flag.h>

extern uint64_t debug_config;

#define DEBUG_SHELL           (1ULL << 0)
#define DEBUG_COMMAND         (1ULL << 1)
#define DEBUG_TERMIO          (1ULL << 2)
#define DEBUG_TIMER           (1ULL << 3)
#define DEBUG_SDPLANE_WIRETAP (1ULL << 4)

// if (FLAG_CHECK (debug_config, DEBUG_SHELL))

struct debug_type
{
  uint64_t flag;
  const char *name;
};

#endif /*__DEBUG_H__*/

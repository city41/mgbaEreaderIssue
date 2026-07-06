#pragma once
#include <tonc.h>

#define MGBA_LOG_MAX_LINE 256

#define ERROR 0x101
#define WARNING 0x102
#define INFO 0x103
#define DEBUG 0x104

#define REG_LOG_ENABLE	(vu32*)(0x4FFF780)
#define REG_LOG_BUFFER (vu32*)(0x4FFF600)
#define REG_LOG_SEND (vu32*)(0x4FFF700)

#ifdef MGBALOG

void _mgbalog(u32 level, const char *format, ...);

#define mgbalog(...) _mgbalog(__VA_ARGS__)

#else

#define mgbalog(level, format, ...)

#endif
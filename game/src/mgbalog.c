#ifdef MGBALOG
#include "mgbalog.h"
#include <stdarg.h>
#include <stdio.h>

static char logBuffer[MGBA_LOG_MAX_LINE];

void _mgbalog(u32 level, const char *format, ...) {
  *REG_LOG_ENABLE = 0xC0DE;
  va_list formatArgs;
  va_start(formatArgs, format);
  vsnprintf(logBuffer, MGBA_LOG_MAX_LINE, format, formatArgs);
  va_end(formatArgs);
  tonccpy((void *)REG_LOG_BUFFER, logBuffer, MGBA_LOG_MAX_LINE);
  *REG_LOG_SEND = level;
}

#endif
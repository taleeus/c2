/**
 * Heavily inspired (((copied))) by the Kohi Engine
 */

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "base.h"
#include "log.h"

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

char *log_level_str(LogLevel level) {
  switch (level) {
  case LOG_LEVEL_FATAL:
    return BOLDRED "FTL" RESET;
  case LOG_LEVEL_ERROR:
    return RED "ERR" RESET;
  case LOG_LEVEL_WARN:
    return YELLOW "WRN" RESET;
  case LOG_LEVEL_INFO:
    return BLUE "INF" RESET;
  case LOG_LEVEL_DEBUG:
    return MAGENTA "DBG" RESET;
  case LOG_LEVEL_TRACE:
    return CYAN "TRC" RESET;

  default:
    break;
  }
}

void now_str(char *output) {
  itime rawtime;
  struct tm *now;

  time(&rawtime);
  now = localtime(&rawtime);

  sprintf(output, "%d/%02d/%02d %02d:%02d:%02d", now->tm_year + 1900,
          now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min,
          now->tm_sec);
}

void log_out(LogLevel level, const char *message, ...) {
  char out_msg[32000];

  va_list args;
  va_start(args, message);
  vsnprintf(out_msg, sizeof(out_msg), message, args);
  va_end(args);

  char time_buf[100];
  now_str(time_buf);
  fprintf(stderr, "%s %s %s\n", log_level_str(level), time_buf, out_msg);
}

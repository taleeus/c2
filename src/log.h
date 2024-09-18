/**
 * Heavily inspired (((copied))) by the Kohi Engine
 */

#pragma once

/** @brief Indicates if warning level logging is enabled. */
#define LOG_WARN_ENABLED 1
/** @brief Indicates if info level logging is enabled. */
#define LOG_INFO_ENABLED 1

// Disable debug and trace logging for release builds.
#ifdef RELEASE
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#else
/** @brief Indicates if debug level logging is enabled. */
#define LOG_DEBUG_ENABLED 1
/** @brief Indicates if trace level logging is enabled. */
#define LOG_TRACE_ENABLED 1
#endif

/** @brief Represents levels of logging */
typedef enum LogLevel {
  /** @brief Fatal log level, should be used to stop the application when hit.
   */
  LOG_LEVEL_FATAL = 0,
  /** @brief Error log level, should be used to indicate critical runtime
     problems that cause the application to run improperly or not at all. */
  LOG_LEVEL_ERROR = 1,
  /** @brief Warning log level, should be used to indicate non-critial problems
     with the application that cause it to run suboptimally. */
  LOG_LEVEL_WARN = 2,
  /** @brief Info log level, should be used for non-erronuous informational
     purposes. */
  LOG_LEVEL_INFO = 3,
  /** @brief Debug log level, should be used for debugging purposes. */
  LOG_LEVEL_DEBUG = 4,
  /** @brief Trace log level, should be used for verbose debugging purposes. */
  LOG_LEVEL_TRACE = 5
} LogLevel;

void log_out(LogLevel level, const char *message, ...);

/**
 * @brief Logs a fatal-level message. Should be used to stop the application
 * when hit.
 * @param message The message to be logged. Can be a format string for
 * additional parameters.
 * @param ... Additional parameters to be logged.
 */
#define FATAL(message, ...) log_out(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef ERROR
/**
 * @brief Logs an error-level message. Should be used to indicate critical
 * runtime problems that cause the application to run improperly or not at all.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ERROR(message, ...) log_out(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
/**
 * @brief Logs a warning-level message. Should be used to indicate non-critial
 * problems with the application that cause it to run suboptimally.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define WARN(message, ...) log_out(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
/**
 * @brief Logs a warning-level message. Should be used to indicate non-critial
 * problems with the application that cause it to run suboptimally. Does nothing
 * when LOG_WARN_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
/**
 * @brief Logs an info-level message. Should be used for non-erronuous
 * informational purposes.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define INFO(message, ...) log_out(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
/**
 * @brief Logs an info-level message. Should be used for non-erronuous
 * informational purposes. Does nothing when LOG_INFO_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
/**
 * @brief Logs a debug-level message. Should be used for debugging purposes.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define DEBUG(message, ...) log_out(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
/**
 * @brief Logs a debug-level message. Should be used for debugging purposes.
 * Does nothing when LOG_DEBUG_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
/**
 * @brief Logs a trace-level message. Should be used for verbose debugging
 * purposes.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define TRACE(message, ...) log_out(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
/**
 * @brief Logs a trace-level message. Should be used for verbose debugging
 * purposes. Does nothing when LOG_TRACE_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define TRACE(message, ...)
#endif

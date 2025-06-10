#ifndef LUFFY_LOG_H
#define LUFFY_LOG_H

#include "types/alias.h"

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_OFF 4

#define LOG_LEVEL_NAME(level)               \
    ((level) == LOG_LEVEL_DEBUG   ? "DEBUG" \
     : (level) == LOG_LEVEL_INFO  ? "INFO"  \
     : (level) == LOG_LEVEL_WARN  ? "WARN"  \
     : (level) == LOG_LEVEL_ERROR ? "ERROR" \
                                  : "OFF")

extern i32 G_LUFFY_LOG_LEVEL;

/**
 * Set the global log level for the Luffy library.
 *
 * @param level The log level to set. Valid values are:
 *              - LOG_LEVEL_DEBUG
 *              - LOG_LEVEL_INFO
 *              - LOG_LEVEL_WARN
 *              - LOG_LEVEL_ERROR
 *              - LOG_LEVEL_OFF
 */
void set_log_level(int const level);

/**
 * Log a message at the DEBUG level.
 *
 * @param fmt The format string for the log message.
 * @param ... The values to format into the log message.
 */
void log_debug(char const* fmt, ...);

/**
 * Log a message at the INFO level.
 *
 * @param fmt The format string for the log message.
 * @param ... The values to format into the log message.
 */
void log_info(char const* fmt, ...);

/**
 * Log a message at the WARN level.
 *
 * @param fmt The format string for the log message.
 * @param ... The values to format into the log message.
 */
void log_warn(char const* fmt, ...);

/**
 * Log a message at the ERROR level.
 *
 * @param fmt The format string for the log message.
 * @param ... The values to format into the log message.
 */
void log_error(char const* fmt, ...);

#endif  // LUFFY_LOG_H

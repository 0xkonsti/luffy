#ifndef LUFFY_ANSI_H
#define LUFFY_ANSI_H

#include "types/alias.h"

// ANSI escape codes
#define ANSI_RESET "\x1b[0m"

// Modifiers
#define ANSI_BOLD "\x1b[1m"
#define ANSI_DIM "\x1b[2m"
#define ANSI_ITALIC "\x1b[3m"
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_BLINK "\x1b[5m"
#define ANSI_REVERSE "\x1b[7m"
#define ANSI_HIDDEN "\x1b[8m"

// Foreground colors
#define ANSI_BLACK "\x1b[30m"
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_WHITE "\x1b[37m"

// Bright foreground colors
#define ANSI_BRIGHT_BLACK "\x1b[90m"
#define ANSI_BRIGHT_RED "\x1b[91m"
#define ANSI_BRIGHT_GREEN "\x1b[92m"
#define ANSI_BRIGHT_YELLOW "\x1b[93m"
#define ANSI_BRIGHT_BLUE "\x1b[94m"
#define ANSI_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_BRIGHT_CYAN "\x1b[96m"
#define ANSI_BRIGHT_WHITE "\x1b[97m"

// Background colors
#define ANSI_BG_BLACK "\x1b[40m"
#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_BG_YELLOW "\x1b[43m"
#define ANSI_BG_BLUE "\x1b[44m"
#define ANSI_BG_MAGENTA "\x1b[45m"
#define ANSI_BG_CYAN "\x1b[46m"
#define ANSI_BG_WHITE "\x1b[47m"

// Bright background colors
#define ANSI_BG_BRIGHT_BLACK "\x1b[100m"
#define ANSI_BG_BRIGHT_RED "\x1b[101m"
#define ANSI_BG_BRIGHT_GREEN "\x1b[102m"
#define ANSI_BG_BRIGHT_YELLOW "\x1b[103m"
#define ANSI_BG_BRIGHT_BLUE "\x1b[104m"
#define ANSI_BG_BRIGHT_MAGENTA "\x1b[105m"
#define ANSI_BG_BRIGHT_CYAN "\x1b[106m"
#define ANSI_BG_BRIGHT_WHITE "\x1b[107m"

typedef char const* ansi_t;

/**
 * Format a string with ANSI escape codes.
 *
 * @param str The string to format.
 * @param fmt The ANSI format codes to apply.
 * @return A new string with the ANSI formatting applied.
 */
char* ansi_formated(char const* str, ansi_t fmt);

/**
 * Format a string with multiple ANSI escape codes.
 *
 * @param str The string to format.
 * @param fmts
 * @return A new string with the ANSI formatting applied.
 */
char* ansi_formated_multi(char const* str, ansi_t fmts[], usize fmts_count);

/**
 * Format a string with ANSI escape codes and free the original string.
 *
 * @param str The string to format. This will be freed after formatting.
 * @param fmt The ANSI format codes to apply.
 * @return A new string with the ANSI formatting applied.
 */
char* ansi_formated_free(char* str, ansi_t fmt);

/**
 * Format a string with multiple ANSI escape codes and free the original string.
 *
 * @param str The string to format. This will be freed after formatting.
 * @param fmts The ANSI format codes to apply.
 * @param fmts_count The number of format codes in the array.
 * @return A new string with the ANSI formatting applied.
 */
char* ansi_formated_multi_free(char* str, ansi_t fmts[], usize fmts_count);

#endif  // LUFFY_ANSI_H

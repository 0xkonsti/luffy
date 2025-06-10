#include "luffy/log.h"

#include <stdarg.h>
#include <stdio.h>

#include "luffy/ansi.h"

i32 G_LUFFY_LOG_LEVEL = LOG_LEVEL_DEBUG;

static char const* dim_bright_black(char const* str) {
    return ansi_formated_multi(str, (ansi_t[]){ANSI_DIM, ANSI_BRIGHT_BLACK}, 2);
}

static void log_on(i32 const level, char const* lable, char const* fmt, va_list args) {
    if (G_LUFFY_LOG_LEVEL > level) {
        return;
    }
    printf("%s%s%s ~ ", dim_bright_black("["), ansi_formated(lable, ANSI_BOLD), dim_bright_black("]"));
    vprintf(fmt, args);
    printf("\n");
}

void log_debug(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_on(LOG_LEVEL_DEBUG, ansi_formated("DEBUG", ANSI_BRIGHT_BLUE), fmt, args);
    va_end(args);
}

void log_info(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_on(LOG_LEVEL_INFO, ansi_formated("INFO", ANSI_BRIGHT_GREEN), fmt, args);
    va_end(args);
}

void log_warn(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_on(LOG_LEVEL_WARN, ansi_formated("WARN", ANSI_BRIGHT_YELLOW), fmt, args);
    va_end(args);
}

void log_error(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_on(LOG_LEVEL_ERROR, ansi_formated("ERROR", ANSI_BRIGHT_RED), fmt, args);
    va_end(args);
}

void set_log_level(int const level) {
    if (level < LOG_LEVEL_DEBUG || level > LOG_LEVEL_OFF) {
        log_error("Invalid log level: %d. Valid levels are: DEBUG, INFO, WARN, ERROR, OFF.", level);
        return;
    }
    G_LUFFY_LOG_LEVEL = level;
}
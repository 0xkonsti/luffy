#define _CRT_SECURE_NO_WARNINGS
#include "luffy/ansi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ansi_formated(char const* str, ansi_t fmt) {
    if (!str || !fmt) {
        return NULL;
    }

    usize len = snprintf(NULL, 0, "%s%s%s", fmt, str, ANSI_RESET);
    char* formatted_str = malloc(len + 1);
    if (!formatted_str) {
        return NULL;
    }

    snprintf(formatted_str, len + 1, "%s%s%s", fmt, str, ANSI_RESET);
    return formatted_str;
}

char* ansi_formated_multi(char const* str, ansi_t fmts[], usize fmts_count) {
    if (!str || !fmts || fmts_count == 0) {
        return NULL;
    }

    usize len = 0;
    for (usize i = 0; i < fmts_count; ++i) {
        len += strlen(fmts[i]);
    }
    len += strlen(str) + strlen(ANSI_RESET);

    char* formatted_str = malloc(len + 1);
    if (!formatted_str) {
        return NULL;
    }

    formatted_str[0] = '\0';
    usize total_len = len + 1;
    for (usize i = 0; i < fmts_count; ++i) {
        strncat(formatted_str, fmts[i], total_len - strlen(formatted_str) - 1);
    }
    strncat(formatted_str, str, total_len - strlen(formatted_str) - 1);
    strncat(formatted_str, ANSI_RESET, total_len - strlen(formatted_str) - 1);

    return formatted_str;
}

char* ansi_formated_free(char* str, ansi_t fmt) {
    if (!str || !fmt) {
        return NULL;
    }

    char* formatted_str = ansi_formated(str, fmt);
    free(str);
    return formatted_str;
}

char* ansi_formated_multi_free(char* str, ansi_t fmts[], usize fmts_count) {
    if (!str || !fmts || fmts_count == 0) {
        return NULL;
    }

    char* formatted_str = ansi_formated_multi(str, fmts, fmts_count);
    free(str);
    return formatted_str;
}

#ifndef LUFFY_TYPES_RESULT_H
#define LUFFY_TYPES_RESULT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFINE_RESULT_TYPE(ok_type, err_type, name)                                                        \
    typedef struct {                                                                                       \
        ok_type ok;                                                                                        \
        err_type err;                                                                                      \
        bool is_ok;                                                                                        \
    } result_##name;                                                                                       \
                                                                                                           \
    static inline result_##name ok_##name(ok_type val) {                                                   \
        return (result_##name){.ok = val, .is_ok = true};                                                  \
    }                                                                                                      \
                                                                                                           \
    static inline result_##name err_##name(err_type val) {                                                 \
        return (result_##name){.err = val, .is_ok = false};                                                \
    }                                                                                                      \
                                                                                                           \
    static inline bool is_ok_##name(result_##name res) {                                                   \
        return res.is_ok;                                                                                  \
    }                                                                                                      \
                                                                                                           \
    static inline bool is_err_##name(result_##name res) {                                                  \
        return !res.is_ok;                                                                                 \
    }                                                                                                      \
                                                                                                           \
    static inline ok_type unwrap_##name(result_##name res) {                                               \
        if (!res.is_ok) {                                                                                  \
            fprintf(stderr, "Error: Attempted to unwrap an Err value of result_" #name "\n");              \
            exit(1);                                                                                       \
        }                                                                                                  \
        return res.ok;                                                                                     \
    }                                                                                                      \
                                                                                                           \
    static inline err_type unwrap_err_##name(result_##name res) {                                          \
        if (res.is_ok) {                                                                                   \
            fprintf(stderr, "Error: Attempted to unwrap an Ok value as Err in result_" #name "\n");        \
            exit(1);                                                                                       \
        }                                                                                                  \
        return res.err;                                                                                    \
    }                                                                                                      \
                                                                                                           \
    static inline ok_type unwrap_or_##name(result_##name res, ok_type fallback) {                          \
        return res.is_ok ? res.ok : fallback;                                                              \
    }                                                                                                      \
                                                                                                           \
    static inline ok_type unwrap_or_else_##name(result_##name res, ok_type (*fallback_fn)(void)) {         \
        return res.is_ok ? res.ok : fallback_fn();                                                         \
    }                                                                                                      \
                                                                                                           \
    static inline result_##name map_##name(result_##name res, ok_type (*func)(ok_type)) {                  \
        if (res.is_ok) {                                                                                   \
            return ok_##name(func(res.ok));                                                                \
        }                                                                                                  \
        return res;                                                                                        \
    }                                                                                                      \
                                                                                                           \
    static inline void match_##name(result_##name res, void (*ok_fn)(ok_type), void (*err_fn)(err_type)) { \
        if (res.is_ok) {                                                                                   \
            ok_fn(res.ok);                                                                                 \
        } else {                                                                                           \
            err_fn(res.err);                                                                               \
        }                                                                                                  \
    }

#endif  // LUFFY_TYPES_OPTION_H

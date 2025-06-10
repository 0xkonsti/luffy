#ifndef LUFFY_TYPES_OPTION_H
#define LUFFY_TYPES_OPTION_H

#include <stdbool.h>
#include <stdlib.h>

#define DEFINE_OPTION_TYPE(type, name)                                                                 \
    typedef struct {                                                                                   \
        type value;                                                                                    \
        bool is_some;                                                                                  \
    } option_##name;                                                                                   \
                                                                                                       \
    static inline option_##name some_##name(type val) {                                                \
        return (option_##name){.value = val, .is_some = true};                                         \
    }                                                                                                  \
                                                                                                       \
    static inline option_##name none_##name(void) {                                                    \
        option_##name opt = {0};                                                                       \
        opt.is_some = false;                                                                           \
        return opt;                                                                                    \
    }                                                                                                  \
                                                                                                       \
    static inline bool is_some_##name(option_##name opt) {                                             \
        return opt.is_some;                                                                            \
    }                                                                                                  \
                                                                                                       \
    static inline bool is_none_##name(option_##name opt) {                                             \
        return !opt.is_some;                                                                           \
    }                                                                                                  \
                                                                                                       \
    static inline type unwrap_##name(option_##name opt) {                                              \
        if (!opt.is_some) {                                                                            \
            fprintf(                                                                                   \
                stderr,                                                                                \
                "Error: Attempted to unwrap a None value of "                                          \
                "option_" #name ".\n"                                                                  \
            );                                                                                         \
            exit(1);                                                                                   \
        }                                                                                              \
        return opt.value;                                                                              \
    }                                                                                                  \
                                                                                                       \
    static inline type unwrap_or_##name(option_##name opt, type fallback) {                            \
        return opt.is_some ? opt.value : fallback;                                                     \
    }                                                                                                  \
                                                                                                       \
    static inline option_##name map_##name(option_##name opt, type (*func)(type)) {                    \
        if (opt.is_some) {                                                                             \
            return some_##name(func(opt.value));                                                       \
        }                                                                                              \
        return none_##name();                                                                          \
    }                                                                                                  \
                                                                                                       \
    static inline type unwrap_or_else_##name(option_##name opt, type (*fallback_func)(void)) {         \
        return opt.is_some ? opt.value : fallback_func();                                              \
    }                                                                                                  \
                                                                                                       \
    static inline void match_##name(option_##name opt, void (*some_fn)(type), void (*none_fn)(void)) { \
        if (opt.is_some) {                                                                             \
            some_fn(opt.value);                                                                        \
        } else {                                                                                       \
            none_fn();                                                                                 \
        }                                                                                              \
    }

#endif  // LUFFY_TYPES_OPTION_H

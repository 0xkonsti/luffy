#ifndef LUFFY_TYPES_STRING_H
#define LUFFY_TYPES_STRING_H

#include "alias.h"
#include "option.h"
#include "result.h"

typedef struct {
    char* data;      // Pointer to the string data
    usize length;    // Length of the string
    usize capacity;  // Capacity of the allocated memory
} string_t;

#define STRING_INIT_CAPACITY 16
#define STRING_GROWTH_FACTOR 2

DEFINE_OPTION_TYPE(string_t, string_t)

/**
 * Initializes a string with a given capacity.
 *
 * If the capacity is zero, it will be set to the default initial capacity.
 *
 * @param capacity The initial capacity of the string.
 * @return A option_string_t containing the initialized string or None if memory allocation fails.
 */
option_string_t string_init(usize const capacity);

/**
 * Frees the memory allocated for by the string.
 *
 * This function does not free the memory for the string itself,
 * but rather the memory used for the string data.
 *
 * @param str A pointer to the string_t to be freed.
 */
void string_free(string_t* str);

/**
 * Appends a character to the string.
 *
 * If the string does not have enough capacity, it will be resized.
 *
 * @param str A pointer to the string_t to append to.
 * @param c The character to append.
 * @return true if the character was successfully appended, false otherwise.
 */
bool string_append_char(string_t* str, char const c);

/**
 * Appends a C-style string to the string.
 *
 * If the string does not have enough capacity, it will be resized.
 *
 * @param str A pointer to the string_t to append to.
 * @param cstr The C-style string to append.
 * @return true if the C-style string was successfully appended, false otherwise.
 */
bool string_append_cstr(string_t* str, char const* cstr, usize const cstr_length);

/**
 * Appends a string to the string.
 *
 * If the string does not have enough capacity, it will be resized.
 *
 * @param str A pointer to the string_t to append to.
 * @param other The string to append.
 * @return true if the string was successfully appended, false otherwise.
 */
bool string_append_string(string_t* str, string_t const* other);

/**
 * Resizes the string to a new capacity.
 *
 * If the new capacity is less than the current length, the string will be truncated.
 *
 * @param str A pointer to the string_t to resize.
 * @param new_capacity The new capacity for the string.
 * @return true if the string was successfully resized, false otherwise.
 */
bool string_resize(string_t* str, usize const new_capacity);

/**
 * Creates a new string with the given C-style string.
 *
 * This function allocates memory for the new string and copies the C-style string into it.
 *
 * @param cstr The C-style string to copy.
 * @return A option_string_t containing the new string or None if memory allocation fails.
 */
option_string_t string_from_cstr(char const* cstr, usize const cstr_length);

/**
 * Creates a new string with the given string.
 *
 * This function allocates memory for the new string and copies the contents of the given string into it.
 *
 * @param other The string to copy.
 * @return A option_string_t containing the new string or None if memory allocation fails.
 */
option_string_t string_from_string(string_t const* other);

/**
 * Converts the string to a C-style string.
 *
 * This function does not allocate new memory for the C-style string,
 * it simply returns a pointer to the string's data.
 *
 * @param str A pointer to the string_t to convert.
 * @return A pointer to the C-style string data.
 */
static inline char const* string_to_cstr(string_t const str) {
    return str.data;
}

/**
 * Gets the length of the string.
 *
 * @param str A pointer to the string_t to get the length of.
 * @return The length of the string.
 */
static inline usize string_length(string_t const str) {
    return str.length;
}

/**
 * Gets the capacity of the string.
 *
 * @param str A pointer to the string_t to get the capacity of.
 * @return The capacity of the string.
 */
static inline usize string_capacity(string_t const str) {
    return str.capacity;
}

/**
 * Checks if the string is empty.
 *
 * @param str A pointer to the string_t to check.
 * @return true if the string is empty, false otherwise.
 */
static inline bool string_is_empty(string_t const str) {
    return str.length == 0;
}

/**
 * Checks if the string is full.
 *
 * @param str A pointer to the string_t to check.
 * @return true if the string is full, false otherwise.
 */
static inline bool string_is_full(string_t const str) {
    return str.length == str.capacity - 1;  // -1 for null terminator
}

#endif  // LUFFY_TYPES_STRING_H

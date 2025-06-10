#include "luffy/types/string.h"

#include <string.h>

option_string_t string_init(usize const capacity) {
    usize _capacity = capacity + 1;  // +1 for null terminator
    if (capacity == 0) {
        _capacity = STRING_INIT_CAPACITY + 1;
    }

    string_t str;
    str.data = malloc(_capacity * sizeof(char));

    if (!str.data) {
        return none_string_t();
    }

    str.length = 0;
    str.capacity = _capacity - 1;  // -1 for null terminator
    str.data[0] = '\0';            // Ensure the string is null-terminated

    return some_string_t(str);
}

void string_free(string_t* str) {
    if (str && str->data) {
        free(str->data);
        str->data = NULL;
        str->length = 0;
        str->capacity = 0;
    }
}

bool string_append_char(string_t* str, char const c) {
    if (!str) {
        return false;
    }

    if (string_is_full(*str)) {
        usize new_capacity = str->capacity * STRING_GROWTH_FACTOR + 1;  // +1 for null terminator
        char* new_data = realloc(str->data, new_capacity * sizeof(char));
        if (!new_data) {
            return false;
        }
        str->data = new_data;
        str->capacity = new_capacity - 1;  // -1 for null terminator
    }

    str->data[str->length++] = c;
    str->data[str->length] = '\0';  // Ensure the string is null-terminated
    return true;
}

bool string_append_cstr(string_t* str, char const* cstr, usize const cstr_length) {
    if (!str || !cstr || cstr_length == 0) {
        return false;
    }

    if (string_is_full(*str)) {
        usize new_capacity = (str->capacity + cstr_length) * STRING_GROWTH_FACTOR + 1;
        char* new_data = realloc(str->data, new_capacity * sizeof(char));
        if (!new_data) {
            return false;
        }
        str->data = new_data;
        str->capacity = new_capacity - 1;  // -1 for null terminator
    }

    memcpy(str->data + str->length, cstr, cstr_length * sizeof(char));
    str->length += cstr_length;
    str->data[str->length] = '\0';

    return true;
}

bool string_append_string(string_t* str, string_t const* other) {
    if (!str || !other || other->length == 0) {
        return false;
    }

    return string_append_cstr(str, other->data, other->length);
}

option_string_t string_from_cstr(char const* cstr, usize const cstr_length) {
    if (!cstr) {
        return none_string_t();
    }

    option_string_t opt_str = string_init(cstr_length);
    if (is_none_string_t(opt_str)) {
        return opt_str;
    }

    memcpy(opt_str.value.data, cstr, cstr_length * sizeof(char));
    opt_str.value.data[cstr_length] = '\0';
    opt_str.value.length = cstr_length;
    opt_str.value.capacity = cstr_length;

    return opt_str;
}

option_string_t string_from_string(string_t const* other) {
    if (!other) {
        return none_string_t();
    }

    option_string_t opt_str = string_init(other->length);
    if (is_none_string_t(opt_str)) {
        return opt_str;
    }

    memcpy(opt_str.value.data, other->data, other->length * sizeof(char));
    opt_str.value.data[other->length] = '\0';  // Ensure null termination
    opt_str.value.length = other->length;
    opt_str.value.capacity = other->capacity;
    return opt_str;
}

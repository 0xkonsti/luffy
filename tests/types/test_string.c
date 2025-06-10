#include <string.h>

#include "luffy/types/string.h"
#include "unity.h"

void setUp(void) {
}
void tearDown(void) {
}

void test_string_init_and_free(void) {
    option_string_t opt = string_init(0);
    TEST_ASSERT_TRUE(is_some_string_t(opt));
    string_t str = unwrap_string_t(opt);
    TEST_ASSERT_NOT_NULL(str.data);
    TEST_ASSERT_EQUAL_UINT64(0, str.length);
    TEST_ASSERT_GREATER_THAN(0, str.capacity);
    string_free(&str);
}

void test_string_append_char(void) {
    string_t str = unwrap_string_t(string_init(1));
    bool ok = string_append_char(&str, 'A');
    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL_STRING("A", str.data);
    TEST_ASSERT_EQUAL_UINT64(1, str.length);
    string_free(&str);
}

void test_string_append_cstr(void) {
    string_t str = unwrap_string_t(string_init(1));
    char const* text = "Hello";
    bool ok = string_append_cstr(&str, text, strlen(text));
    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL_STRING("Hello", str.data);
    TEST_ASSERT_EQUAL_UINT64(strlen(text), str.length);
    string_free(&str);
}

void test_string_append_string(void) {
    string_t base = unwrap_string_t(string_init(1));
    string_t src = unwrap_string_t(string_from_cstr("World", 5));
    string_append_string(&base, &src);
    TEST_ASSERT_EQUAL_STRING("World", base.data);
    string_free(&base);
    string_free(&src);
}

void test_string_growth(void) {
    string_t str = unwrap_string_t(string_init(1));
    for (int i = 0; i < 100; ++i) {
        TEST_ASSERT_TRUE(string_append_char(&str, 'a'));
    }
    TEST_ASSERT_EQUAL_UINT64(100, str.length);
    TEST_ASSERT_TRUE(str.capacity > 100);
    string_free(&str);
}

void test_string_from_cstr(void) {
    option_string_t opt = string_from_cstr("Test", 4);
    TEST_ASSERT_TRUE(is_some_string_t(opt));
    TEST_ASSERT_EQUAL_STRING("Test", opt.value.data);
    TEST_ASSERT_EQUAL_UINT64(4, opt.value.length);
    string_free(&opt.value);
}

void test_string_from_null_cstr(void) {
    option_string_t opt = string_from_cstr(NULL, 0);
    TEST_ASSERT_TRUE(is_none_string_t(opt));
}

void test_string_from_string(void) {
    string_t original = unwrap_string_t(string_from_cstr("Copy", 4));
    option_string_t copy = string_from_string(&original);
    TEST_ASSERT_TRUE(is_some_string_t(copy));
    TEST_ASSERT_EQUAL_STRING("Copy", copy.value.data);
    TEST_ASSERT_EQUAL_UINT64(original.length, copy.value.length);
    string_free(&original);
    string_free(&copy.value);
}

void test_string_static_methods(void) {
    string_t str = unwrap_string_t(string_from_cstr("abc", 3));
    TEST_ASSERT_EQUAL_STRING("abc", string_to_cstr(str));
    TEST_ASSERT_EQUAL_UINT64(3, string_length(str));
    TEST_ASSERT_FALSE(string_is_empty(str));
    string_free(&str);
}

void test_string_empty_and_full(void) {
    string_t str = unwrap_string_t(string_init(1));
    TEST_ASSERT_TRUE(string_is_empty(str));
    string_append_char(&str, 'X');
    TEST_ASSERT_TRUE(string_is_full(str));
    string_free(&str);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_string_init_and_free);
    RUN_TEST(test_string_append_char);
    RUN_TEST(test_string_append_cstr);
    RUN_TEST(test_string_append_string);
    RUN_TEST(test_string_growth);
    RUN_TEST(test_string_from_cstr);
    RUN_TEST(test_string_from_null_cstr);
    RUN_TEST(test_string_from_string);
    RUN_TEST(test_string_static_methods);
    RUN_TEST(test_string_empty_and_full);

    return UNITY_END();
}

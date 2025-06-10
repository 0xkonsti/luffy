#include <stdio.h>
#include <string.h>

#include "luffy/types/option.h"
#include "unity.h"

DEFINE_OPTION_TYPE(int, int)
DEFINE_OPTION_TYPE(char const*, str)

void setUp(void) {
}
void tearDown(void) {
}

/// Test: Erzeugung von Some(int)
void test_some_int(void) {
    option_int opt = some_int(42);
    TEST_ASSERT_TRUE(is_some_int(opt));
    TEST_ASSERT_FALSE(is_none_int(opt));
    TEST_ASSERT_EQUAL_INT(42, unwrap_int(opt));
    TEST_ASSERT_EQUAL_INT(42, unwrap_or_int(opt, 0));
}

/// Test: None(int) sollte false bei is_some sein
void test_none_int(void) {
    option_int opt = none_int();
    TEST_ASSERT_FALSE(is_some_int(opt));
    TEST_ASSERT_TRUE(is_none_int(opt));
    TEST_ASSERT_EQUAL_INT(123, unwrap_or_int(opt, 123));
}

/// Test: unwrap(None) → erwartet crash (nicht getestet hier)
void test_unwrap_none_crash(void) {
    // ⚠️ Kann nicht sicher getestet werden, außer man mockt exit()
    // option_int opt = none_int();
    // unwrap_int(opt); // würde Programm beenden
}

/// Test: 0 als gültiger Wert
void test_some_zero(void) {
    option_int opt = some_int(0);
    TEST_ASSERT_TRUE(is_some_int(opt));
    TEST_ASSERT_EQUAL_INT(0, unwrap_or_int(opt, 999));
}

/// Test: map(int)
int double_int(int x) {
    return x * 2;
}

void test_map_int(void) {
    option_int a = some_int(10);
    option_int b = map_int(a, double_int);
    TEST_ASSERT_EQUAL_INT(20, unwrap_int(b));

    option_int none = none_int();
    option_int still_none = map_int(none, double_int);
    TEST_ASSERT_TRUE(is_none_int(still_none));
}

/// Test: Option<const char*>
char const* fallback_str = "fallback";

void test_some_str(void) {
    option_str opt = some_str("hello");
    TEST_ASSERT_TRUE(is_some_str(opt));
    TEST_ASSERT_EQUAL_STRING("hello", unwrap_str(opt));
}

void test_none_str(void) {
    option_str opt = none_str();
    TEST_ASSERT_FALSE(is_some_str(opt));
    TEST_ASSERT_EQUAL_STRING(fallback_str, unwrap_or_str(opt, fallback_str));
}

char const* to_upper(char const* s) {
    if (strcmp(s, "abc") == 0) return "ABC";
    return s;
}

void test_map_str(void) {
    option_str a = some_str("abc");
    option_str b = map_str(a, to_upper);
    TEST_ASSERT_EQUAL_STRING("ABC", unwrap_str(b));
}

/// Unity-Entry
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_some_int);
    RUN_TEST(test_none_int);
    RUN_TEST(test_some_zero);
    RUN_TEST(test_map_int);
    RUN_TEST(test_some_str);
    RUN_TEST(test_none_str);
    RUN_TEST(test_map_str);

    return UNITY_END();
}

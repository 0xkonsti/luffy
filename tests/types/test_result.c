#include <stdio.h>
#include <string.h>

#include "luffy/types/result.h"
#include "unity.h"

DEFINE_RESULT_TYPE(int, char const*, int_str)
DEFINE_RESULT_TYPE(char const*, char const*, str_str)

void setUp(void) {
}
void tearDown(void) {
}

/// Test: Ok-Wert
void test_result_ok(void) {
    result_int_str res = ok_int_str(123);
    TEST_ASSERT_TRUE(is_ok_int_str(res));
    TEST_ASSERT_FALSE(is_err_int_str(res));
    TEST_ASSERT_EQUAL_INT(123, unwrap_int_str(res));
}

/// Test: Err-Wert
void test_result_err(void) {
    result_int_str res = err_int_str("Fehler");
    TEST_ASSERT_FALSE(is_ok_int_str(res));
    TEST_ASSERT_TRUE(is_err_int_str(res));
    TEST_ASSERT_EQUAL_STRING("Fehler", unwrap_err_int_str(res));
}

/// Test: unwrap_or
void test_result_unwrap_or(void) {
    result_int_str ok = ok_int_str(42);
    result_int_str err = err_int_str("fail");

    TEST_ASSERT_EQUAL_INT(42, unwrap_or_int_str(ok, 0));
    TEST_ASSERT_EQUAL_INT(999, unwrap_or_int_str(err, 999));
}

/// Test: unwrap_or_else
int fallback_func(void) {
    return 777;
}

void test_result_unwrap_or_else(void) {
    result_int_str ok = ok_int_str(5);
    result_int_str err = err_int_str("nope");

    TEST_ASSERT_EQUAL_INT(5, unwrap_or_else_int_str(ok, fallback_func));
    TEST_ASSERT_EQUAL_INT(777, unwrap_or_else_int_str(err, fallback_func));
}

/// Test: map
int triple(int x) {
    return x * 3;
}

void test_result_map(void) {
    result_int_str ok = ok_int_str(4);
    result_int_str mapped = map_int_str(ok, triple);
    TEST_ASSERT_TRUE(is_ok_int_str(mapped));
    TEST_ASSERT_EQUAL_INT(12, unwrap_int_str(mapped));

    result_int_str err = err_int_str("E");
    result_int_str still_err = map_int_str(err, triple);
    TEST_ASSERT_TRUE(is_err_int_str(still_err));
    TEST_ASSERT_EQUAL_STRING("E", unwrap_err_int_str(still_err));
}

/// Test: match
char const* state = NULL;

void save_ok(int val) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "OK_%d", val);
    state = buf;
}

void save_err(char const* msg) {
    state = msg;
}

void test_result_match(void) {
    result_int_str ok = ok_int_str(3);
    result_int_str err = err_int_str("problem");

    match_int_str(ok, save_ok, save_err);
    TEST_ASSERT_EQUAL_STRING("OK_3", state);

    match_int_str(err, save_ok, save_err);
    TEST_ASSERT_EQUAL_STRING("problem", state);
}

/// Main
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_result_ok);
    RUN_TEST(test_result_err);
    RUN_TEST(test_result_unwrap_or);
    RUN_TEST(test_result_unwrap_or_else);
    RUN_TEST(test_result_map);
    RUN_TEST(test_result_match);

    return UNITY_END();
}

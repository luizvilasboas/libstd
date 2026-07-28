#include "../include/base_string.h"

#include <check.h>
#include <stdlib.h>
#include <valgrind/valgrind.h>

START_TEST(test_string_create) {
  string* str = string_create("Hello");
  ck_assert_ptr_nonnull(str);
  ck_assert_str_eq(string_to_c(str), "Hello");
  ck_assert_int_eq(string_length(str), 5);
  ck_assert_int_ge(string_capacity(str), 6);
  string_destroy(str);
}
END_TEST

START_TEST(test_string_create_empty) {
  string* str = string_create(NULL);
  ck_assert_ptr_nonnull(str);
  ck_assert_str_eq(string_to_c(str), "");
  ck_assert_int_eq(string_length(str), 0);
  ck_assert_int_ge(string_capacity(str), 1);
  string_destroy(str);
}
END_TEST

START_TEST(test_string_concat) {
  string* str = string_create("Hello");
  string_concat(str, " World");
  ck_assert_str_eq(string_to_c(str), "Hello World");
  ck_assert_int_eq(string_length(str), 11);
  ck_assert_int_ge(string_capacity(str), 11);
  string_destroy(str);
}
END_TEST

START_TEST(test_string_compare) {
  string* str_1 = string_create("Hello");
  string* str_2 = string_create("Hello");
  ck_assert_int_eq(string_compare(str_1, str_2), 0);

  string_concat(str_2, " World");
  ck_assert_int_lt(string_compare(str_1, str_2), 0);

  string_destroy(str_1);
  string_destroy(str_2);
}
END_TEST

START_TEST(test_string_length) {
  string* str = string_create("Check");
  ck_assert_int_eq(string_length(str), 5);
  string_destroy(str);
}
END_TEST

START_TEST(test_string_clear) {
  string* str = string_create("Hello");
  string_clear(str);
  ck_assert_str_eq(string_to_c(str), "");
  ck_assert_int_eq(string_length(str), 0);
  string_destroy(str);
}
END_TEST

START_TEST(test_string_reserve) {
  string* str = string_create("Hello");
  size_t old_capacity = string_capacity(str);
  string_reserve(str, old_capacity + 50);
  ck_assert_int_ge(string_capacity(str), old_capacity + 50);
  string_destroy(str);
}
END_TEST

START_TEST(test_string_set) {
  string* str = string_create("Hello");
  string_set(str, "World");

  ck_assert_str_eq(string_to_c(str), "World");
  ck_assert_int_eq(string_length(str), 5);

  string_destroy(str);
}
END_TEST

START_TEST(test_string_contains) {
  string* str = string_create("Hello World");

  ck_assert(string_contains(str, "World"));
  ck_assert(!string_contains(str, "Universe"));

  string_destroy(str);
}
END_TEST

START_TEST(test_string_replace) {
  string* str = string_create("Hello World");

  string_replace(str, "World", "Universe");
  ck_assert_str_eq(string_to_c(str), "Hello Universe");

  string_destroy(str);
}
END_TEST

START_TEST(test_string_split) {
  string* str = string_create("one,two,three,four");
  size_t num_tokens;

  string** tokens = string_split(str, ",", &num_tokens);

  ck_assert_int_eq(num_tokens, 4);
  ck_assert_str_eq(string_to_c(tokens[0]), "one");
  ck_assert_str_eq(string_to_c(tokens[1]), "two");
  ck_assert_str_eq(string_to_c(tokens[2]), "three");
  ck_assert_str_eq(string_to_c(tokens[3]), "four");

  for (size_t i = 0; i < num_tokens; i++) {
    string_destroy(tokens[i]);
  }

  free(tokens);
  string_destroy(str);
}
END_TEST

Suite* string_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("String");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_string_create);
  tcase_add_test(tc_core, test_string_create_empty);
  tcase_add_test(tc_core, test_string_concat);
  tcase_add_test(tc_core, test_string_compare);
  tcase_add_test(tc_core, test_string_length);
  tcase_add_test(tc_core, test_string_clear);
  tcase_add_test(tc_core, test_string_reserve);
  tcase_add_test(tc_core, test_string_set);
  tcase_add_test(tc_core, test_string_contains);
  if (!RUNNING_ON_VALGRIND) tcase_add_test(tc_core, test_string_replace);
  tcase_add_test(tc_core, test_string_split);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

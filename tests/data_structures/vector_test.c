#include "../../include/data_structures/vector.h"

#include <check.h>
#include <stdlib.h>
#include <string.h>

int cmp_fn(void* a, void* b) { return (*(int*)a - *(int*)b); }

START_TEST(test_vector_init) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  ck_assert_int_eq(vector.size, 0);
  ck_assert_ptr_eq(vector.head, NULL);

  vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_insert) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  int a = 1, b = 2;

  ck_assert(vector_insert(&vector, &a));
  ck_assert_int_eq(vector.size, 1);
  ck_assert_ptr_ne(vector.head, NULL);
  ck_assert_int_eq(*(int*)vector.head->data, 1);

  ck_assert(vector_insert(&vector, &b));
  ck_assert_int_eq(vector.size, 2);
  ck_assert_int_eq(*(int*)vector.head->data, 2);

  vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_remove) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  int a = 1, b = 2;

  vector_insert(&vector, &a);
  vector_insert(&vector, &b);

  ck_assert(vector_remove(&vector, 0));
  ck_assert_int_eq(vector.size, 1);
  ck_assert_int_eq(*(int*)vector.head->data, 1);

  ck_assert(vector_remove(&vector, 0));
  ck_assert_int_eq(vector.size, 0);
  ck_assert_ptr_eq(vector.head, NULL);

  vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_update) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  int a = 1, b = 2, new_value = 3;

  vector_insert(&vector, &a);
  vector_insert(&vector, &b);

  ck_assert(vector_update(&vector, 0, &new_value));
  ck_assert_int_eq(*(int*)vector.head->data, 3);

  vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_get) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  int a = 1, b = 2;

  vector_insert(&vector, &a);
  vector_insert(&vector, &b);

  int* result = (int*)vector_get(&vector, 1);
  ck_assert_int_eq(*result, 1);

  result = (int*)vector_get(&vector, 0);
  ck_assert_int_eq(*result, 2);

  vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_search) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  int a = 1, b = 2;

  vector_insert(&vector, &a);
  vector_insert(&vector, &b);

  int pos = vector_search(&vector, cmp_fn, &a);
  ck_assert_int_eq(pos, 1);

  pos = vector_search(&vector, cmp_fn, &b);
  ck_assert_int_eq(pos, 0);

  pos = vector_search(&vector, cmp_fn, NULL);
  ck_assert_int_eq(pos, -1);

  vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_destroy) {
  Vector vector;
  vector_init(&vector, sizeof(int));

  int a = 1;

  vector_insert(&vector, &a);

  vector_destroy(&vector);

  ck_assert_int_eq(vector.size, 0);
  ck_assert_ptr_eq(vector.head, NULL);
  ck_assert_int_eq(vector.element_size, 0);

  vector_destroy(&vector);
}
END_TEST

Suite* vector_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("Vector");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_vector_init);
  tcase_add_test(tc_core, test_vector_insert);
  tcase_add_test(tc_core, test_vector_remove);
  tcase_add_test(tc_core, test_vector_update);
  tcase_add_test(tc_core, test_vector_get);
  tcase_add_test(tc_core, test_vector_search);
  tcase_add_test(tc_core, test_vector_destroy);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = vector_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

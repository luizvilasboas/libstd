#include "../../include/data_structures/stack.h"

#include <check.h>
#include <stdlib.h>

int cmp_fn(void* a, void* b) { return (*(int*)a - *(int*)b); }

START_TEST(test_stack_init) {
  Stack stack;
  stack_init(&stack, sizeof(int));

  ck_assert_ptr_eq(stack.top, NULL);
  ck_assert_int_eq(stack.size, 0);
  ck_assert_int_eq(stack.element_size, sizeof(int));

  stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_push) {
  Stack stack;
  stack_init(&stack, sizeof(int));

  int a = 1, b = 2, c = 3;

  ck_assert(stack_push(&stack, &a));
  ck_assert_int_eq(stack.size, 1);

  ck_assert(stack_push(&stack, &b));
  ck_assert_int_eq(stack.size, 2);

  ck_assert(stack_push(&stack, &c));
  ck_assert_int_eq(stack.size, 3);

  int* data = (int*)stack.top->data;
  ck_assert_int_eq(*data, c);

  stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_pop) {
  Stack stack;
  stack_init(&stack, sizeof(int));

  int a = 1, b = 2, c = 3;

  stack_push(&stack, &a);
  stack_push(&stack, &b);
  stack_push(&stack, &c);

  ck_assert(stack_pop(&stack));
  ck_assert_int_eq(stack.size, 2);

  int* data = (int*)stack.top->data;
  ck_assert_int_eq(*data, b);

  ck_assert(stack_pop(&stack));
  ck_assert_int_eq(stack.size, 1);

  data = (int*)stack.top->data;
  ck_assert_int_eq(*data, a);

  ck_assert(stack_pop(&stack));
  ck_assert_int_eq(stack.size, 0);
  ck_assert_ptr_eq(stack.top, NULL);

  ck_assert(!stack_pop(&stack));

  stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_top) {
  Stack stack;
  stack_init(&stack, sizeof(int));

  int a = 1, b = 2, c = 3;

  stack_push(&stack, &a);
  stack_push(&stack, &b);
  stack_push(&stack, &c);

  int* top_value = (int*)stack_top(&stack);
  ck_assert_int_eq(*top_value, c);

  stack_pop(&stack);
  top_value = (int*)stack_top(&stack);
  ck_assert_int_eq(*top_value, b);

  stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_search) {
  Stack stack;
  stack_init(&stack, sizeof(int));

  int a = 1, b = 2, c = 3;

  stack_push(&stack, &a);
  stack_push(&stack, &b);
  stack_push(&stack, &c);

  int search_value = 2;
  int index = stack_search(&stack, cmp_fn, &search_value);
  ck_assert_int_eq(index, 1);

  search_value = 3;
  index = stack_search(&stack, cmp_fn, &search_value);
  ck_assert_int_eq(index, 0);

  search_value = 100;
  index = stack_search(&stack, cmp_fn, &search_value);
  ck_assert_int_eq(index, -1);

  stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_size) {
  Stack stack;
  stack_init(&stack, sizeof(int));

  int a = 1, b = 2;

  stack_push(&stack, &a);
  ck_assert_int_eq(stack_size(&stack), 1);

  stack_push(&stack, &b);
  ck_assert_int_eq(stack_size(&stack), 2);

  stack_pop(&stack);
  ck_assert_int_eq(stack_size(&stack), 1);

  stack_pop(&stack);
  ck_assert_int_eq(stack_size(&stack), 0);

  stack_destroy(&stack);
}
END_TEST

Suite* stack_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("Stack");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_stack_init);
  tcase_add_test(tc_core, test_stack_push);
  tcase_add_test(tc_core, test_stack_pop);
  tcase_add_test(tc_core, test_stack_top);
  tcase_add_test(tc_core, test_stack_search);
  tcase_add_test(tc_core, test_stack_size);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = stack_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include "../../include/data_structures/queue.h"

#include <check.h>
#include <stdlib.h>
#include <string.h>

int cmp_fn(void* a, void* b) { return (*(int*)a - *(int*)b); }

START_TEST(test_queue_init) {
  Queue queue;
  queue_init(&queue, sizeof(int));

  ck_assert_int_eq(queue.size, 0);
  ck_assert_ptr_eq(queue.front, NULL);
  ck_assert_ptr_eq(queue.back, NULL);

  queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_push) {
  Queue queue;
  queue_init(&queue, sizeof(int));

  int a = 1, b = 2;

  ck_assert_int_eq(queue_push(&queue, &a), 1);
  ck_assert_int_eq(queue.size, 1);
  ck_assert_ptr_ne(queue.front, NULL);
  ck_assert_ptr_ne(queue.back, NULL);

  int* data = (int*)queue.front->data;
  ck_assert_int_eq(*data, 1);

  ck_assert_int_eq(queue_push(&queue, &b), 1);
  ck_assert_int_eq(queue.size, 2);

  data = (int*)queue.back->data;
  ck_assert_int_eq(*data, 2);

  queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_pop) {
  Queue queue;
  queue_init(&queue, sizeof(int));

  int a = 1, b = 2;

  queue_push(&queue, &a);
  queue_push(&queue, &b);

  ck_assert_int_eq(queue_pop(&queue), 1);
  ck_assert_int_eq(queue.size, 1);
  ck_assert_int_eq(*(int*)queue.front->data, 2);

  ck_assert_int_eq(queue_pop(&queue), 1);
  ck_assert_int_eq(queue.size, 0);
  ck_assert_ptr_eq(queue.front, NULL);
  ck_assert_ptr_eq(queue.back, NULL);

  queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_search) {
  Queue queue;
  queue_init(&queue, sizeof(int));

  int a = 1, b = 2, c = 3;

  queue_push(&queue, &a);
  queue_push(&queue, &b);
  queue_push(&queue, &c);

  ck_assert_int_eq(queue_search(&queue, cmp_fn, &a), 0);
  ck_assert_int_eq(queue_search(&queue, cmp_fn, &b), 1);
  ck_assert_int_eq(queue_search(&queue, cmp_fn, &c), 2);

  queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_destroy) {
  Queue queue;
  queue_init(&queue, sizeof(int));

  int a = 1;

  queue_push(&queue, &a);

  queue_destroy(&queue);
  ck_assert_int_eq(queue.size, 0);
  ck_assert_ptr_eq(queue.front, NULL);
  ck_assert_ptr_eq(queue.back, NULL);
  ck_assert_int_eq(queue.element_size, 0);

  queue_destroy(&queue);
}
END_TEST

Suite* queue_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("Queue");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_queue_init);
  tcase_add_test(tc_core, test_queue_push);
  tcase_add_test(tc_core, test_queue_pop);
  tcase_add_test(tc_core, test_queue_search);
  tcase_add_test(tc_core, test_queue_destroy);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = queue_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

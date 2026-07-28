#include "../../include/data_structures/hashmap.h"

#include <check.h>
#include <stdlib.h>

unsigned long simple_hash(void* key) { return (unsigned long)*(int*)key; }

int cmp_fn(void* a, void* b) { return *(int*)a - *(int*)b; }

START_TEST(test_hashmap_init) {
  HashMap map;
  hashmap_init(&map, 10, sizeof(int), sizeof(int), simple_hash, cmp_fn);

  ck_assert_ptr_nonnull(map.buckets);
  ck_assert_int_eq(map.bucket_count, 10);
  ck_assert_int_eq(map.size, 0);

  hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_insert) {
  HashMap map;
  hashmap_init(&map, 10, sizeof(int), sizeof(int), simple_hash, cmp_fn);

  int key = 42;
  int value = 100;
  bool inserted = hashmap_insert(&map, &key, &value);

  ck_assert(inserted);
  ck_assert_int_eq(map.size, 1);

  hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_remove) {
  HashMap map;
  hashmap_init(&map, 10, sizeof(int), sizeof(int), simple_hash, cmp_fn);

  int key = 42;
  int value = 100;
  hashmap_insert(&map, &key, &value);

  bool removed = hashmap_remove(&map, &key);
  ck_assert(removed);
  ck_assert_int_eq(map.size, 0);

  hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_get) {
  HashMap map;
  hashmap_init(&map, 10, sizeof(int), sizeof(int), simple_hash, cmp_fn);

  int key = 42;
  int value = 100;
  hashmap_insert(&map, &key, &value);

  int* retrieved_value = (int*)hashmap_get(&map, &key);
  ck_assert_ptr_nonnull(retrieved_value);
  ck_assert_int_eq(*retrieved_value, 100);

  hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_update) {
  HashMap map;
  hashmap_init(&map, 10, sizeof(int), sizeof(int), simple_hash, cmp_fn);

  int key = 42;
  int value = 100;
  int new_value = 200;

  hashmap_insert(&map, &key, &value);
  bool updated = hashmap_update(&map, &key, &new_value);

  ck_assert(updated);

  int* retrieved_value = (int*)hashmap_get(&map, &key);
  ck_assert_ptr_nonnull(retrieved_value);
  ck_assert_int_eq(*retrieved_value, 200);

  hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_size) {
  HashMap map;
  hashmap_init(&map, 10, sizeof(int), sizeof(int), simple_hash, cmp_fn);

  int key1 = 1, value1 = 100;
  int key2 = 2, value2 = 200;

  hashmap_insert(&map, &key1, &value1);
  hashmap_insert(&map, &key2, &value2);

  ck_assert_int_eq(hashmap_size(&map), 2);

  hashmap_destroy(&map);
}
END_TEST

Suite* hashmap_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("HashMap");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_hashmap_init);
  tcase_add_test(tc_core, test_hashmap_insert);
  tcase_add_test(tc_core, test_hashmap_remove);
  tcase_add_test(tc_core, test_hashmap_get);
  tcase_add_test(tc_core, test_hashmap_update);
  tcase_add_test(tc_core, test_hashmap_size);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = hashmap_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

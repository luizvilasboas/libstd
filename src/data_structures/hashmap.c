#include "../../include/data_structures/hashmap.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static HashNode* create_node(size_t key_size, size_t value_size,
                             const void* key, const void* value) {
  if (key == NULL || value == NULL || key_size == 0 || value_size == 0) {
    return NULL;
  }

  HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
  if (new_node == NULL) {
    return NULL;
  }

  new_node->key = malloc(key_size);
  new_node->value = malloc(value_size);
  if (new_node->key == NULL || new_node->value == NULL) {
    free(new_node);
    return NULL;
  }

  memcpy(new_node->key, key, key_size);
  memcpy(new_node->value, value, value_size);
  new_node->next = NULL;

  return new_node;
}

void hashmap_init(HashMap* map, size_t bucket_count, size_t key_size,
                  size_t value_size, unsigned long (*hash_fn)(void*),
                  int (*cmp_fn)(void*, void*)) {
  if (map == NULL || bucket_count == 0 || key_size == 0 || value_size == 0 ||
      hash_fn == NULL || cmp_fn == NULL) {
    return;
  }

  map->buckets = (HashNode**)calloc(bucket_count, sizeof(HashNode*));
  if (map->buckets == NULL) {
    return;
  }

  map->bucket_count = bucket_count;
  map->key_size = key_size;
  map->value_size = value_size;
  map->hash_fn = hash_fn;
  map->cmp_fn = cmp_fn;
  map->size = 0;
}

void hashmap_destroy(HashMap* map) {
  if (map == NULL) {
    return;
  }

  for (size_t i = 0; i < map->bucket_count; i++) {
    HashNode* node = map->buckets[i];

    while (node != NULL) {
      HashNode* tmp = node;
      node = node->next;

      free(tmp->key);
      free(tmp->value);
      free(tmp);
    }
  }

  free(map->buckets);
  map->buckets = NULL;
  map->bucket_count = 0;
  map->size = 0;
}

bool hashmap_insert(HashMap* map, void* key, const void* data) {
  if (map == NULL || key == NULL || data == NULL) {
    return false;
  }

  unsigned long hash_value = map->hash_fn(key) % map->bucket_count;
  HashNode* current = map->buckets[hash_value];

  while (current != NULL) {
    if (map->cmp_fn(current->key, key) == 0) {
      memcpy(current->value, data, map->value_size);
      return true;
    }

    current = current->next;
  }

  HashNode* new_node = create_node(map->key_size, map->value_size, key, data);
  if (new_node == NULL) {
    return false;
  }

  new_node->next = map->buckets[hash_value];
  map->buckets[hash_value] = new_node;
  map->size++;
  return true;
}

bool hashmap_remove(HashMap* map, void* key) {
  if (map == NULL || key == NULL) {
    return false;
  }

  unsigned long hash_value = map->hash_fn(key) % map->bucket_count;
  HashNode* current = map->buckets[hash_value];
  HashNode* prev = NULL;

  while (current != NULL) {
    if (map->cmp_fn(current->key, key) == 0) {
      if (prev == NULL) {
        map->buckets[hash_value] = current->next;
      } else {
        prev->next = current->next;
      }

      free(current->key);
      free(current->value);
      free(current);
      map->size--;
      return true;
    }
    prev = current;
    current = current->next;
  }

  return false;
}

bool hashmap_update(HashMap* map, void* key, const void* new_value) {
  if (map == NULL || key == NULL || new_value == NULL) {
    return false;
  }

  unsigned long hash_value = map->hash_fn(key) % map->bucket_count;
  HashNode* current = map->buckets[hash_value];

  while (current != NULL) {
    if (map->cmp_fn(current->key, key) == 0) {
      memcpy(current->value, new_value, map->value_size);
      return true;
    }
    current = current->next;
  }

  return false;
}

void* hashmap_get(HashMap* map, void* key) {
  if (map == NULL || key == NULL) {
    return NULL;
  }

  unsigned long hash_value = map->hash_fn(key) % map->bucket_count;
  HashNode* current = map->buckets[hash_value];

  while (current != NULL) {
    if (map->cmp_fn(current->key, key) == 0) {
      return current->value;
    }
    current = current->next;
  }

  return NULL;
}

int hashmap_size(const HashMap* map) {
  if (map == NULL) {
    return -1;
  }

  return map->size;
}

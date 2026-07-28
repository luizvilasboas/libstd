#include "../../include/data_structures/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static VectorNode* create_vector_node(const void* data, size_t element_size) {
  if (data == NULL || element_size == 0) {
    return NULL;
  }

  VectorNode* node = (VectorNode*)malloc(sizeof(VectorNode));
  if (node == NULL) {
    return NULL;
  }

  node->data = malloc(element_size);
  if (node->data == NULL) {
    free(node);
    return NULL;
  }

  memcpy(node->data, data, element_size);
  node->next = NULL;

  return node;
}

void vector_init(Vector* vector, size_t element_size) {
  if (vector == NULL || element_size == 0) {
    return;
  }

  vector->head = NULL;
  vector->element_size = element_size;
  vector->size = 0;
}

void vector_destroy(Vector* vector) {
  if (vector == NULL) {
    return;
  }

  VectorNode* current = vector->head;
  VectorNode* next;

  while (current != NULL) {
    next = current->next;

    free(current->data);
    free(current);

    current = next;
  }

  vector->head = NULL;
  vector->size = 0;
  vector->element_size = 0;
}

bool vector_insert(Vector* vector, const void* data) {
  if (vector == NULL || data == NULL) {
    return false;
  }

  VectorNode* new_node = create_vector_node(data, vector->element_size);
  if (new_node == NULL) {
    return false;
  }

  new_node->next = vector->head;
  vector->head = new_node;
  vector->size++;

  return true;
}

bool vector_remove(Vector* vector, size_t index) {
  if (vector == NULL || index >= vector->size) {
    return false;
  }

  VectorNode* current = vector->head;
  VectorNode* previous = NULL;

  if (index == 0) {
    vector->head = current->next;
    free(current->data);
    free(current);
  } else {
    for (size_t i = 0; i < index; i++) {
      previous = current;
      current = current->next;
    }

    if (current == NULL) {
      return false;
    }

    previous->next = current->next;
    free(current->data);
    free(current);
  }

  vector->size--;
  return true;
}

bool vector_update(Vector* vector, size_t index, const void* new_data) {
  if (vector == NULL || new_data == NULL || index >= vector->size) {
    return false;
  }

  VectorNode* current = vector->head;

  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  if (current == NULL) {
    return false;
  }

  memcpy(current->data, new_data, vector->element_size);
  return true;
}

void* vector_get(Vector* vector, size_t index) {
  if (vector == NULL || index >= vector->size) {
    return NULL;
  }

  VectorNode* current = vector->head;

  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  return current ? current->data : NULL;
}

int vector_search(Vector* vector, int (*cmp_fn)(void*, void*), void* key) {
  if (vector == NULL || cmp_fn == NULL || key == NULL) {
    return -1;
  }

  VectorNode* current = vector->head;
  int position = 0;

  while (current != NULL) {
    if (cmp_fn(current->data, key) == 0) {
      return position;
    }

    current = current->next;
    position++;
  }

  return -1;
}

int vector_size(const Vector* vector) {
  if (vector == NULL) {
    return -1;
  }

  return vector->size;
}

bool vector_sort(Vector* vector, int (*cmp_fn)(void*, void*)) {
  if (vector == NULL || cmp_fn == NULL || vector->size < 2) {
    return false;
  }

  for (VectorNode* i = vector->head; i != NULL; i = i->next) {
    for (VectorNode* j = i->next; j != NULL; j = j->next) {
      if (cmp_fn(i->data, j->data) > 0) {
        void* temp = i->data;
        i->data = j->data;
        j->data = temp;
      }
    }
  }

  return true;
}

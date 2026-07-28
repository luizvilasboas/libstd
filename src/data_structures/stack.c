#include "../../include/data_structures/stack.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static StackNode* create_queue_node(const void* data, size_t element_size) {
  if (data == NULL || element_size == 0) {
    return NULL;
  }

  StackNode* node = (StackNode*)malloc(sizeof(StackNode));
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

void stack_init(Stack* stack, size_t element_size) {
  if (stack == NULL || element_size == 0) {
    return;
  }

  stack->top = NULL;
  stack->element_size = element_size;
  stack->size = 0;
}

void stack_destroy(Stack* stack) {
  if (stack == NULL) {
    return;
  }

  StackNode* current = stack->top;
  StackNode* next;

  while (current != NULL) {
    next = current->next;

    free(current->data);
    free(current);

    current = next;
  }

  stack->top = NULL;
  stack->size = 0;
  stack->element_size = 0;
}

bool stack_push(Stack* stack, const void* data) {
  if (stack == NULL || data == NULL) {
    return false;
  }

  StackNode* new_node = create_queue_node(data, stack->element_size);
  if (new_node == NULL) {
    return false;
  }

  new_node->next = stack->top;
  stack->top = new_node;
  stack->size++;
  return true;
}

bool stack_pop(Stack* stack) {
  if (stack == NULL || stack->top == NULL) {
    return false;
  }

  StackNode* top_node = stack->top;

  stack->top = top_node->next;
  free(top_node->data);
  free(top_node);
  stack->size--;
  return true;
}

void* stack_top(Stack* stack) {
  if (stack == NULL) {
    return NULL;
  }

  return stack->top->data;
}

int stack_search(Stack* stack, int (*cmp_fn)(void*, void*), void* key) {
  if (stack == NULL || cmp_fn == NULL || key == NULL) {
    return -1;
  }

  StackNode* current = stack->top;
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

int stack_size(const Stack* stack) {
  if (stack == NULL) {
    return -1;
  }

  return stack->size;
}

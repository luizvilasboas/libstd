#include "../../include/data_structures/queue.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static QueueNode* create_queue_node(const void* data, size_t element_size) {
  if (data == NULL || element_size == 0) {
    return NULL;
  }

  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
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

void queue_init(Queue* queue, size_t element_size) {
  if (queue == NULL || element_size == 0) {
    return;
  }

  queue->front = NULL;
  queue->back = NULL;
  queue->element_size = element_size;
  queue->size = 0;
}

void queue_destroy(Queue* queue) {
  if (queue == NULL) {
    return;
  }

  QueueNode* current = queue->front;
  QueueNode* next;

  while (current != NULL) {
    next = current->next;

    free(current->data);
    free(current);
    current = next;
  }

  queue->front = NULL;
  queue->back = NULL;
  queue->size = 0;
  queue->element_size = 0;
}

bool queue_push(Queue* queue, const void* data) {
  if (queue == NULL || data == NULL) {
    return false;
  }

  QueueNode* new_node = create_queue_node(data, queue->element_size);
  if (new_node == NULL) {
    return false;
  }

  if (queue->size == 0) {
    queue->front = new_node;
    queue->back = new_node;
  } else {
    queue->back->next = new_node;
    queue->back = new_node;
  }

  queue->size++;
  return true;
}

bool queue_pop(Queue* queue) {
  if (queue == NULL || queue->size == 0) {
    return false;
  }

  QueueNode* temp = queue->front;
  queue->front = queue->front->next;

  if (queue->front == NULL) {
    queue->back = NULL;
  }

  free(temp->data);
  free(temp);
  queue->size--;
  return true;
}

void* queue_front(Queue* queue) {
  if (queue == NULL) {
    return NULL;
  }

  return queue->front->data;
}

void* queue_back(Queue* queue) {
  if (queue == NULL) {
    return NULL;
  }

  return queue->back->data;
}

int queue_search(Queue* queue, int (*cmp_fn)(void*, void*), void* key) {
  if (queue == NULL || cmp_fn == NULL || key == NULL) {
    return -1;
  }

  QueueNode* current = queue->front;
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

int queue_size(const Queue* queue) {
  if (queue == NULL) {
    return -1;
  }

  return queue->size;
}

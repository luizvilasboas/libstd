#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Node structure representing an element in the queue.
 */
typedef struct QueueNode {
  void* data;             /**< Pointer to the stored element data. */
  struct QueueNode* next; /**< Pointer to the next node in the queue. */
} QueueNode;

/**
 * @brief Structure representing a generic linked-list-based Queue.
 */
typedef struct {
  QueueNode* front;    /**< Pointer to the front node (removal point). */
  QueueNode* back;     /**< Pointer to the back node (insertion point). */
  size_t element_size; /**< Memory size (in bytes) of each stored element. */
  size_t size;         /**< Total number of elements currently in the queue. */
} Queue;

/**
 * @brief Initializes an empty Queue.
 *
 * @param queue Pointer to the `Queue` structure to initialize.
 * @param element_size Size of each element in bytes.
 */
void queue_init(Queue* queue, size_t element_size);

/**
 * @brief Destroys the Queue and frees all allocated nodes and their associated
 * data.
 *
 * @param queue Pointer to the `Queue` to destroy.
 */
void queue_destroy(Queue* queue);

/**
 * @brief Enqueues (pushes) a new element to the back of the queue.
 *
 * @param queue Pointer to the `Queue`.
 * @param data Pointer to the element data to insert.
 * @return `true` if insertion was successful, or `false` on memory allocation
 * failure.
 */
bool queue_push(Queue* queue, const void* data);

/**
 * @brief Dequeues (removes) the element at the front of the queue.
 *
 * @param queue Pointer to the `Queue`.
 * @return `true` if an element was successfully removed, or `false` if the
 * queue was empty.
 */
bool queue_pop(Queue* queue);

/**
 * @brief Accesses the element at the front of the queue without removing it.
 *
 * @param queue Pointer to the `Queue`.
 * @return Pointer to the data at the front of the queue, or NULL if the queue
 * is empty.
 */
void* queue_front(Queue* queue);

/**
 * @brief Accesses the element at the back of the queue without removing it.
 *
 * @param queue Pointer to the `Queue`.
 * @return Pointer to the data at the back of the queue, or NULL if the queue is
 * empty.
 */
void* queue_back(Queue* queue);

/**
 * @brief Searches for an element in the queue using a comparison function.
 *
 * @param queue Pointer to the `Queue`.
 * @param cmp_fn Pointer to the comparison function (should return 0 when
 * elements match).
 * @param key Pointer to the value/key being searched for.
 * @return The zero-based index of the element if found, or -1 if not found.
 */
int queue_search(Queue* queue, int (*cmp_fn)(void*, void*), void* key);

/**
 * @brief Retrieves the total number of elements currently stored in the queue.
 *
 * @param queue Pointer to the `Queue`.
 * @return Total number of elements.
 */
int queue_size(const Queue* queue);

#endif  // QUEUE_H_

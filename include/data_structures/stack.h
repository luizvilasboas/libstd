#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Node structure representing an element in the stack.
 */
typedef struct StackNode {
  void* data;             /**< Pointer to the stored element data. */
  struct StackNode* next; /**< Pointer to the next node lower in the stack. */
} StackNode;

/**
 * @brief Structure representing a generic linked-list-based Stack.
 */
typedef struct {
  StackNode* top; /**< Pointer to the top node (push/pop insertion point). */
  size_t element_size; /**< Memory size (in bytes) of each stored element. */
  size_t size;         /**< Total number of elements currently on the stack. */
} Stack;

/**
 * @brief Initializes an empty Stack.
 *
 * @param stack Pointer to the `Stack` structure to initialize.
 * @param element_size Size of each element in bytes.
 */
void stack_init(Stack* stack, size_t element_size);

/**
 * @brief Destroys the Stack and frees all allocated nodes and their associated
 * data.
 *
 * @param stack Pointer to the `Stack` to destroy.
 */
void stack_destroy(Stack* stack);

/**
 * @brief Pushes a new element onto the top of the stack.
 *
 * @param stack Pointer to the `Stack`.
 * @param data Pointer to the element data to insert.
 * @return `true` if insertion was successful, or `false` on memory allocation
 * failure.
 */
bool stack_push(Stack* stack, const void* data);

/**
 * @brief Pops (removes) the top element from the stack.
 *
 * @param stack Pointer to the `Stack`.
 * @return `true` if an element was successfully removed, or `false` if the
 * stack was empty.
 */
bool stack_pop(Stack* stack);

/**
 * @brief Accesses the top element of the stack without removing it.
 *
 * @param stack Pointer to the `Stack`.
 * @return Pointer to the data at the top of the stack, or NULL if the stack is
 * empty.
 */
void* stack_top(Stack* stack);

/**
 * @brief Searches for an element in the stack using a comparison function.
 *
 * @param stack Pointer to the `Stack`.
 * @param cmp_fn Pointer to the comparison function (should return 0 when
 * elements match).
 * @param key Pointer to the value/key being searched for.
 * @return The 1-based distance from the top of the stack if found (where 1 is
 * top), or -1 if not found.
 */
int stack_search(Stack* stack, int (*cmp_fn)(void*, void*), void* key);

/**
 * @brief Retrieves the total number of elements currently stored on the stack.
 *
 * @param stack Pointer to the `Stack`.
 * @return Total number of elements.
 */
int stack_size(const Stack* stack);

#endif  // STACK_H_

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Node structure representing an element in the vector.
 */
typedef struct VectorNode {
  void* data;              /**< Pointer to the stored element data. */
  struct VectorNode* next; /**< Pointer to the next node in the sequence. */
} VectorNode;

/**
 * @brief Structure representing a generic linked-list-backed Vector.
 */
typedef struct Vector {
  VectorNode* head;    /**< Pointer to the head (first) node of the vector. */
  size_t element_size; /**< Memory size (in bytes) of each stored element. */
  size_t size;         /**< Total number of elements currently in the vector. */
} Vector;

/**
 * @brief Initializes an empty Vector.
 *
 * @param vector Pointer to the `Vector` structure to initialize.
 * @param element_size Size of each element in bytes.
 */
void vector_init(Vector* vector, size_t element_size);

/**
 * @brief Destroys the Vector and frees all allocated nodes and their associated
 * data.
 *
 * @param vector Pointer to the `Vector` to destroy.
 */
void vector_destroy(Vector* vector);

/**
 * @brief Appends (inserts) a new element to the end of the vector.
 *
 * @param vector Pointer to the `Vector`.
 * @param data Pointer to the element data to insert.
 * @return `true` if insertion was successful, or `false` on memory allocation
 * failure.
 */
bool vector_insert(Vector* vector, const void* data);

/**
 * @brief Removes an element at a specific index from the vector.
 *
 * @param vector Pointer to the `Vector`.
 * @param index Zero-based position of the element to remove.
 * @return `true` if the element was successfully removed, or `false` if index
 * is out of bounds.
 */
bool vector_remove(Vector* vector, size_t index);

/**
 * @brief Updates the element data at a specific index in the vector.
 *
 * @param vector Pointer to the `Vector`.
 * @param index Zero-based position of the element to update.
 * @param new_data Pointer to the new data to be copied into the vector.
 * @return `true` if the element was successfully updated, or `false` if index
 * is out of bounds.
 */
bool vector_update(Vector* vector, size_t index, const void* new_data);

/**
 * @brief Retrieves a pointer to the element at a specific index.
 *
 * @param vector Pointer to the `Vector`.
 * @param index Zero-based position of the element to retrieve.
 * @return Pointer to the stored data, or NULL if index is out of bounds.
 */
void* vector_get(Vector* vector, size_t index);

/**
 * @brief Searches for an element in the vector using a custom comparison
 * function.
 *
 * @param vector Pointer to the `Vector`.
 * @param cmp_fn Pointer to the comparison function (should return 0 when
 * elements match).
 * @param key Pointer to the value/key being searched for.
 * @return Zero-based index of the element if found, or -1 if not found.
 */
int vector_search(Vector* vector, int (*cmp_fn)(void*, void*), void* key);

/**
 * @brief Retrieves the total number of elements currently stored in the vector.
 *
 * @param vector Pointer to the `Vector`.
 * @return Total number of elements.
 */
int vector_size(const Vector* vector);

/**
 * @brief Sorts the elements in the vector using a comparison function.
 *
 * @param vector Pointer to the `Vector`.
 * @param cmp_fn Pointer to the comparison function defining the sort order
 *               (e.g., returns < 0 if a < b, 0 if a == b, > 0 if a > b).
 * @return `true` if sorting succeeded, or `false` if the operation failed.
 */
bool vector_sort(Vector* vector, int (*cmp_fn)(void*, void*));

#endif  // VECTOR_H_

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Node structure representing a key-value pair in a hash bucket's
 * collision chain.
 */
typedef struct HashNode {
  void* key;   /**< Pointer to the stored key data. */
  void* value; /**< Pointer to the stored value data. */
  struct HashNode*
      next; /**< Pointer to the next node in the linked list (chaining). */
} HashNode;

/**
 * @brief Structure representing a generic Hash Map.
 */
typedef struct {
  HashNode** buckets;  /**< Array of pointers to bucket head nodes. */
  size_t bucket_count; /**< Number of buckets available in the hash table. */
  size_t key_size;     /**< Memory size (in bytes) of individual keys. */
  size_t value_size;   /**< Memory size (in bytes) of individual values. */
  size_t size;         /**< Total number of key-value pairs currently stored. */
  unsigned long (*hash_fn)(
      void*); /**< Function pointer to compute the hash code for a key. */
  int (*cmp_fn)(void*, void*); /**< Function pointer to compare two keys
                                  (returns 0 if equal). */
} HashMap;

/**
 * @brief Initializes a Hash Map structure.
 *
 * @param map Pointer to the `HashMap` structure to initialize.
 * @param bucket_count Initial number of buckets to allocate.
 * @param key_size Size of the key data in bytes.
 * @param value_size Size of the value data in bytes.
 * @param hash_fn Pointer to the hash function for keys.
 * @param cmp_fn Pointer to the key comparison function (should return 0 when
 * keys match).
 */
void hashmap_init(HashMap* map, size_t bucket_count, size_t key_size,
                  size_t value_size, unsigned long (*hash_fn)(void*),
                  int (*cmp_fn)(void*, void*));

/**
 * @brief Destroys the Hash Map and frees all allocated buckets, nodes, and
 * stored data.
 *
 * @param map Pointer to the `HashMap` to destroy.
 */
void hashmap_destroy(HashMap* map);

/**
 * @brief Inserts a new key-value pair into the Hash Map.
 *
 * @param map Pointer to the `HashMap`.
 * @param key Pointer to the key to insert.
 * @param data Pointer to the value associated with the key.
 * @return `true` if the insertion was successful, or `false` on memory
 * allocation failure or duplicate entry depending on implementation behavior.
 */
bool hashmap_insert(HashMap* map, void* key, const void* data);

/**
 * @brief Removes a key-value pair from the Hash Map by key.
 *
 * @param map Pointer to the `HashMap`.
 * @param key Pointer to the key to remove.
 * @return `true` if the key was found and removed, `false` otherwise.
 */
bool hashmap_remove(HashMap* map, void* key);

/**
 * @brief Updates the value associated with an existing key in the Hash Map.
 *
 * @param map Pointer to the `HashMap`.
 * @param key Pointer to the key whose value should be updated.
 * @param new_data Pointer to the new value data.
 * @return `true` if the key was found and updated, `false` if the key does not
 * exist.
 */
bool hashmap_update(HashMap* map, void* key, const void* new_data);

/**
 * @brief Retrieves the value associated with a given key.
 *
 * @param map Pointer to the `HashMap`.
 * @param key Pointer to the key to search for.
 * @return Pointer to the stored value data if found, or NULL if the key does
 * not exist.
 */
void* hashmap_get(HashMap* map, void* key);

/**
 * @brief Retrieves the total number of key-value pairs stored in the Hash Map.
 *
 * @param map Pointer to the `HashMap`.
 * @return Total number of items stored.
 */
int hashmap_size(const HashMap* map);

#endif  // HASHMAP_H_

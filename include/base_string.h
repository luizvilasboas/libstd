#ifndef BASE_STRING_H_
#define BASE_STRING_H_

#include <stddef.h>

/**
 * @brief Structure representing a dynamic string with capacity tracking.
 */
typedef struct {
  char* data;  /**< Pointer to the null-terminated character buffer. */
  size_t size; /**< Current length of the string (excluding the null
                  terminator). */
  size_t
      capacity; /**< Total allocated memory capacity for the buffer in bytes. */
} string;

/**
 * @brief Creates and initializes a new `string` instance.
 *
 * @param initial Null-terminated initial C-string. If NULL, an empty string is
 * created.
 * @return Pointer to the newly allocated `string`, or NULL on allocation
 * failure.
 * @note The returned pointer must be freed using `string_destroy()`.
 */
string* string_create(const char* initial);

/**
 * @brief Destroys a `string` instance and frees its allocated memory.
 *
 * @param str Pointer to the `string` to destroy. If NULL, no action is taken.
 */
void string_destroy(string* str);

/**
 * @brief Retrieves the current length of the string.
 *
 * @param str Pointer to the `string`.
 * @return The number of characters in the string (excluding the null
 * terminator).
 */
size_t string_length(const string* str);

/**
 * @brief Retrieves the current capacity of the string buffer.
 *
 * @param str Pointer to the `string`.
 * @return The total buffer capacity in bytes.
 */
size_t string_capacity(const string* str);

/**
 * @brief Appends a C-string to the end of the existing `string`.
 *
 * @param str Pointer to the destination `string`.
 * @param suffix Null-terminated C-string to append.
 */
void string_concat(string* str, const char* suffix);

/**
 * @brief Lexicographically compares two `string` instances.
 *
 * @param str_1 Pointer to the first `string`.
 * @param str_2 Pointer to the second `string`.
 * @return An integer less than, equal to, or greater than zero if `str_1` is
 * found, respectively, to be less than, to match, or be greater than `str_2`.
 */
int string_compare(const string* str_1, const string* str_2);

/**
 * @brief Clears the contents of the string, resetting its size to 0 without
 * reallocating memory.
 *
 * @param str Pointer to the `string` to clear.
 */
void string_clear(string* str);

/**
 * @brief Returns a pointer to the internal C-style null-terminated string.
 *
 * @param str Pointer to the `string`.
 * @return Pointer to the underlying character array.
 * @warning The returned pointer points directly to the structure's internal
 * buffer. Do not attempt to free or directly modify this memory.
 */
char* string_to_c(const string* str);

/**
 * @brief Ensures that the string buffer has at least the specified capacity.
 *
 * @param str Pointer to the `string`.
 * @param new_capacity Minimum required capacity in bytes.
 */
void string_reserve(string* str, size_t new_capacity);

/**
 * @brief Overwrites the current content of the `string` with a new value.
 *
 * @param str Pointer to the `string` to modify.
 * @param new_value Null-terminated C-string to set as the new content.
 */
void string_set(string* str, const char* new_value);

/**
 * @brief Checks if the string contains a specific substring.
 *
 * @param str Pointer to the `string` to search in.
 * @param substring Null-terminated C-string to search for.
 * @return 1 if the substring is found, 0 otherwise.
 */
int string_contains(const string* str, const char* substring);

/**
 * @brief Splits the string into an array of tokens using a specified delimiter.
 *
 * @param str Pointer to the `string` to split.
 * @param delimiter Null-terminated C-string used as the delimiter.
 * @param num_tokens Pointer to a `size_t` where the count of created tokens
 * will be stored.
 * @return Pointer to an array of dynamic `string*` tokens, or NULL on failure.
 * @note Each element in the array must be destroyed individually using
 * `string_destroy()`, and the returned array pointer itself must be released
 * using `free()`.
 */
string** string_split(const string* str, const char* delimiter,
                      size_t* num_tokens);

/**
 * @brief Replaces all occurrences of a target substring with a new substring.
 *
 * @param str Pointer to the `string` to modify.
 * @param old_substring Substring to be replaced.
 * @param new_substring Substring to insert in place of `old_substring`.
 */
void string_replace(string* str, const char* old_substring,
                    const char* new_substring);

#endif  // BASE_STRING_H_

#include "../include/base_string.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

string* string_create(const char* initial) {
  string* str = (string*)malloc(sizeof(string));
  if (str == NULL) {
    return NULL;
  }

  size_t initial_length = initial ? strlen(initial) : 0;
  str->capacity = initial_length + 1;
  str->size = initial_length;
  str->data = (char*)malloc(str->capacity * sizeof(char));

  if (initial) {
    strcpy(str->data, initial);
  } else {
    str->data[0] = '\0';
  }

  return str;
}

void string_destroy(string* str) {
  if (str != NULL) {
    free(str->data);
    free(str);
  }
}

size_t string_length(const string* str) { return str ? str->size : 0; }

size_t string_capacity(const string* str) { return str ? str->capacity : 0; }

void string_concat(string* str, const char* suffix) {
  if (str == NULL || suffix == NULL) {
    return;
  }

  size_t suffix_len = strlen(suffix);
  size_t new_size = str->size + suffix_len;

  if (new_size + 1 > str->capacity) {
    string_reserve(str, new_size + 1);
  }

  strcat(str->data, suffix);
  str->size = new_size;
}

int string_compare(const string* str_1, const string* str_2) {
  if (str_1 == NULL || str_2 == NULL) {
    return -1;
  }

  return strcmp(str_1->data, str_2->data);
}

void string_clear(string* str) {
  if (str != NULL) {
    str->size = 0;
    str->data[0] = '\0';
  }
}

char* string_to_c(const string* str) { return str->data; }

void string_reserve(string* str, size_t new_capacity) {
  if (str == NULL || new_capacity <= str->capacity) {
    return;
  }

  char* new_data = (char*)realloc(str->data, new_capacity * sizeof(char));
  if (new_data == NULL) {
    return;
  }

  str->data = new_data;
  str->capacity = new_capacity;
}

void string_set(string* str, const char* new_value) {
  if (str == NULL || new_value == NULL) {
    return;
  }

  size_t new_length = strlen(new_value);
  if (new_length + 1 > str->capacity) {
    string_reserve(str, new_length + 1);
  }

  strcpy(str->data, new_value);
  str->size = new_length;
}

int string_contains(const string* str, const char* substring) {
  if (str == NULL || substring == NULL) {
    return 0;
  }

  return strstr(str->data, substring) != NULL;
}

string** string_split(const string* str, const char* delimiter,
                      size_t* num_tokens) {
  if (num_tokens == NULL) {
    return NULL;
  }

  *num_tokens = 0;
  if (str == NULL || delimiter == NULL) {
    return NULL;
  }

  size_t capacity = 10;
  string** tokens = malloc(capacity * sizeof(string*));
  if (tokens == NULL) {
    *num_tokens = 0;
    return NULL;
  }

  char* copy = strdup(str->data);
  char* token = strtok(copy, delimiter);
  size_t count = 0;

  while (token != NULL) {
    if (count >= capacity) {
      capacity *= 2;
      string** tmp = realloc(tokens, capacity * sizeof(string*));
      if (tmp == NULL) {
        for (size_t i = 0; i < count; i++) {
          string_destroy(tokens[i]);
        }
        free(tokens);
        *num_tokens = 0;
        return NULL;
      }
      tokens = tmp;
    }

    tokens[count] = string_create(token);
    count++;
    token = strtok(NULL, delimiter);
  }

  *num_tokens = count;
  free(copy);
  return tokens;
}

void string_replace(string* str, const char* old_substring,
                    const char* new_substring) {
  if (str == NULL || old_substring == NULL || new_substring == NULL) {
    return;
  }

  char* pos = strstr(str->data, old_substring);
  if (pos == NULL) {
    return;
  }

  size_t old_len = strlen(old_substring);
  size_t new_len = strlen(new_substring);
  size_t diff_len = new_len - old_len;
  size_t new_size = str->size + diff_len;

  if (new_size + 1 > str->capacity) {
    string_reserve(str, new_size + 1);
  }

  memmove(pos + new_len, pos + old_len,
          str->size - (pos - str->data) - old_len + 1);

  memcpy(pos, new_substring, new_len);

  str->size = new_size;
}

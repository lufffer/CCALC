#include "str.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String *newString(char *str, size_t n) {
  String *string = malloc(sizeof(String));
  string->length = n == 0 ? strlen(str) : n;
  string->available = string->length * 2 + 1;
  string->data = malloc(string->available);
  if (string->data == NULL) {
    return NULL;
  }
  if (n == 0) {
    strcpy(string->data, str);
  } else {
    strncpy(string->data, str, n);
  }

  return string;
}

void appendString(String *string, char *str) {
  size_t length = strlen(str);
  bool reallocate = false;

  while (length + string->length > string->available) {
    string->available *= 2;
    reallocate = true;
  }

  if (reallocate) {
    char *aux = string->data;
    string->data = realloc(string->data, string->available + 1);
    if (string->data == NULL) {
      string->data = aux;
    }
  }

  strcat(string->data, str);
  string->length += length;
}

void appendStringN(String *string, char *str, size_t n) {
  size_t length = strlen(str);
  bool reallocate = false;

  while (length + n > string->available) {
    string->available = string->available * 2 + 1;
    reallocate = true;
  }

  if (reallocate) {
    char *aux = string->data;
    string->data = realloc(string->data, string->available + 1);
    if (string->data == NULL) {
      string->data = aux;
    }
  }

  strncat(string->data, str, n);
  string->length += length;
}

void deleteString(String *string) {
  free(string->data);
  free(string);
}

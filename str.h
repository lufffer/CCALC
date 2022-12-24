#ifndef STR_H
#define STR_H

#include <stddef.h>

typedef struct String {
  size_t length;
  size_t available;
  char *data;
} String;

String *newString(char *str, size_t n);

void appendString(String *string, char *str);

void appendStringN(String *string, char *str, size_t n);

void deleteString(String *string);

#endif

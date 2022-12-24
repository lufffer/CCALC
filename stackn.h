#ifndef STACKN_H
#define STACKN_H

#include <stdbool.h>
#include <stddef.h>

typedef struct StackNoden {
  struct StackNoden *next;
  double number;
} StackNoden;

typedef struct Stackn {
  size_t length;
  struct StackNoden *top;
} Stackn;

Stackn *newStackn(void);

bool emptyStackn(Stackn *stack);

size_t sizeStackn(Stackn *stack);

double *topStackn(Stackn *stack);

void pushStackn(Stackn *stack, double number);

void popStackn(Stackn *stack);

void swapStackn(Stackn **a, Stackn **b);

void deleteStackn(Stackn *stack);

#endif // !DEBUG

#include "stackn.h"

#include <stdlib.h>
#include <string.h>

static StackNoden *newStackNoden(Stackn *stack, double number) {
  StackNoden *stackNode = malloc(sizeof(StackNoden));
  if (stackNode == NULL) {
    return NULL;
  }

  stackNode->number = number;
  stackNode->next = NULL;

  return stackNode;
}

Stackn *newStackn(void) {
  Stackn *stack = malloc(sizeof(Stackn));
  if (stack == NULL) {
    return NULL;
  }

  stack->length = 0;
  stack->top = NULL;

  return stack;
}

bool emptyStackn(Stackn *stack) { return stack->length == 0; }

size_t sizeStackn(Stackn *stack) { return stack->length; }

double *topStackn(Stackn *stack) { return &(stack->top->number); }

void pushStackn(Stackn *stack, double number) {
  StackNoden *stackNode = newStackNoden(stack, number);
  stackNode->next = stack->top;
  stack->top = stackNode;
  stack->length++;
}

void popStackn(Stackn *stack) {
  StackNoden *aux = stack->top;
  stack->top = aux->next;
  aux->next = NULL;
  free(aux);
  if (emptyStackn(stack)) {
    return;
  }
  stack->length--;
}

void swapStackn(Stackn **a, Stackn **b) {
  Stackn *aux = *a;
  *a = *b;
  *b = aux;
}

void deleteStackn(Stackn *stack) {
  while (!emptyStackn(stack)) {
    popStackn(stack);
  }

  free(stack);
}

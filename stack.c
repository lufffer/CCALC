#include "stack.h"

#include <stdlib.h>
#include <string.h>

static StackNode *newStackNode(Stack *stack, Symbols symbol) {
  StackNode *stackNode = malloc(sizeof(StackNode));
  if (stackNode == NULL) {
    return NULL;
  }

  stackNode->symbol = symbol;
  stackNode->next = NULL;

  return stackNode;
}

Stack *newStack(void) {
  Stack *stack = malloc(sizeof(Stack));
  if (stack == NULL) {
    return NULL;
  }

  stack->length = 0;
  stack->top = NULL;

  return stack;
}

bool emptyStack(Stack *stack) { return stack->length == 0; }

size_t sizeStack(Stack *stack) { return stack->length; }

Symbols *topStack(Stack *stack) { return &(stack->top->symbol); }

void pushStack(Stack *stack, Symbols symbol) {
  StackNode *stackNode = newStackNode(stack, symbol);
  stackNode->next = stack->top;
  stack->top = stackNode;
  stack->length++;
}

void popStack(Stack *stack) {
  StackNode *aux = stack->top;
  stack->top = aux->next;
  aux->next = NULL;
  free(aux);
  if (emptyStack(stack)) {
    return;
  }
  stack->length--;
}

void swapStack(Stack **a, Stack **b) {
  Stack *aux = *a;
  *a = *b;
  *b = aux;
}

void deleteStack(Stack *stack) {
  while (!emptyStack(stack)) {
    popStack(stack);
  }

  free(stack);
}

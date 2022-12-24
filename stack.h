#ifndef STACK_H
#define STACK_H

#include "calculatorSymbols.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct StackNode {
  struct StackNode *next;
  Symbols symbol;
} StackNode;

typedef struct Stack {
  size_t length;
  struct StackNode *top;
} Stack;

Stack *newStack(void);

bool emptyStack(Stack *stack);

size_t sizeStack(Stack *stack);

Symbols *topStack(Stack *stack);

void pushStack(Stack *stack, Symbols symbol);

void popStack(Stack *stack);

void swapStack(Stack **a, Stack **b);

void deleteStack(Stack *stack);

#endif // !DEBUG

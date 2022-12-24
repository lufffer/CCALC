#include "calculator.h"
#include "calculatorSymbols.h"
#include "queue.h"
#include "stack.h"
#include "stackn.h"
#include "str.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static double add(double a, double b) { return a + b; }

static double substract(double a, double b) { return a - b; }

static double multiply(double a, double b) { return a * b; }

static double divide(double a, double b) {
  if (b == 0) {
    puts("Cannot divide by zero");
    exit(EXIT_FAILURE);
  }
  return a / b;
}

static double module(double a, double b) { return fmod(a, b); }

static double min(double a, double b) { return a <= b ? a : b; }

static double max(double a, double b) { return a >= b ? a : b; }

static double unaryMinus(double a) { return -a; }

static double factorial(double a) {
  if (a < 0) {
    puts("Factorial does not exist");
  }
  return a == 0 || a == 1 ? 1 : a * factorial(a - 1);
}

Symbols symbols[] = {
    {'l', 2, OPERATOR, "+", NULL, add},
    {'l', 2, OPERATOR, "-", NULL, substract},
    {'l', 3, OPERATOR, "*", NULL, multiply},
    {'l', 3, OPERATOR, "/", NULL, divide},
    {'l', 3, OPERATOR, "%", NULL, module},
    {'r', 4, OPERATOR, "^", NULL, pow},
    {'n', 0, FUNCTION, "min", NULL, min},
    {'n', 0, FUNCTION, "max", NULL, max},
    {'n', 0, FUNCTION, "sin", sin, NULL},
    {'n', 0, FUNCTION, "cos", cos, NULL},
    {'n', 0, FUNCTION, "tan", tan, NULL},
    {'n', 0, FUNCTION, "log", log, NULL},
    {'n', 0, FUNCTION, "ln", log10, NULL},
    {'n', 0, FUNCTION, "sqrt", sqrt, NULL},
    {'n', 0, FUNCTION, "?", unaryMinus, NULL},
    {'n', 0, FUNCTION, "!", factorial, NULL},
    {'n', 0, OPENBRACKET, "(", NULL, NULL},
    {'n', 0, OPENBRACKET, "[", NULL, NULL},
    {'n', 0, OPENBRACKET, "{", NULL, NULL},
    {'n', 0, CLOSEBRACKET, "}", NULL, NULL},
    {'n', 0, CLOSEBRACKET, "]", NULL, NULL},
    {'n', 0, CLOSEBRACKET, ")", NULL, NULL},
    {'n', 0, CONSTANT, "pi", NULL, NULL},
    {'n', 0, CONSTANT, "e", NULL, NULL},
};
size_t symbolsLength = sizeof symbols / sizeof(Symbols);

char *replaceMinus(char *exp) {
  size_t length = strlen(exp);
  char *newExp = malloc(sizeof(char) * length + sizeof(char));
  if (newExp == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < length; ++i) {
    newExp[i] =
        (i == 0 && exp[i] == '-') || (!isdigit(exp[i - 1]) && exp[i] == '-')
            ? '?'
            : exp[i];
  }
  newExp[length] = '\0';

  return newExp;
}

// Static functions
static Symbols getNum(char *exp, size_t *i, size_t length) {
  if (isdigit(exp[*i])) {
    String *number = newString(exp + *i, 0);
    bool obteined = false;

    if (number->length > 0) {
      while (!obteined && (isdigit(exp[*i + 1]) || exp[*i + 1] == '.')) {
        appendStringN(number, exp + *i + 1, 1);
        (*i)++;
        if (*i >= length - 1) {
          obteined = true;
        }
      }
    }
    char *aux = number->data;
    free(number);
    return (Symbols){'n', 0, CONSTANT, aux, NULL, NULL};
  }
  return (Symbols){'n', 0, NONE, NULL, NULL, NULL};
}

static Symbols getSymbol(char *exp, size_t *i) {
  for (size_t j = 0; j < symbolsLength; ++j) {
    size_t expLength = strlen(exp + *i);
    size_t symbolLength = strlen(symbols[j].name);
    if (strncmp(exp + *i, symbols[j].name,
                expLength > symbolLength ? symbolLength : expLength) == 0) {
      *i += strlen(symbols[j].name) - 1;
      return symbols[j];
    }
  }
  return (Symbols){'n', 0, NONE, "", NULL, NULL};
}

static Symbols classification(char *exp, size_t *i, size_t length) {
  Symbols symbol = getNum(exp, i, length);
  if (symbol.type == CONSTANT) {
    return symbol;
  }
  free(symbol.name);

  return getSymbol(exp, i);
}

static void shunting_yard(Symbols symbol, Queue *queue, Stack *stack) {
  Symbols *top = topStack(stack);
  switch (symbol.type) {
  case CONSTANT:
    pushQueue(queue, symbol);
    break;
  case OPERATOR:
    if (sizeStack(stack) != 0) {
      while (top->type == FUNCTION || top->precedence > symbol.precedence ||
             top->precedence == symbol.precedence && top->asociation == 'l') {
        pushQueue(queue, *topStack(stack));
        popStack(stack);
        if (stack->length == 0) {
          break;
        }
        top = topStack(stack);
      }
    }
    pushStack(stack, symbol);
    break;
  case FUNCTION:
    pushStack(stack, symbol);
    break;
  case OPENBRACKET:
    symbol.name = "(";
    pushStack(stack, symbol);
    break;
  case CLOSEBRACKET:
    while (strcmp(top->name, "(") != 0) {
      pushQueue(queue, *topStack(stack));
      popStack(stack);
      top = topStack(stack);
    }
    popStack(stack);
    break;
  case NONE:
    break;
  }
}

Queue *rpn(char *exp) {
  Queue *queue = newQueue();
  Stack *stack = newStack();

  for (size_t i = 0, length = strlen(exp); i < length; ++i) {
    char token = exp[i];
    if (token == ' ' || token == ',') {
      continue;
    }

    Symbols symbol;
    if (i < length) {
      symbol = classification(exp, &i, length);
    }

    shunting_yard(symbol, queue, stack);
  }

  while (!emptyStack(stack)) {
    pushQueue(queue, *topStack(stack));
    popStack(stack);
  }

  deleteStack(stack);
  return queue;
}

double evaluate(Queue *parsed) {
  Stackn *stack = newStackn();

  while (!emptyQueue(parsed)) {
    if (frontQueue(parsed)->type == CONSTANT) {
      if (strcmp(frontQueue(parsed)->name, "pi") == 0) {
        pushStackn(stack, M_PI);
      } else if (strcmp(frontQueue(parsed)->name, "e") == 0) {
        pushStackn(stack, M_E);
      } else {
        pushStackn(stack, atof(frontQueue(parsed)->name));
        free(frontQueue(parsed)->name);
      }
    } else if (frontQueue(parsed)->unary != NULL) {
      double a = *topStackn(stack);
      popStackn(stack);
      pushStackn(stack, frontQueue(parsed)->unary(a));
    } else {
      double b = *topStackn(stack);
      popStackn(stack);
      double a = *topStackn(stack);
      popStackn(stack);
      pushStackn(stack, frontQueue(parsed)->binary(a, b));
    }
    popQueue(parsed);
  }
  deleteQueue(parsed);
  double aux = *topStackn(stack);
  deleteStackn(stack);
  return aux;
}

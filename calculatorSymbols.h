#ifndef CALCULATOR_SYMBOLS_H
#define CALCULATOR_SYMBOLS_H

typedef enum TYPE {
  CONSTANT,
  FUNCTION,
  OPERATOR,
  OPENBRACKET,
  CLOSEBRACKET,
  NONE
} TYPE;

typedef struct Symbols Symbols;

struct Symbols {
  char asociation;
  int precedence;
  TYPE type;
  char *name;
  double (*unary)(double a);
  double (*binary)(double a, double b);
};

#endif

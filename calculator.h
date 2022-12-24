#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "queue.h"

char *replaceMinus(char *exp);

Queue *rpn(char *exp);

double evaluate(Queue *parsed);

#endif

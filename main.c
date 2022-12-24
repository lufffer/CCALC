#include "calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    return 0;
  } else if (argc > 2) {
    puts("Too many arguments\n\n Usage: ./calc \"exp\"");
    return 0;
  } 
  char *exp = argv[1];
  exp = replaceMinus(exp);
  Queue *parsed = rpn(exp);
  free(exp);

  double res = evaluate(parsed);
  printf("res: %f\n", res);

  return 0;
}

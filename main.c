#include "calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *exp = "e * pi";
  exp = replaceMinus(exp);
  Queue *parsed = rpn(exp);
  free(exp);

  double res = evaluate(parsed);
  printf("res: %f\n", res);

  return 0;
}

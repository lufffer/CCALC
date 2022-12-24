# CCALC

A scientific calculator super easy to extend

## HOW TO EXTEND

Just follow the pattern in symbol variable (calculator.c) and add the desire
symbol, then create a new static function for that symbol (static functions are
also inside caculator.c) and that's it.

PD: The function should return a double.

PD2: This program was tested with valgrind, it has no memory leaks nor errors

## BUILD

`gcc -lm main.c calculator.c stack.c stackn.c str.c queue.c -o calc`

## USAGE

./calc "exp".

### Example

./calc "(5+6)\*2 + sin(pi)"

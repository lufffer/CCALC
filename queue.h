#ifndef QUEUE_H
#define QUEUE_H

#include "calculatorSymbols.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct QueueNode {
  struct QueueNode *next;
  Symbols symbol;
} QueueNode;

typedef struct Queue {
  size_t length;
  struct QueueNode *first;
  struct QueueNode *last;
} Queue;

Queue *newQueue(void);

bool emptyQueue(Queue *queue);

size_t sizeQueue(Queue *queue);

Symbols *frontQueue(Queue *queue);

Symbols *backQueue(Queue *queue);

void pushQueue(Queue *queue, Symbols symbol);

void popQueue(Queue *queue);

void swapQueue(Queue **a, Queue **b);

void deleteQueue(Queue *queue);

#endif // !QUEUE_H

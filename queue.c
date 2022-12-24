#include "queue.h"

#include <stdlib.h>
#include <string.h>

static QueueNode *newQueueNode(Queue *queue, Symbols symbol) {
  QueueNode *queueNode = malloc(sizeof(QueueNode));
  if (queueNode == NULL) {
    return NULL;
  }

  queueNode->symbol = symbol;
  queueNode->next = NULL;

  return queueNode;
}

Queue *newQueue(void) {
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    return NULL;
  }

  queue->length = 0;
  queue->first = NULL;
  queue->last = NULL;

  return queue;
}

bool emptyQueue(Queue *queue) { return queue->length == 0; }

size_t sizeQueue(Queue *queue) { return queue->length; }

Symbols *frontQueue(Queue *queue) { return &(queue->first->symbol); }

Symbols *backQueue(Queue *queue) { return &(queue->last->symbol); }

void pushQueue(Queue *queue, Symbols symbol) {
  QueueNode *queueNode = newQueueNode(queue, symbol);
  if (emptyQueue(queue)) {
    queue->first = queueNode;
  }
  queueNode->next = queue->last;
  queue->last = queueNode;
  queue->length++;
}

void popQueue(Queue *queue) {
  QueueNode *ptr = queue->last;
  if (queue->last != queue->first) {
    while (ptr->next != queue->first) {
      ptr = ptr->next;
    }
    queue->first = ptr;
    free(ptr->next);
    ptr->next = NULL;
  } else {
    free(queue->first);
    queue->first = queue->last = NULL;
  }

  queue->length--;
}

void swapQueue(Queue **a, Queue **b) {
  Queue *aux = *a;
  *a = *b;
  *b = aux;
}

void deleteQueue(Queue *queue) {
  while (!emptyQueue(queue)) {
    popQueue(queue);
  }

  free(queue);
}

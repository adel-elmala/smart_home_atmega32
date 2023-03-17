#ifndef QUEUE_H
#define QUEUE_H
#include "../Datatypes.h"

// #define QUEUE_MAX_SIZE 64
#define QUEUE_ERROR_EMPTY 14
#define QUEUE_ERROR_FULL 15
#define QUEUE_MAX_SIZE 256

typedef struct Queue_Circular
{
    uint16 queue_buffer[QUEUE_MAX_SIZE];
    uint16 rd_idx;
    uint16 wt_idx;
    uint16 capacity;
} Queue_Circular_t;

void q_init(Queue_Circular_t *q);
bool q_enqueue(Queue_Circular_t *q, uint16 data);
uint16 q_dequeue(Queue_Circular_t *q);
uint16 q_peek(Queue_Circular_t *q);
bool q_isEmpty(Queue_Circular_t *q);
bool q_isFull(Queue_Circular_t *q);

#endif
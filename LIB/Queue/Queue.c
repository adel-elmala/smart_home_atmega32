#include "Queue.h"
// typedef struct Queue_Circular
// {
//     uint8 queue_buffer[QUEUE_MAX_SIZE];
//     uint8 rd_idx;
//     uint8 wt_idx;
//     uint8 capacity;
//
// } Queue_Circular_t;
void q_init(Queue_Circular_t *q)
{
    q->capacity = 0;
    q->rd_idx = 0;
    q->wt_idx = 0;
}
void incr_index(uint16 *idx)
{
    uint16 tmp = (*idx) + 1;
    if (tmp == QUEUE_MAX_SIZE)
        *idx = 0;
    else
        *idx = tmp;
}
void decr_index(uint16 *idx) // not used
{
    uint16 tmp = (*idx) - 1;
    if (tmp == 255) // -1
        *idx = QUEUE_MAX_SIZE - 1;
    else
        *idx = tmp;
}
bool q_enqueue(Queue_Circular_t *q, uint16 data)
{
    if (q_isFull(q))
        return QUEUE_ERROR_FULL;
    else
    {
        q->queue_buffer[q->wt_idx] = data;
        incr_index(&(q->wt_idx));
        (q->capacity)++;
    }
    return true;
}
uint16 q_dequeue(Queue_Circular_t *q)
{
    if (q_isEmpty(q))
        return QUEUE_ERROR_EMPTY;
    else
    {
        uint16 fetched_data = q->queue_buffer[q->rd_idx];
        incr_index(&(q->rd_idx));
        (q->capacity)--;
        return fetched_data;
    }
}
uint16 q_peek(Queue_Circular_t *q)
{
    return q->queue_buffer[0];
}
bool q_isEmpty(Queue_Circular_t *q)
{
    if ((q->capacity == 0) && ((q->wt_idx) == (q->rd_idx)))
        return true;
    else
        return false;
}

bool q_isFull(Queue_Circular_t *q)
{
    if ((q->capacity == (QUEUE_MAX_SIZE)) && ((q->wt_idx) == (q->rd_idx)))
        return true;
    else
        return false;
}
#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
    size_t semaphoreCount;
    queue_t waiting_Queue;
};

sem_t sem_create(size_t count)
{
    // creates the semaphore
    struct semaphore *s = malloc(sizeof(struct semaphore));

    // returns null if the semaphore is NULL
    if (s == NULL){
        return NULL;
    }

    // initializes the semaphore internal count and creates the waiting thread
    s->semaphoreCount = count;
    s->waiting_Queue = queue_create();

    // returns null if the queue is null for the semaphore
    if(s->waiting_Queue == NULL){
        free(s);
        return NULL;
    }
    
    return s;
}

int sem_destroy(sem_t sem)
{
    // if the semaphore or waiting thread is null, return -1
    if(sem == NULL || sem->waiting_Queue != NULL){
        return -1;
    }

    // destroys the waiting thread and deallocate the semaphore
    queue_destroy(sem->waiting_Queue);
    free(sem);
    return 0;
}

int sem_down(sem_t sem)
{
    // checks if the semaphore is NULL
    if (sem == NULL){
        return -1;
    }

    struct uthread_tcb *current = uthread_current();

    /*if the count or resources is 0, then put the current
    thread into the waiting queue and block it*/
    while(sem->semaphoreCount == 0){
        queue_enqueue(sem->waiting_Queue, current);
        uthread_block();
    }

    //decrements the internal count of the semaphore
    sem->semaphoreCount--;
    return 0;
}

int sem_up(sem_t sem)
{
    //if the semaphore is NULL, return -1
    if (sem == NULL){
        return -1;
    }

    //increments the internal count of the semaphore
    sem->semaphoreCount++;

    // if the waiting list is not empty, will unblock the oldest thread
    if(queue_length(sem->waiting_Queue) > 0){
        struct uthread_tcb *oldest_thread;

        // removes the oldest thread from the queue and unblocks it
        queue_dequeue(sem->waiting_Queue, (void**)&oldest_thread);
        uthread_unblock(oldest_thread);
    }

    return 0;
}

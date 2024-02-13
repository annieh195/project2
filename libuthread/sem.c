#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
    /* TODO Phase 3 */
    int semaphoreCount;
    queue_t waiting_Queue;
};

sem_t sem_create(size_t count)
{
    /* TODO Phase 3 */
    struct semaphore *s = malloc(sizeof(struct semaphore));

    if (s == NULL){
        return NULL;
    }
    s->semaphoreCount = count;
    s->waiting_Queue = queue_create();

    
    
    return s;
}

int sem_destroy(sem_t sem)
{
    /* TODO Phase 3 */
    if(sem == NULL || sem->waiting_Queue != NULL){
        return -1;
    }

    queue_destroy(sem->waiting_Queue);
    free(sem);
    return 0;
}

int sem_down(sem_t sem)
{
    if (sem == NULL){
        return -1;
    }

    struct uthread_tcb *current = uthread_current();
    if(sem->semaphoreCount == 0){
        queue_enqueue(sem->waiting_Queue, current);
        uthread_block();
    }
    sem->semaphoreCount--;
    return 0;
    /* TODO Phase 3 */
}

int sem_up(sem_t sem)
{
    /* TODO Phase 3 */

    if (sem == NULL){
        return -1;
    }

    
    if(queue_length(sem->waiting_Queue) > 0){
        struct uthread_tcb *oldest_thread;
        queue_dequeue(sem->waiting_Queue, (void**)&oldest_thread);
        uthread_unblock(oldest_thread);
    }
    sem->semaphoreCount++;

    return 0;

}

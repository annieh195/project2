#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

static struct uthread_tcb *current_thread = NULL;
static queue_t ready;
typedef enum { READY, RUN, BLOCK, ZOMBIE } state_t;

struct uthread_tcb
{
	/* TODO Phase 2 */
	void *stack;
	state_t state;
	uthread_ctx_t context;
};

struct uthread_tcb *uthread_current(void)
{
	return current_thread;
}

void uthread_yield(void)
{
    /* TODO Phase 2 */\
	preempt_disable();
    struct uthread_tcb *previous_thread = current_thread;
    if (queue_dequeue(ready, (void **)&current_thread) == 0)
    {
        if (previous_thread->state == READY)
        {
            queue_enqueue(ready, previous_thread);
        }
        uthread_ctx_switch(&previous_thread->context, &current_thread->context);
    }
	preempt_enable();
}

void uthread_exit(void)
{
	current_thread->state = ZOMBIE;
	free(current_thread->stack);
	free(current_thread);
	uthread_yield();
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	preempt_disable();
	struct uthread_tcb *new_thread = malloc(sizeof(struct uthread_tcb));
	if (new_thread == NULL)
	{
		return -1;
	}

	new_thread->stack = uthread_ctx_alloc_stack();
	if (new_thread->stack == NULL)
	{
		free(new_thread);
		return -1;
	}

	uthread_ctx_init(&new_thread->context, new_thread->stack, func, arg);
	new_thread->state = READY;
	queue_enqueue(ready, new_thread);
	preempt_enable();
	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	//(void)preempt;
	preempt_start(preempt);
	ready = queue_create();
	if (ready == NULL)
	{
		return -1;
	}

	current_thread = malloc(sizeof(struct uthread_tcb));
	if (current_thread == NULL)
	{
		queue_destroy(ready);
		return -1;
	}

	current_thread->stack = uthread_ctx_alloc_stack();
	if (current_thread->stack == NULL)
	{
		free(current_thread);
		queue_destroy(ready);
		return -1;
	}

	uthread_ctx_init(&current_thread->context, current_thread->stack, func, arg);
	current_thread->state = RUN;
	uthread_create(func, arg); //
	preempt_enable();
	while (1)
	{
		if (queue_length(ready) == 0 && current_thread->state == ZOMBIE)
		{
			break;
		}
		uthread_yield();
	}
	preempt_disable();
	
	if (preempt == true) {
        preempt_stop();
  	}
	queue_destroy(ready);
	free(current_thread->stack);
	free(current_thread);
	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 3 */
	if (current_thread != NULL)
	{
		current_thread->state = BLOCK;
		uthread_yield();
	}
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 3 */
	if (uthread != NULL && uthread->state == BLOCK)
	{
		uthread->state = READY;
		queue_enqueue(ready, uthread);
	}
}

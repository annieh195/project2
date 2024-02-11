#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct node
{
	void *data;
	struct node *next;
};

struct queue
{
	/* TODO Phase 1 */
	node_t *head;
	node_t *tail;
	int size;
};

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	queue_t queue = malloc(sizeof(struct queue));
	if (queue == NULL)
	{
		return NULL;
	}

	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;

	return queue;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	if (queue == NULL || queue->size != 0)
	{
		return -1;
	}

	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (queue == NULL || data == NULL)
	{
		return -1;
	}
	node_t *node_next = malloc(sizeof(node_t));
	if (node_next == NULL)
	{
		return -1;
	}
	node_next->data = data;
	node_next->next = NULL;

	if (queue->head == NULL)
	{
		queue->tail = node_next;
	}
	else
	{
		queue->tail->next = node_next;
	}
	queue->head = node_next;

	queue->size++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	if (queue == NULL || data == NULL || queue->size == 0)
	{
		return -1;
	}

	*data = queue->head->data;
	node_t *temp = queue->head;
	queue->head = queue->head->next;

	if (queue->head == NULL)
	{
		queue->tail = NULL;
	}

	free(temp);
	queue->size--;
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (queue == NULL || data == NULL)
	{
		return -1;
	}

	node_t *current = queue->head;
	node_t *previous = NULL;

	while (current != NULL)
	{
		if (current->data == data)
		{
			if (previous == NULL)
			{
				queue->head = current->next;
			}
			else
			{
				previous->next = current->next;
			}

			if (current == queue->tail)
			{
				queue->tail = previous;
			}

			free(current);
			queue->size--;
			return 0;
		}

		previous = current;
		current = current->next;
	}

	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
	if (queue == NULL || func == NULL)
	{
		return -1;
	}

	node_t *current = queue->head;
	for (; current != NULL; current = current->next)
	{
		func(queue, current->data);
	}

	return 0;
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	if (queue == NULL)
	{
		return -1;
	}

	return queue->size;
}
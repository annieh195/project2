#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node node_t;
struct node
{
	void *data;
	struct node *next;
};

struct queue
{
	node_t *head;
	node_t *tail;
	int size;
};

queue_t queue_create(void)
{
	/* Allocates memory:
		- If fail, return null
		- If success, set head and tail pointers to null (queue empty size=0) */
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
	/* Check if there is no queue or queue not empty, return error */
	if (queue == NULL || queue->size > 0)
	{
		return -1;
	}

	free(queue); // free memory if there is queue but empty
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* Check if there is no queue or invalid data, return error */
	if (queue == NULL || data == NULL)
	{
		return -1;
	}
	
	node_t *node_next = malloc(sizeof(node_t));
	/* Check if malloc successfully allocated memory */
	if (node_next != NULL)
	{
		node_next->data = data;
		node_next->next = NULL;
	}

	/* if queue empty, set head and tail pointers to node_next */
	if (queue->head == NULL && queue->tail == NULL)
	{
		queue->head = queue->tail = node_next;
	}
	/* or set next pointer of tail node to node_next
		and then update tail pointer to node_next make it last node */
	else
	{
		queue->tail->next = node_next;
		queue->tail = node_next;
	}

	queue->size++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* Check if there is no queue/ invalid data/ queue no node, return error */
	if (queue == NULL || data == NULL || queue->size == 0)
	{
		return -1;
	}

	/* Set node to dequeue and data to dequeue node data */
	node_t *current = queue->head;
	*data = current->data;

	/* update head */
	queue->head = current->next;
	if (queue->head == NULL) // incase afrer dequeue, queue is empty
	{
		queue->tail = NULL;
	}

	free(current);
	queue->size--;
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* Check if there is no queue or invalid data, return error */
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
			if (previous == NULL) // check if this is head node
			{
				queue->head = current->next; // Update head
				if (queue->head == NULL)
				{
					queue->tail = NULL; // Queue is empty
				}
			}
			else
			{
				previous->next = current->next; // Bypass the curret node
			}

			free(current);
			queue->size--;
			return 0;
		}

		// Update pointers' position
		previous = current;
		current = current->next;
	}
	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* Check if there is no queue or invalid func, return error */
	if (queue == NULL || func == NULL)
	{
		return -1;
	}

	node_t *current = queue->head;
	node_t *next = current->next;
	for (; current != NULL; current = next)
	{
		next = current->next;
		func(queue, current->data);
	}
	return 0;
}

int queue_length(queue_t queue)
{
	if (queue == NULL)
	{
		return -1;
	}

	return queue->size;
}
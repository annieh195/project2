#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

/*empty queue test*/
void test_queue_empty(void){

    queue_t q;
    fprintf(stderr, "*** TEST queue_empty ***\n");

    q = queue_create();
    int length = queue_length(q);

    TEST_ASSERT(length == 0);


}

void test_queue_length(void){
	queue_t q;
	fprintf(stderr, "*** TEST queue_length ***\n");

	q = queue_create();
	int data[] = {1, 2, 3, 4, 5};

	for(unsigned int i = 0; i < sizeof(data) / sizeof(data[0]); i++){
		queue_enqueue(q, &data[i]);
	}

	int length = queue_length(q);
	TEST_ASSERT(length == 5);
}

void test_queue_enqueue_null(void){
	queue_t q;
	fprintf(stderr, "*** TEST queue_enqueue_data ***\n");
	int *data = NULL;
	q = queue_create();
	TEST_ASSERT(queue_enqueue(q, data) == -1);
}

void test_queue_dequeue_null(void){
	queue_t q;
	fprintf(stderr, "*** TEST queue_enqueue_dequeue_data ***\n");
	int *ptr = NULL;
	q = queue_create();
	TEST_ASSERT(queue_dequeue(q, (void**)&ptr) == -1);
}




void test_queue_delete(void){
    queue_t q;
    fprintf(stderr, " TEST queue_delete \n");
    q = queue_create();

    int dataset[] = {1, 2, 3, 4, 5, 6, 7, 8};

    for(unsigned int i = 0; i < sizeof(dataset) / sizeof(dataset[0]); i++){
        queue_enqueue(q, &dataset[i]);
    }

    int *element = &dataset[6];
	TEST_ASSERT(queue_length(q) == 8);
    int test = queue_delete(q, element);
    TEST_ASSERT(test == 0);
	TEST_ASSERT(queue_length(q) == 7);
}

/* Callback function that increments items */
static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;
	fprintf(stderr, "*** TEST queue_iterator ***\n");
    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);
}

/*simple queue destroy tester*/
void test_queue_destroy(void){
	queue_t q;
	queue_t q2;
	fprintf(stderr, "*** TEST queue_destroy ***\n");
	
	q = queue_create();
	q2 = queue_create();

	TEST_ASSERT(queue_destroy(q) == 0);

	int data[] = {1, 2, 3, 4, 5};
	size_t i;
	for (i = 0; i < sizeof(data) / sizeof(data[0]); i++){
        queue_enqueue(q2, &data[i]);
	
	}

	TEST_ASSERT(queue_destroy(q2) == -1);

}


int main(void)
{
	test_create();
	test_queue_simple();
	test_queue_length();
	test_queue_enqueue_null();
	test_queue_empty();
	test_queue_destroy();
	test_queue_dequeue_null();
	test_queue_delete();
	test_iterator();

	return 0;
}

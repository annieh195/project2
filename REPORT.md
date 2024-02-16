# Project #2 - User-level Thread Library

## Summary

# Phase 1 `queue API`
### Datastructures
In this phase, we used Single Linked List to implement the queue. 
- We defined `node struct` that represents a queue node, containing user 
data and a pointer to the next node.
- `queue struct` that represents a queue, containing pointers to head and tail,
and tracking the size of the queue.
### Functions
- `queue_create`:
    - First, we allocate memory for `queue_t` using `malloc`. 
    - We check if the allocation was successful. If not, return `NULL`. 
    - We initialize head and tail pointers to `NULL`, indicating the queue 
    is empty. Also, set size to 0. 
- `queue_destroy`: 
    - First, we check if the `queue` is `NULL` or is not empty (size > 0). If 
    so, return `error`.
    - We use `free` to deallocate the memory for the queue.
- `queue_enqueue`: 
    - First, we check if the `queue` or `data` are `NULL`. If so, return `error`
    - Allocate memory for `node_t` using `malloc`.
    - We check if the allocation was successful, then assign the `data` to the 
    next node and set its next pointer to `NULL`.
    - We check if the `queue` is empty, set both head and tail to the next node.
    - But if the `queue` is not empty, set current tail node's next pointer to
    the next node and then update the tail pointer to the next node.
    - Lastly, we increase the `size of the queue`.
- `queue_dequeue`: 
    - First, we check if the `queue` or `data` are `NULL`, or `queue` is empty 
    (size = 0). If any is true, return error.
    - Set a current pointer to the head node.
    - Update `data` to point to the data of the head node.
    - Move the head pointer to the next node in the queue.
    - If the queue becomes empty (head is `NULL`), also set tail to `NULL`.
    - We use `free` to deallocate the memory of the dequeued node.
    - Lastly, we decrease the `size of the queue`.
- `queue_delete`: 
    - First, we check if the `queue` or `data` are `NULL`. If so, return `error`
    - We iterate through the `queue` to find the node with the matching `data`.
    - Adjust the pointers of previous and next node to bypass the found node.
    - After, we use `free` to deallocate the memory of the found node, decrease 
    the size.
    - We update previous node's pointer to point to current node also update
    current node's pointer to point to next node.
- `queue_iterate`: 
    - First, we check if the `queue` or `func` are `NULL`. If so, return `error`
    - Iterate over each node in the queue.
    - Apply the `func` to each node's `data`.
- `queue_length`: 
    - First, we check if the `queue` is `NULL`. If so, return `error`.
    - Then, return the `size of the queue`.

# Phase 2
`state_t` enum represents 4 states of a thread in the thread library.
`uthread_tcb struct` contains a stack pointer (`void *stack`), `state_t state`,
and thread context.
### Functions
- `uthread_current`: We return the currently running thread.
- `uthread_yield`: Switches from the current thread to the next ready thread.
    - First, we create a pointer `previous_thread` point to `current_thread`.
    - Dequeuing the next thread from the `ready queue` and assign it to 
    `current_thread`. If the dequeue is successful, then:
        > We check if the thread is still ready, we enqueue it back.
        > We switch context to new current thread using `uthread_ctx_switch()`.
- `uthread_exit`: Called when a thread finishes its execution.
    - First, we set the thread's state to `ZOMBIE`.
    - We use `free` to deallocate its stack and the thread control block (TCB).
    - Lastly, we yield to the next thread.
- `uthread_create`: Creates a new thread.
    - First, we allocate memory for a new TCB using `malloc` and check if it is 
    `NULL`, we return `error`.
    - We allocate a stack for the new thread using `uthread_ctx_alloc_stack()`
    and check if it is `NULL`, then `free` it and return `error`.
    - We initialize the thread context with `uthread_ctx_init()`.
    - We set the thread's state to `READY`.
    - Lastly, we enqueue the new thread into the `ready queue`.
- `uthread_run`: Starts the threading system.
    - First, we create the `ready queue` and check if `NULL`, return `error`.
    - Then, we set up the current thread (similar to creating a new thread).
    - And then, We run the current thread until all threads are done.
    - Lastly, we use `free` to deallocate its stack and the thread control block
# Phase 3
- `uthread_block`: Block the current thread.
    - First, we check if `current thread` is not `NULL`. 
    - If so, we set thread's state to `BLOCK` and then yield to the next thread.
- `uthread_unblock`: Unblock a previously blocked thread.
    - First, we check if the `thread` is not `NULL` and in `BLOCK` state.
    - If so, we change its state to `READY`.
    - Lastly, we re-enqueue it into the `ready queue`.
# Phase 4

# Resources

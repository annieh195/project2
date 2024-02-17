# Project #2 - User-level Thread Library
## Summary

# Phase 1 `queue API`
### Data Structures
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
# Phase 2 `uthread API`
`state_t` enum represents 4 states of a thread in the thread library.
`uthread_tcb struct` contains a stack pointer (`void *stack`), `state_t state`,
and thread `context`.
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
# Phase 3 `semaphore API`
- `uthread_block`: Block the current thread.
    - First, we check if `current thread` is not `NULL`. 
    - If so, we set thread's state to `BLOCK` and then yield to the next thread.
- `uthread_unblock`: Unblock a previously blocked thread.
    - First, we check if the `thread` is not `NULL` and in `BLOCK` state.
    - If so, we change its state to `READY`.
    - Lastly, we re-enqueue it into the `ready queue`.
- `sem_create`
  - First, we allocate memory for a new semaphore utilizing `malloc`.
  - Afterwords, we check to see if it is `NULL`.
  - Then, we initialized the semaphore internal count and create the waiting
    thread.
  - After initializing the variables of the semaphore, we check to see if the
    the waiting thread to see if it is `NULL`.
    - If it is NULL, then we deallocate the semaphore.   
- `sem_destroy`
  - First, we need check to see if the semaphore is `NULL` or if the waiting
    queue of threads is `NULL`.
  - Afterwards, we destroy the waiting queue utilizing `queue_destroy()` and
    deallocate the semaphore.   
- `sem_down`
  - First, we checked to see if the semaphore `NULL`.
  - Afterwards, we need to also check if the count or resource is `0`
    - If it is equal to `0`, then we place the current thread into the waiting
      queue and block it.
    - Otherwise, we decrement the internal count by `1`.
- `sem_up`
  - First, we checked to see if the semaphore `NULL`.
  - Then we increment the `semaphore` count by `1`.
  - When approaching on how the semaphore releases a resource, first we checked
    to see if the waiting queue is not empty
    - If it is not empty, we take the oldest thread and `dequeue` from
      the waiting queue.
    - Lastly we unblock the thread.
# Phase 4 `preemption`
### Functions
- `signal_handler`
  - When checking for the alarm signal, it would make the thread `yield`.
- `preempt_disable`: Disables preemption.
  - First, we initialized a `sigset`.
  - Then we utilized `sigprocmask` to block `SIGVTALRM` to disable preemption.
- `preempt_enable`: Enables preemption.
  - First, we initialized a `sigset`.
  - Then we utilized `sigprocmask` to unblock `SIGVTALRM` to enable preemption.
- `preempt_start`: Start thread preemption.
  - First, we initialized the preempt Status to what the argument is.
  - Then we initialize a `sigaction` struct.
    - To handle `SIGVTALRM`, we call `signal_handler`.
    - Then we set up and utilized `sigaction()` to register `SIGVTALRM`
      and specified the action to be taken.
  - We also initialized `itimerval` structs to help set the timer and alarm.
    - Then we configured the timer to go off in `microseconds`.
  - **For the uthreads, we implemented `preempt_start` at the start of
    `uthread_run()`.**
- `preempt_stop`: Stops preemption.
  - First we utilized `sigaction` to restore the previous signal handling
  configuration.
  - Then we reverted the timer to its previous state.
  - **For the uthreads, we implemented `preempt_stop` before `uthread` returns.**
### Testing
# Resources

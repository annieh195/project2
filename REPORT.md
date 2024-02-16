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
    - We initialize `head` and `tail` pointers to `NULL`, indicating the queue 
    is empty. Also, set `size` to 0. 
- `queue_destroy`: 
    - First, we check if the `queue` is `NULL` or is `not empty` (`size`> 0). If 
    so, return `error`.
    - We use `free` to deallocate the memory for the queue.
- `queue_enqueue`: 
    - First, we check if the `queue` or `data` are `NULL`. If so, return `error`
    - Allocate memory for `node_t` using `malloc`.
    - We check if the allocation was successful, then assign the `data` to the 
    next node and set its `next` pointer to `NULL`.
    - We check if the `queue` is empty, set both head and tail to the next node.
    - But if the `queue` is not empty, set current tail node's `next` pointer to
    the next node and then update the `tail` pointer to the next node.
    - Lastly, we increase the `size` of the `queue`.
- `queue_dequeue`: 
    - First, we check if the `queue` or `data` are `NULL`, or `queue` is empty 
    (`size`= 0). If any is true, return error.
    - Set a `current` pointer to the head node.
    - Update `data` to point to the data of the head node.
    - Move the `head` pointer to the next node in the `queue`.
    - If the queue becomes empty (`head` is `NULL`), also set `tail` to `NULL`.
    - We use `free` to deallocate the memory of the dequeued node.
    - Lastly, we decrease the `size` of the `queue`.
- `queue_delete`: 
    - First, we check if the `queue` or `data` are `NULL`. If so, return error.
    - We iterate through the `queue` to find the node with the matching `data`.
    - Adjust the pointers of previous and next node to bypass the found node.
    - After, we use `free` to deallocate the memory of the found node, decrease 
    the size.
    - We update previous node's pointer to point to current node also update
    current node's pointer to point to next node.
- `queue_iterate`: 
    - First, we check if the `queue` or `func` are `NULL`. If so, return `error`
    - Iterate over each node in the `queue`.
    - Apply the `func` to each node's `data`.
- `queue_length`: 
    - First, we check if the `queue` is `NULL`. If so, return `error`.
    - Then, return the `size` of the `queue`.

# Phase 2

# Phase 3

# Phase 4

# Resources

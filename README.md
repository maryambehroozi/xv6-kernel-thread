# XV6 Threading and Scheduling Enhancement

This project focuses on enhancing the XV6 operating system by introducing kernel thread support, mutex locks for synchronization, and implementing a round-robin scheduling mechanism. The goal is to enable XV6 to support concurrent execution of kernel threads within a single process on multi-core systems, thereby improving the operating system's efficiency and multitasking capabilities.

## Features

- **Kernel Threads**: Introduce system calls (`clone`, `join`) to manage kernel threads, allowing a single process to execute multiple threads concurrently.
- **Mutex Locks**: Implement mutex locks (`lock_init`, `lock_acquire`, `lock_release`) to ensure thread safety and prevent race conditions in critical sections.
- **Round Robin Scheduling**: Modify the scheduler to adopt a round-robin approach, ensuring fair CPU time allocation among processes and threads.

## Development Notes

- **Memory Management**: Pay special attention to the allocation and deallocation of thread stacks.
- **Synchronization**: Implement and test lock mechanisms carefully to avoid deadlocks and race conditions.
- **Concurrency Control**: Ensure that the new scheduling mechanism and thread model do not introduce fairness issues.

## Challenges

- **Shared Memory Management**: Managing shared memory between threads to prevent conflicts.
- **Concurrency Control**: Implementing effective synchronization to handle race conditions.
- **Stack Management**: Dynamic allocation and deallocation of thread stacks while maintaining safety.

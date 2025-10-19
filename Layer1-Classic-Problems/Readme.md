This laboratory/layer 1 focused on understanding how operating systems manage processes, memory, CPU scheduling, and synchronization in a computing environment.

Process Management
A process refers to an independent program in execution, while a thread is a smaller unit that operates within a process and shares the same memory space. Processes are more isolated and resource-heavy, whereas threads are lighter but can affect the entire process if one fails. Processes transition through states — New, Ready, Running, Blocked, and Exit — during their execution.
For Inter-Process Communication (IPC), Pipes allow direct data transfer between processes, while Message Queues organize communication between multiple processes for better coordination.

Memory Management
Paging divides memory into fixed-size pages to improve efficiency, while Segmentation divides it into variable-sized logical parts for better organization. The Translation Lookaside Buffer (TLB) speeds up memory access by storing recent address translations. With a hit rate of 80%, the computed Effective Memory Access Time (EMAT) is 130 ns, demonstrating the impact of caching on performance.

CPU Scheduling
First-Come, First-Served (FCFS) executes processes based on arrival order, which is simple but can cause long waiting times. Round Robin (RR) uses time slices (quantums) to give each process fair CPU access. For the given example, the average waiting time under FCFS was 6.67 ms.

Synchronization
The Dining Philosophers, Producer-Consumer, and Reader-Writer problems illustrate issues in resource sharing such as deadlock, starvation, and data inconsistency. These are addressed using semaphores and monitors to control process access and maintain fairness and stability.


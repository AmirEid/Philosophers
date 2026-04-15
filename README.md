# Philosophers 🧠🍝

This project is part of the 42 curriculum and explores the classic **Dining Philosophers problem**, focusing on **concurrency, synchronization, threads, and processes**.

The goal is to simulate philosophers sitting at a table who alternate between:
- eating 🍝
- sleeping 😴
- thinking 🤔

Each philosopher must eat without causing deadlocks or race conditions, using proper synchronization mechanisms such as **mutexes (mandatory part)** and **process synchronization tools (bonus part)**.

Processes vs Threads
For simplicity, let’s think of a process as a “task” and a thread as a “small task” inside it.
During the core curriculum at 42 Firenze, the Philosophers project (especially the bonus part) was a real turning point in my learning journey.
A process is the starting point of everything running on a computer. In simple terms, it’s a program in execution—a task you give to the computer. It contains its own variables, data structures, and logic, and typically runs in a linear flow.
But what if you want to perform multiple actions at the same time using the same data and resources?
That’s where threads come in.
Inside a process, you can create multiple threads—think of them as “small jobs” within the same task. These threads share the same memory and resources of the main process, and each one executes its own part of the logic concurrently.
This shared access is powerful—but also dangerous.
If multiple threads try to access the same resource at the same time, problems can occur. Who gets access first? Who should wait?
This is where mutexes come into play. I like to think of them as a toilet with just one key 😄—they control access and ensure that only one thread uses a shared resource at a time.
Unlike processes, threads don’t have independent exit statuses. They execute their function, terminate, and the main process can wait for them to finish (e.g., using joins). Threads are lightweight because they share memory, which makes them faster—but also more complex to manage correctly.

Now comes the interesting part from the bonus section of Philosophers:
Instead of using threads, you can solve the same problem using multiple processes.
In this approach, you don’t just create one task with multiple small tasks—you create multiple independent tasks (processes, philosophers).
The key difference?
Processes do not share memory by default. Each process has its own separate address space and resources. In a way, processes are more “independent” than threads—they don’t like sharing 😄
So how do you coordinate them?
How does the main process know when another process has finished?
This is where concepts like exit statuses, signals, pipes, and semaphores come in.
When a process finishes, it exits with a status code that the parent process can read (for example, using wait or waitpid). This allows the parent process to understand whether the child succeeded, failed, or ended in a specific state.
Signals allow processes to communicate asynchronous events, such as termination requests or interruptions.
Pipes are a form of inter-process communication used to transfer data in a one-way stream between processes. Unlike signals or exit statuses, pipes are used to send actual data (for example, text or binary information) from one process to another.
Semaphores are used for synchronization. They control access to shared resources by allowing a limited number of processes to enter a critical section at the same time. In the Philosophers project, they are commonly used to coordinate access to shared resources like forks.

And that’s the key idea:
When you create multiple processes using fork(), each one gets its own copy of the parent’s data. These copies are independent and not shared.
To coordinate behavior, processes do not rely on shared variables but on operating system mechanisms such as semaphores, signals, or other forms of inter-process communication.
In the Philosophers bonus project, forks are not represented as shared variables in memory. Instead, they are modeled using semaphores, which control how many philosophers can access the resource at the same time.

Want to make it even more complex?
A main process can create other processes, and each of those processes can create its own threads. This combination of processes and threads is common in real-world systems.

Finally, a small note to myself (and anyone reading):
This code was written as part of a learning journey—it’s not optimized for production or meant to show off, but to deeply understand how things work.

---

## ⚙️ Compilation

Compile the mandatory version:

```bash
make

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

./philo 5 800 200 200 5
./philo_bonus 5 800 200 200 5



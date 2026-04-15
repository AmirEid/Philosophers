# Philosophers 🧠🍝

This project is part of the 42 curriculum and explores the classic **Dining Philosophers problem**, focusing on **concurrency, synchronization, threads, and processes**.

The goal is to simulate philosophers sitting at a table who alternate between:
- eating 🍝
- sleeping 😴
- thinking 🤔

Each philosopher must eat without causing deadlocks or race conditions, using proper synchronization mechanisms such as **mutexes (mandatory part)** and **process synchronization tools (bonus part)**.

---

## ⚙️ Compilation

Compile the mandatory version:

```bash
make

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

./philo 5 800 200 200 5
./philo_bonus 5 800 200 200 5

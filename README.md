# 🧠 Philosophers

A 42 School project that explores multithreading, mutexes, and synchronization by implementing the classic Dining Philosophers Problem in C.

## 📘 Project Description

This project is a simulation of the **Dining Philosophers Problem**, designed to deepen understanding of **concurrent programming**, **mutexes**, and **thread management** in C using the POSIX threads (pthreads) library.

Five philosophers sit at a round table, alternating between **thinking**, **eating**, and **sleeping**. Each needs two forks to eat, but there are only five forks total. The challenge is to ensure that the philosophers don’t starve or cause deadlocks.

## 🧪 Project Objectives

- Implement concurrent threads using `pthread`.
- Manage race conditions using mutexes.
- Prevent deadlocks and starvation.
- Comply with project rules: no data races, no memory leaks, and safe thread handling.

## ⚙️ Parameters

| Argument                                   | Description                                                  |
|--------------------------------------------|--------------------------------------------------------------|
| `number_of_philosophers`                   | Number of philosophers and forks                             |
| `time_to_die`                              | Time (in ms) a philosopher survives without eating           |
| `time_to_eat`                              | Time (in ms) a philosopher takes to eat                      |
| `time_to_sleep`                            | Time (in ms) a philosopher sleeps                            |
| `number_of_times_each_philosopher_must_eat` (optional) | Stop simulation when each philosopher has eaten this many times |

## ▶️ Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## 🧠 What I Learned

- Deepened understanding of low-level concurrency
- How to use pthread and semaphores correctly
- Handling synchronization, race conditions, and deadlocks
- The importance of timing precision in concurrent systems

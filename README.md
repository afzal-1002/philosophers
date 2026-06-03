*This project has been created as part of the 42 curriculum by mafzal.*

# Dining Philosophers

## Description

Classic concurrency problem: N philosophers sit at a round table, alternating between thinking, eating, and sleeping. Each philosopher needs two adjacent forks to eat. The simulation ends when a philosopher starves or all have eaten the required number of times. The goal is a deadlock-free, starvation-free implementation using POSIX threads and mutexes.

---

## Instructions

### Compilation

```bash
make        # build
make re     # rebuild
make fclean # remove binary and objects
```

### Execution

```bash
./philo <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required]
```

| Argument | Description |
|---|---|
| `num_philos` | Number of philosophers and forks |
| `time_to_die` (ms) | Time before a philosopher starves since last meal |
| `time_to_eat` (ms) | Duration of eating (holds 2 forks) |
| `time_to_sleep` (ms) | Duration of sleeping |
| `meals_required` (optional) | Stop when all philosophers reach this meal count |

### Test Cases

```bash
./philo 1 800 200 200      # philosopher dies (can't eat alone)
./philo 5 800 200 200      # no one dies
./philo 5 800 200 200 7    # stops after each eats 7 times
./philo 4 410 200 200      # no one dies
./philo 4 310 200 100      # one philosopher dies
```

---

## Synchronization Algorithm

**Even/Odd Fork Assignment** combined with a **dedicated monitor thread**.

- **Odd philosophers** pick up left fork first, then right.
- **Even philosophers** pick up right fork first, then left.

This breaks circular wait — the root cause of deadlock — without any extra mutexes.

A separate monitor thread watches `last_meal_time` for every philosopher. If `now - last_meal_time > time_to_die`, it sets `simulation_should_end` and prints the death message within 10ms.

**Why this approach:** Simple, deterministic, and requires no additional primitives beyond the fork mutexes. Separating death detection into its own thread keeps the philosopher loop clean.

---

## Resources

- POSIX Threads: https://man7.org/linux/man-pages/man7/pthreads.7.html
- Mutex API: https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
- Dijkstra, E. W. (1971). *Hierarchical ordering of sequential processes.* (Original formulation)

### AI Usage (Claude)

| Task | Usage |
|---|---|
| Architecture | Discussed deadlock prevention strategies and trade-offs |
| Debugging | Caught wrong fork message format (`"has taken a fork"` vs `"left/right fork"`) |
| Code review | Checked subject requirements, norminette, and test cases |
| Documentation | Structured and wrote this README |

All suggestions were reviewed and tested before use.

---

## Project Management

**Solo project** — mafzal (all design, implementation, testing, documentation).

### What Worked Well
- Even/odd fork assignment eliminated deadlocks immediately.
- Monitor as a separate thread kept philosopher logic simple.
- `precision_usleep` (500µs polling loop) kept death timing within 1ms.


### Tools Used
`gcc`, `norminette`, `valgrind`, `make`, `VSCode`

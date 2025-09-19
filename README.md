# Philosophers: Dining Philosophers Problem Solution

## 📋 Table of Contents

- [About](#about)
- [Problem Overview](#problem-overview)
- [Program Specifications](#program-specifications)
- [Installation & Usage](#installation--usage)
- [Algorithm Strategy](#algorithm-strategy)
- [Implementation Details](#implementation-details)
- [Testing & Validation](#testing--validation)
- [Makefile Targets](#makefile-targets)

## About

**Philosophers** is a solution to the classic Dining Philosophers problem, demonstrating synchronization in concurrent programming using threads and mutexes. This project implements a simulation where philosophers alternate between eating, thinking, and sleeping while avoiding deadlock and starvation.

## Problem Overview

The Dining Philosophers problem involves:
- **N philosophers** sitting at a round table
- **N forks** (one between each pair of philosophers)
- Each philosopher needs **two forks** to eat
- Philosophers must **avoid deadlock** (circular wait)
- Philosophers must **avoid starvation** (never getting to eat)

### Philosopher States
- **Eating**: Holding two forks, consuming spaghetti
- **Thinking**: Pondering philosophy
- **Sleeping**: Resting after eating
- **Dead**: Failed to eat within time limit

## Program Specifications

### Command Line Arguments
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

| Argument | Description | Units |
|----------|-------------|-------|
| `number_of_philosophers` | Number of philosophers/forks | integer |
| `time_to_die` | Max time without eating before death | milliseconds |
| `time_to_eat` | Time required to eat | milliseconds |
| `time_to_sleep` | Time spent sleeping | milliseconds |
| `number_of_meals` (optional) | Simulation stops after each philosopher eats this many times | integer |

### Output Format
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

### Requirements
- **No data races** or synchronization issues
- **Death detection** within 10ms of actual death
- **No message overlap** in output
- **No global variables**
- **Proper cleanup** of resources

## Installation & Usage

### Compilation
```bash
git clone https://github.com/viridian-green/Philosophers.git
cd philosophers
make
```

### Running the Simulation
```bash
# Basic simulation (stops when philosopher dies)
./philo 5 800 200 200

# Simulation with meal limit (stops after each eats 7 times)
./philo 5 800 200 200 7

# Single philosopher scenario (will die)
./philo 1 800 200 200
```

### Example Output
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating
```

## Algorithm Strategy

### Synchronization Approach
- **Mutex-protected forks**: Each fork has a mutex lock
- **Thread per philosopher**: Each philosopher runs in separate thread
- **Timing precision**: Microsecond accuracy using `gettimeofday()`
- **Death monitoring**: Separate thread or main thread checks status

### Deadlock Prevention
- **Asymmetric picking**: Odd/even philosophers pick forks in different order
- **Timeout mechanisms**: Prevent infinite waiting
- **Resource hierarchy**: Ordered fork acquisition

### Starvation Avoidance
- **Fair scheduling**: Ensure all philosophers get access to resources
- **Priority management**: Prevent philosopher monopolization
- **Efficient sleeping**: Proper usleep implementation with time checking

## Implementation Details

### Core Components

#### Thread Management
- **Philosopher threads**: Simulate philosopher behavior
- **Monitor thread**: Checks for deaths and meal completion
- **Mutex synchronization**: Protects shared resources

#### Meal Limit Testing
```bash
# Should stop after 7 meals each
./philo 3 800 200 200 7

# Verify all philosophers eat required meals
./philo 4 800 200 200 5 | grep "is eating" | wc -l
```

#### Edge Cases
```bash
# Large number of philosophers
./philo 200 800 200 200

# Very short times
./philo 5 100 50 50

# Very long simulation
./philo 5 10000 1000 1000
```

### Validation Criteria
- **No data races**: Use thread sanitizers or valgrind
- **Proper death timing**: Death within 10ms of starvation
- **No message overlap**: Clean, sequential output
- **Resource cleanup**: No memory leaks or mutex leaks
- **Correct meal counting**: Accurate tracking when meal goal specified

## Makefile Targets

```bash
make        # Compile philo executable
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Clean and recompile
```


## Dependencies

- **pthread**: POSIX threads library
- **Standard C Library**: malloc, free, printf, write, usleep, gettimeofday

## Common Issues & Solutions

### Deadlock Prevention
- Implement asymmetric fork picking strategy
- Use timeout mechanisms for fork acquisition
- Consider adding a "arbitrator" or "waiter" thread

### Performance Issues
- Avoid busy waiting with proper usleep
- Minimize mutex locking time
- Use efficient time calculation methods

### Race Conditions
- Protect all shared data with mutexes
- Use proper memory barriers
- Test with thread sanitizers

---

**Note**: This implementation focuses on solving the classic synchronization problem while meeting all specified requirements. The solution demonstrates proper thread management, mutex synchronization, and timing precision while avoiding common concurrency issues like deadlock and race conditions.

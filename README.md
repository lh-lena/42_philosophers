# philosophers
The Dining Philosophers problem written in C

The Philosophers project at 42 Berlin is an implementation of the classic synchronization problem known as the Dining Philosophers problem. 
</br></br>In this project, we have create a simulation where a certain number of philosophers sit around a table, alternating between **eating**, **sleeping** and **thinking**, using **thread** and **mutex**.

### Installing and running the project:
1. Clone the repository:
```C
    git clone git@github.com:lh-lena/philosopher.git
```
2. Navigate to the project directory:
```C
    cd philosopher/philo
```
3. Compile the project: 
```C
    make
```
4. Run the Philo: 
```C
    ./philo <nbr_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [nbr_of_times_each_philo_must_eat]
```
or
```C
    make run
```

# Some Examples:
* ./philo 1 800 200 200 - Philosopher should not eat and should die.
* ./philo 5 800 200 200 - No Philosopher should die.
* ./philo 5 800 200 200 7 - No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
* ./philo 4 410 200 200 - No Philosopher should die.
* ./philo 4 310 200 100 - One Philosopher should die.

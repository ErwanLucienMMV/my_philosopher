*his project has been created as part
of the 42 curriculum by emaigne*

# DESCRIPTION
Philosopher is a project that aims to teach us about thread, multithreading and how to avoid datarace (which is the moment when two threads are in a race for a data, and one can alter said data while the other is reading it through the usage of mutex)

One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.

• The philosophers take turns eating, thinking, and sleeping.

While they are eating, they are not thinking nor sleeping;

while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

• There are also forks on the table. There are as many forks as philosophers, each fork in this project is a mutex.

• Since eating spaghetti with just one fork is impractical, a philosopher must pick up
both the fork to their right and the fork to their left before eating, hence they should avoid fighting with their neigbhour for the holy fork.

• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation, we are allowed a delay of 10ms to identify one died.

• Every philosopher needs to eat and should never starve (if possible).

• Philosophers do not communicate with each other.

• Philosophers do not know if another philosopher is about to die.

• Needless to say, philosophers should avoid dying!

# INSTRUCTIONS

```
git clone https://github.com/ErwanLucienMMV/my_philosopher.git
```

then once in the folder
```
make

./philo <NumberOfPhilo> <TimeToDie> <TimeToEat> <TimeToSleep> [how many meals do they need to eat before ending the simulation]
```

# RESSOURCES

[Page manuel de GETTIMEOFDAY](http://manpagesfr.free.fr/man/man2/gettimeofday.2.html)

[Page manuel de pthread_create](http://manpagesfr.free.fr/man/man3/pthread_create.3.html)

[Page manuel de pthread_mutex_init](http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html)

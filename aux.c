#include "philo.h"

void print_data(t_data *data)
{
    printf("Philosopher Number: %d\n", data->ph_number);
    printf("Time to Die: %ld\n", data->tt_die);
    printf("Time to Eat: %ld\n", data->tt_eat);
    printf("Time to Sleep: %ld\n", data->tt_sleep);
    printf("Number Each Philosopher Must Eat: %d\n", data->num_each_philo_must_eat);
    printf("Time Start: %ld\n", data->time_start);
	printf("End of Simulation: %d\n", data->end_simulation);
    printf("Forks Pointer: %p\n", (void*)data->forks);
    printf("Philosophers Pointer: %p\n", (void*)data->philos);
}
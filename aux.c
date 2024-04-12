#include "philo.h"

void	wait_threads(t_data *data)
{
	while(!get_state(&data->mutex, &data->all_threads))
	;
}
void print_philo(t_philo *philo)
{
	if (philo == NULL) {
		printf("Philo pointer is NULL.\n");
		return;
	}

	printf("Philo ID: %ld\n", philo->id);
	printf("\tLast Meal Time: %ld\n", philo->time_lastmeal);
	printf("\tNumber of Meals: %ld\n", philo->number_of_meals);
	printf("\tIs Full: %ld\n", philo->full);
	printf("\tRight Fork: %ld, Left Fork: %ld\n", philo->first_fork->fork_id, philo->second_fork->fork_id);
	printf("\tState (Eat: %ld, Sleep: %ld, Think: %ld)\n", philo->eat, philo->sleep, philo->think);
	// Nota: No imprimimos 't_data *data' para evitar recursión profunda y complejidad.
}

void print_data(t_data *data) {
	if (data == NULL) {
		printf("Data pointer is NULL.\n");
		return;
	}

	printf("Philosopher Number: %ld\n", data->ph_number);
	printf("Time to Die: %ld\n", data->tt_die);
	printf("Time to Eat: %ld\n", data->tt_eat);
	printf("Time to Sleep: %ld\n", data->tt_sleep);
	printf("Number Each Philosopher Must Eat: %ld\n", data->num_each_philo_must_eat);
	printf("Time Start: %ld\n", data->time_start);
	printf("End Simulation: %ld\n", data->end_simulation);

	// Imprimir información sobre los forks si es posible
	if (data->forks != NULL) {
		for (int i = 0; i < data->ph_number; i++) {
			printf("Fork ID: %ld\n", data->forks[i].fork_id);
			// La información del mutex se omite porque no es trivialmente imprimible
		}
	}

	// Imprimir información sobre los filósofos
	if (data->phs != NULL) {
		for (int i = 0; i < data->ph_number; i++) {
			print_philo(&data->phs[i]);
		}
	}
}

unsigned long	ft_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec/1000);
}

int free_data(t_data *data)
{
	if (data != NULL)
	{
		if (data->forks != NULL)
		{
			free(data->forks);
			data->forks = NULL;
		}
		if (data->phs != NULL)
		{
			free(data->phs);
			data->phs = NULL; 
		}
		free(data);
	}
	return (1);
}
#include "philo.h"

void print_philo(t_philo *philo)
{
	if (philo == NULL) {
		printf("Philo pointer is NULL.\n");
		return;
	}

	printf("Philo ID: %d\n", philo->id);
	printf("\tLast Meal Time: %ld\n", philo->time_lastmeal);
	printf("\tNumber of Meals: %d\n", philo->number_of_meals);
	printf("\tIs Full: %d\n", philo->full);
	printf("\tState (Eat: %d, Sleep: %d, Think: %d)\n", philo->eat, philo->sleep, philo->think);
	// Nota: No imprimimos 't_data *data' para evitar recursión profunda y complejidad.
}

void print_data(t_data *data) {
	if (data == NULL) {
		printf("Data pointer is NULL.\n");
		return;
	}

	printf("Philosopher Number: %d\n", data->ph_number);
	printf("Time to Die: %ld\n", data->tt_die);
	printf("Time to Eat: %ld\n", data->tt_eat);
	printf("Time to Sleep: %ld\n", data->tt_sleep);
	printf("Number Each Philosopher Must Eat: %d\n", data->num_each_philo_must_eat);
	printf("Time Start: %ld\n", data->time_start);
	printf("End Simulation: %d\n", data->end_simulation);

	// Imprimir información sobre los forks si es posible
	if (data->forks != NULL) {
		for (int i = 0; i < data->ph_number; i++) {
			printf("Fork ID: %d\n", data->forks[i].fork_id);
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

void free_data(t_data *data)
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
}
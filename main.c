#include "philo.h"

void print_data(t_data *data) {
    if (!data) {
        printf("Data pointer is NULL\n");
        return;
    }

    // Bloquear el mutex de impresión para evitar conflictos en la salida
    
    printf("Data Structure:\n");
    printf("  Number of Philosophers: %ld\n", data->ph_number);
    printf("  Time to Die: %ld\n", data->tt_die);
    printf("  Time to Eat: %ld\n", data->tt_eat);
    printf("  Time to Sleep: %ld\n", data->tt_sleep);
    printf("  Number Each Philosopher Must Eat: %ld\n", data->num_each_philo_must_eat);
    printf("  Time Start: %ld\n", data->time_start);
    printf("  All Threads: %ld\n", data->all_threads);
    printf("  Number of Threads Running: %ld\n", data->num_thrd_run);
    printf("  End Simulation: %ld\n", data->end_simulation);
    
    if (data->forks) {
        for (long int i = 0; i < data->ph_number; i++) {
            printf("  Fork %ld ID: %ld\n", i, data->forks[i].fork_id);
        }
    }

    if (data->phs) {
        for (long int i = 0; i < data->ph_number; i++) {
            printf("  Philosopher %ld:\n", i);
            printf("    Thread ID: %lu\n", data->phs[i].thrd);
            printf("    ID: %ld\n", data->phs[i].id);
            printf("    Last Meal: %ld\n", data->phs[i].lstmeal);
            printf("    Meal Counter: %ld\n", data->phs[i].meal_counter);
            printf("    Is Full: %ld\n", data->phs[i].full);
            printf("    Eating: %ld\n", data->phs[i].eat);
            printf("    Sleeping: %ld\n", data->phs[i].sleep);
            printf("    Thinking: %ld\n", data->phs[i].think);
            printf("    Dead: %ld\n", data->phs[i].dead);
            printf("    First Fork ID: %ld\n", data->phs[i].first_fork->fork_id);
            printf("    Second Fork ID: %ld\n", data->phs[i].second_fork->fork_id);
        }
    }

    // Desbloquear el mutex de impresión
}

int main(int argc, char **argv)
{
	t_data	*data;

	if (!valid_args(argc, argv))
		return (1);
	data = init_data(argv);
	//print_data(data);
	if (!data)
		return (1);
	if (!start_dinner(data))
		return (1);
	cleanup_data(data);
	return (0);
}

/*void	print_philo(t_philo *philo)
{
	if (philo == NULL) {
		printf("Philo pointer is NULL.\n");
		return;
	}

	printf("Philo ID: %ld\n", philo->id);
	printf("\tLast Meal Time: %ld\n", philo->lstmeal);
	printf("\tNumber of Meals: %ld\n", philo->meal_counter);
	printf("\tIs Full: %ld\n", philo->full);
	printf("\tRight Fork: %ld, Left Fork: %ld\n", philo->first_fork->fork_id, philo->second_fork->fork_id);
	printf("\tState (Eat: %ld, Sleep: %ld, Think: %ld)\n", philo->eat, philo->sleep, philo->think);
}

void	print_data(t_data *data) {
	if (data == NULL) {
		printf("Data pointer is NULL.\n");
		return;
	}

	printf("Philosopher Number: %ld\n", data->ph_number);
	printf("Time to Die: %ld\n", data->tt_die);
	printf("Time to Eat: %ld\n", data->tt_eat);
	printf("Time to Sleep: %ld\n", data->tt_sleep);
	printf("Number of Philos: %ld\n", data->ph_number);
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
}*/



#include "philo.h"

int	start_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_number)
	{
		printf("Initializing fork ID: %d\n", data->forks[i].fork_id);
		if (pthread_mutex_init(&data->forks[i].mutex,NULL) != 0) 
			return (0);
		i++;
	}
	return (1);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_number)
	{
		printf("Destroying fork ID: %d\n", data->forks[i].fork_id);
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
}

int	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_number)
	{
		if (pthread_create(&data->phs[i].thrd,NULL,thrd_run,&data->phs[i]))
			return (0);
		i++;
	}
	return (1);
}
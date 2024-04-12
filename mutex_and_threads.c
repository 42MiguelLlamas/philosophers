#include "philo.h"


void	*thrd_run(void *philo)
{
	t_philo				*ph;


	ph = (t_philo *) philo;
	printf("Philo ID: %ld\n", ph->id);
	printf("First Fork ID: %ld\n", ph->first_fork->fork_id);
	printf("Second Fork ID: %ld\n", ph->second_fork->fork_id);
	wait_threads(ph->data);
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_number)
	{
		printf("Destroying fork ID: %ld\n", data->forks[i].fork_id);
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
			return (print_error("Error creating thread."));
		i++;
	}
	set_state(&data->mutex, &data->all_threads, 1);
	return (1);
}

int start_dinner(t_data *data)
{
	if (data->num_each_philo_must_eat == 0)
		return (0);
	else if (data->ph_number== 1)
	{
		//Por hacer
	}
	if (!start_philos(data))
		return (0);
	return (1);
}
#include "philo.h"


int	write_status(t_status status, t_philo *philo)
{
	if (get_state(&philo->data->mutex, &philo->data->end_simulation) == 0)
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %ld has taken a fork.\n", ft_time(), philo->id);
		else if (status == EAT)
			printf("%-6ld %ld is eating.\n",ft_time(), philo->id);
		else if (status == SLEEP)
			printf("%-6ld %ld is sleeping.\n", ft_time(),philo->id);
		else if (status == THINK)
			printf("%-6ld %ld is thinking.\n", ft_time(),philo->id);
		else if (status == DIED)
			printf("%-6ld %ld died.\n", ft_time(),philo->id);
		return (1);
	}
	else if (get_state(&philo->data->mutex, &philo->data->end_simulation) == -1)
		return (0);
	return (1);
}

void	*thrd_run(void *philo)
{
	t_philo				*ph;


	ph = (t_philo *) philo;
	printf("Philo ID: %ld\n", ph->id);
	printf("First Fork ID: %ld\n", ph->first_fork->fork_id);
	printf("Second Fork ID: %ld\n", ph->second_fork->fork_id);
	if (!wait_threads(ph->data))
		return (NULL);
	if (!increase_value(&ph->data->mutex, &ph->data->num_threads_running))
		return (NULL);
	
	return (NULL);
}


void	*watchdog_run(void *data)
{
	t_data	*mon_data;

	mon_data = (t_data *)data;
	while (get_value(&mon_data->mutex, &mon_data->num_threads_running) ==
		mon_data->ph_number)
	;
	while (get_value(&mon_data->mutex, &mon_data->end_simulation))
	{}
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
	if (pthread_create(&data->watchdog,NULL,watchdog_run,&data))
			return (print_error("Error creating thread."));
	data->time_start = ft_time();
	if (!data->time_start)
		return(print_error("Error getting time."));
	set_state(&data->mutex, &data->all_threads, 1);
	return (1);
}

int start_dinner(t_data *data)
{
	int i;

	i = 0;
	if (data->num_each_philo_must_eat == 0)
		return (0);
	else if (data->ph_number== 1)
	{
		return (0);
	}
	if (!start_philos(data))
		return (0);
	while (i < data->ph_number)
	{
		pthread_join(data->phs[i].thrd, NULL);
		i++;
	}
	return (1);
}
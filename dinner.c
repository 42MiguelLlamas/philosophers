#include "philo.h"

int	write_status(t_status status, t_philo *philo)
{
	long	time;

	time = ft_time() - philo->data->time_start;
	if (get_value(&philo->data->mutex, &philo->data->end_simulation) == 0)
	{
		if (pthread_mutex_lock(&philo->data->print_mutex))
			return (print_error("Error en Mutex Lock."));
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %ld has taken a fork.\n", time, philo->id);
		else if (status == EAT)
			printf("%-6ld %ld is eating.\n", time, philo->id);
		else if (status == SLEEP)
			printf("%-6ld %ld is sleeping.\n", time, philo->id);
		else if (status == THINK)
			printf("%-6ld %ld is thinking.\n", time, philo->id);
		else if (status == DIED)
			printf("%-6ld %ld died.\n", time, philo->id);
		if (pthread_mutex_unlock(&philo->data->print_mutex))
			return (print_error("Error en Mutex Lock."));
		return (1);
	}
	else if (get_value(&philo->data->mutex, &philo->data->end_simulation) == -1)
		return (0);
	return (1);
}

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->mutex))
		return (print_error("Error en Mutex Lock."));
	if (!write_status(TAKE_FIRST_FORK, philo))
		return (0);
	if (pthread_mutex_lock(&philo->second_fork->mutex))
		return (print_error("Error en Mutex Lock."));
	if (!write_status(TAKE_SECOND_FORK, philo))
		return (0);
	if (!set_value(&philo->ph_mut, &philo->lstmeal, ft_time()))
		return (0);
	philo->meal_counter++;
	if (!write_status(EAT, philo))
		return (0);
	usleep(philo->data->tt_eat * 1000);
	if (philo->data->num_each_philo_must_eat == philo->meal_counter)
		if (!set_value(&philo->ph_mut, &philo->full, 1))
			return (0);
	if (pthread_mutex_unlock(&philo->first_fork->mutex))
		return (print_error("Error en Mutex Lock."));
	if (pthread_mutex_unlock(&philo->second_fork->mutex))
		return (print_error("Error en Mutex Lock."));
	return (1);
}

void	*thrd_run(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *) philo;
	if (!wait_threads(ph->data))
		return (NULL);
	if (!increase_value(&ph->data->mutex, &ph->data->num_thrd_run))
		return (NULL);
	if (!set_value(&ph->ph_mut, &ph->lstmeal, ft_time()))
		return (NULL);
	while(!get_value(&ph->data->mutex, &ph->data->end_simulation))
	{
		if (get_value(&ph->data->mutex, &ph->full) == 1)
			break;
		else if (get_value(&ph->data->mutex, &ph->full) == -1)
			return (NULL);
		if (!eat(ph))
			return(NULL);
		if (!write_status(SLEEP, ph))
			return (NULL);
		usleep(ph->data->tt_sleep * 1000);
		if (!write_status(THINK, ph))
			return (NULL);
	}
	return (NULL);
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
	if (pthread_create(&data->watchdog,NULL,watchdog_run, &data))
		return (print_error("Error creating thread."));
	data->time_start = ft_time();
	if (!data->time_start)
		return(print_error("Error getting time."));
	if (!set_value(&data->mutex, &data->all_threads, 1))
		return (0);
	printf("All threads ready main\n");
	return (1);
}

int start_dinner(t_data *data)
{
	int i;

	i = 0;
	if (data->num_each_philo_must_eat == 0 || data->ph_number == 0)
		return (0);
	else if (data->ph_number == 1)
	{
		//Create one philo

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
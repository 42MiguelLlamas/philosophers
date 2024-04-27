#include "philo.h"


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
	if (!desync(ph))
		return (NULL);
	while(!get_value(&ph->data->mutex, &ph->data->end_simulation))
	{
		if (get_value(&ph->data->mutex, &ph->full) == 1)
			break;
		else if (get_value(&ph->data->mutex, &ph->full) == -1)
			return (NULL);
		if (!eating(ph))
			return(NULL);
		if (!sleeping(ph))
			return (NULL);
		if (!thinking(ph, 1))
			return (NULL);
	}
	return (NULL);
}

void	*watchdog_run(void *data)
{
    t_data	*wd_d;
	long	i;
	
	wd_d= (t_data *)data;
    if (!wait_thread_run(wd_d))
		return (NULL);
    while (get_value(&wd_d->mutex, &wd_d->end_simulation) == 0)
	{
		i = -1;
        while (++i < wd_d->ph_number &&
			get_value(&wd_d->mutex, &wd_d->end_simulation) == 0)
		{
            if (philo_dead(&wd_d->phs[i]))
			{
				if (!write_status(DIED, &wd_d->phs[i]))
					return (NULL);
				if (!set_value(&wd_d->mutex, &wd_d->end_simulation, 1))
					return (NULL);
                break;
            }
		}
		usleep(200);
    }
    return (NULL);
}

void	*lone_philo(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *) philo;

	if (!wait_threads(ph->data))
		return (NULL);
	if (!set_value(&ph->ph_mut, &ph->lstmeal, ft_time()))
		return (NULL);
	if (!increase_value(&ph->data->mutex, &ph->data->num_thrd_run))
		return (NULL);

	if (!write_status(TAKE_FIRST_FORK, ph))
		return (NULL);
	while(get_value(&ph->data->mutex, &ph->data->end_simulation) == 0)
	{
		usleep(200);
	}
	return (NULL);
}

int	start_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->ph_number == 1)
	{
		if (pthread_create(&data->phs[0].thrd,NULL,lone_philo,&data->phs[0]))
			return (print_error("Error creating thread."));
	}
	else
	{
		while (i < data->ph_number)
		{
			if (pthread_create(&data->phs[i].thrd,NULL,thrd_run,&data->phs[i]))
				return (print_error("Error creating thread."));
			i++;
		}
	}
	if (pthread_create(&data->watchdog,NULL,watchdog_run, data))
		return (print_error("Error creating thread."));
	data->time_start = ft_time();
	if (!set_value(&data->mutex, &data->all_threads, 1))
		return (0);
	return (1);
}

int start_dinner(t_data *data)
{
	int i;

	i = -1;
	if (data->ph_number == 0)
		return (0);
	if (!start_philos(data))
		return (0);
	while (++i < data->ph_number)
		pthread_join(data->phs[i].thrd, NULL);
	if (!set_value(&data->mutex, &data->end_simulation, 1))
		return (0);
	pthread_join(data->watchdog, NULL);
	return (1);
}

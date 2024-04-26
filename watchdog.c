#include "philo.h"

int	philo_dead(t_philo *philo)
{
	long	elapsed;
	long	tt_die;

	if (get_value(&philo->ph_mut, &philo->full) == 1)
		return (0);
	elapsed = ft_time() - philo->lstmeal;
	tt_die = philo->data->tt_die;
	if (elapsed > tt_die)
		return (1);
	return (0);
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
    }
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
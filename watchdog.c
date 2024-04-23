#include "philo.h"

void	*watchdog_run(void *data)
{
    t_data	*wd_d;
	long	last_time;
	long	i;
	
	wd_d= (t_data *)data;
    if (!wait_thread_run(wd_d))
		return (NULL);
    while (get_value(&wd_d->mutex, &wd_d->end_simulation) == 0)
	{
		i = -1;
        while (++i < wd_d->ph_number)
		{
			last_time = get_value(&wd_d->phs[i].ph_mut, &wd_d->phs[i].lstmeal);
            if ((ft_time() - last_time) > wd_d->phs[i].data->tt_die)
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
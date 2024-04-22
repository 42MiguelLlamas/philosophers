#include "philo.h"

void	*watchdog_run(void *data)
{
	t_data	*wd_data;

	wd_data = (t_data *)data;
	while (get_value(&wd_data->mutex, &wd_data->num_thrd_run) ==
		wd_data->ph_number)
	;
	while (get_value(&wd_data->mutex, &wd_data->end_simulation))
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
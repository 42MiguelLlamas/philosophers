#include "philo.h"


t_fork	*create_forks(int	num)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = malloc(num * sizeof(t_fork));
	if (!forks)
		return (forks);
	while (i < num)
	{
		forks[i].fork_id = i;
		if (pthread_mutex_init(&forks[i].mutex, NULL))
			return (NULL);
		i++;
	}
	return(forks);
}

t_fork	*assign_fork(int order, int id, t_data *data)
{
	if (id % 2  == 0)
	{
		if (order == 1)
		{
			if (id == data->ph_number - 1)
				return (&data->forks[0]);
			return (&data->forks[id + 1]);
		}
		return(&data->forks[id]);
	}
	if (order == 1)
		return(&data->forks[id]);
	if (id == data->ph_number - 1)
		return (&data->forks[0]);
	return (&data->forks[id + 1]);
}

t_philo	*create_philos(int	num, t_data *data)
{
	t_philo *philos;
	int		i;

	i = 0;
	philos = malloc(num * sizeof(t_philo));
	if (!philos)
		return (NULL);
	while (i < num)
	{
		philos[i].id = i;
		philos[i].time_lastmeal = 0;
		philos[i].number_of_meals = 0;
		philos[i].full = 0;
		philos[i].eat = 0;
		philos[i].sleep = 0;
		philos[i].think = 0;
		philos[i].dead = 0;
		philos[i].data = data;
		philos[i].first_fork = assign_fork(1, i, data);
		philos[i].second_fork = assign_fork(2, i, data);
		i++;
	}
	return(philos);
}

t_data	*init_basic_data(char **args, t_data *data)
{
	data->ph_number = (int)ft_tolong(args[1]);
	data->tt_die = ft_tolong(args[2]);
	data->tt_eat = ft_tolong(args[3]);
	data->tt_sleep = ft_tolong(args[4]);
	data->num_each_philo_must_eat = 0;
	data->num_threads_running = 0;
	data->time_start = 0;
	if (args[5])
		data->num_each_philo_must_eat = (int)ft_tolong(args[5]);
	data->end_simulation = 0;
	if (pthread_mutex_init(&data->mutex, NULL))
		return (NULL);
	if (pthread_mutex_init(&data->mutex, NULL))
		return (NULL);
	data->all_threads = 0;
	return(data);
}

t_data	*init_data(char **args)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data = init_basic_data(args, data);
	if (!data)
	{
		free(data);
		return (NULL);
	}
	data->forks = create_forks(data->ph_number);
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	data->phs = create_philos(data->ph_number, data);
	if (!data->phs)
	{
		free(data->forks);
		free(data);
		return (NULL);
	}
	return (data);
}

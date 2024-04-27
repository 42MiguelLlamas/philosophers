/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:18:48 by mllamas-          #+#    #+#             */
/*   Updated: 2024/04/27 10:18:50 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_threads(t_data *data)
{
	while (!get_value(&data->mutex, &data->all_threads))
		;
	if (get_value(&data->mutex, &data->all_threads) == -1)
		return (0);
	return (1);
}

int	wait_thread_run(t_data *data)
{
	int	number;

	number = 0;
	while (number != data->ph_number && number != -1)
	{
		number = get_value(&data->mutex, &data->num_thrd_run);
	}
	if (number == -1)
		return (0);
	return (1);
}

void	precise_usleep(long time, t_philo *philo)
{
	long	start;
	long	now;
	long	elapsed;
	long	rem;

	start = ft_microtime();
	while (1)
	{
		now = ft_microtime();
		elapsed = now - start;
		if (elapsed >= time)
			break ;
		if (get_value(&philo->data->mutex, &philo->data->end_simulation) != 0)
			break ;
		rem = time - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			usleep(100);
	}
}

int	desync(t_philo *philo)
{
	if (philo->data->ph_number % 2 == 0)
	{
		if (philo->id % 2 != 0)
			precise_usleep(3e4, philo);
	}
	else
	{
		if (philo ->id % 2 == 0)
			if (!thinking(philo, 0))
				return (0);
	}
	return (1);
}

void	cleanup_data(t_data *data)
{
	long int	i;

	i = -1;
	if (!data)
		return ;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (data->forks && ++i < data->ph_number)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
	}
	if (data->forks)
		free(data->forks);
	i = -1;
	while (data->phs && ++i < data->ph_number)
	{
		pthread_mutex_destroy(&data->phs[i].ph_mut);
	}
	if (data->phs)
		free(data->phs);
	free(data);
}

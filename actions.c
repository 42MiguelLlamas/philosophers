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
			printf("%-6ld %ld has taken a fork\n", time, philo->id);
		else if (status == EAT)
			printf("%-6ld %ld is eating\n", time, philo->id);
		else if (status == SLEEP)
			printf("%-6ld %ld is sleeping\n", time, philo->id);
		else if (status == THINK)
			printf("%-6ld %ld is thinking\n", time, philo->id);
		else if (status == DIED)
			printf("%-6ld %ld died\n", time, philo->id);
		if (pthread_mutex_unlock(&philo->data->print_mutex))
			return (print_error("Error en Mutex Lock."));
		return (1);
	}
	else if (get_value(&philo->data->mutex, &philo->data->end_simulation) == -1)
		return (0);
	return (1);
}

int	eating(t_philo *philo)
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
	precise_usleep(philo->data->tt_eat * 1000, philo);
	if (philo->data->num_each_philo_must_eat == philo->meal_counter)
		if (!set_value(&philo->ph_mut, &philo->full, 1))
			return (0);
	if (pthread_mutex_unlock(&philo->first_fork->mutex))
		return (print_error("Error en Mutex Lock."));
	if (pthread_mutex_unlock(&philo->second_fork->mutex))
		return (print_error("Error en Mutex Lock."));
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!write_status(SLEEP, philo))
		return (0);
	precise_usleep(philo->data->tt_sleep * 1000, philo);
	return (1);
}

int	thinking(t_philo *philo, int do_it)
{
	long	tt_think;

	if (do_it == 1)
		if (!write_status(THINK, philo))
			return (0);
	if (philo->data->ph_number % 2 != 0)
		return (1);
	tt_think = philo->data->tt_eat * 2 - philo->data->tt_sleep;
	if (tt_think < 0)
		tt_think = 0;
	precise_usleep(tt_think * 0.42, philo);
	return (1);
}

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
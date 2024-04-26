#include "philo.h"

int	set_value(pthread_mutex_t *mutex, long *old, long new)
{
	if (pthread_mutex_lock(mutex))
		return (print_error("Error en Mutex Lock."));
	*old = new;
	if (pthread_mutex_unlock(mutex))
		return (print_error("Error en Mutex Unlock."));
	return (1);
}


long int	increase_value(pthread_mutex_t *mutex, long int *old)
{
	if (pthread_mutex_lock(mutex))
		return (print_error("Error en Mutex Lock."));
	(*old)++;
	if (pthread_mutex_unlock(mutex))
		return (print_error("Error en Mutex Unlock."));
	return (1);
}

long	get_value(pthread_mutex_t *mutex, long *value)
{
	long	val;
	int		lock_result;

	lock_result = pthread_mutex_lock(mutex);
	if (lock_result)
	{
		print_error("Error en Mutex Lock.");
		return (-1);
	}
	val = *value;
	if (pthread_mutex_unlock(mutex))
	{
		print_error("Error en Mutex Unlock.");
		return (-1);
	}
	return (val);
}

long	ft_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec/1000);
}

long	ft_microtime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}
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
	long val;

	if (pthread_mutex_lock(mutex))
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

int	set_state(pthread_mutex_t *mutex, long *old, long new)
{
	if (pthread_mutex_lock(mutex))
		return (print_error("Error en Mutex Lock."));
	*old = new;
	if (pthread_mutex_unlock(mutex))
		return (print_error("Error en Mutex Unlock."));
	return (1);
}

long	get_state(pthread_mutex_t *mutex, long *state)
{
	long st;
	
	if (pthread_mutex_lock(mutex))
	{
		print_error("Error en Mutex Lock.");
		return (-1);
	}
	st = *state;
	if (pthread_mutex_unlock(mutex))
	{
		print_error("Error en Mutex Unlock.");
		return (-1);
	}
	return (st);
}
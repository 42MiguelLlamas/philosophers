#include "philo.h"

void	set_value(pthread_mutex_t *mutex, long *old, long new)
{
	pthread_mutex_lock(mutex);
	*old = new;
	pthread_mutex_unlock(mutex);
}

long	get_value(pthread_mutex_t *mutex, long *value)
{
	long val;

	pthread_mutex_lock(mutex);
	val = *value;
	pthread_mutex_unlock(mutex);
	return (val);
}

void	set_state(pthread_mutex_t *mutex, long *old, long new)
{
	pthread_mutex_lock(mutex);
	*old = new;
	pthread_mutex_unlock(mutex);
}

long	get_state(pthread_mutex_t *mutex, long *state)
{
	long st;
	
	pthread_mutex_lock(mutex);
	st = *state;
	pthread_mutex_unlock(mutex);
	return (st);
}
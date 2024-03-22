#include "philo.h"


void	*thrd_run(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *) philo;
	printf("Philo ID: %d\n", ph->id);
	printf("Left Fork ID: %d\n", ph->data->forks[ph->id].fork_id);
	if (ph->id == ph->data->ph_number - 1)
		printf("Right Fork ID: %d\n", ph->data->forks[0].fork_id);
	else
		printf("Right Fork ID: %d\n", ph->data->forks[(ph->id) + 1].fork_id);
	return (NULL);
}


int main(int argc, char **argv)
{
	t_data	*data;

	if (!valid_args(argc, argv))
	{
		printf("Error: Arguments not valid.\n");
		return (1);
	}
	data = init_data(argv);
	if (!data)
		return (1);
	if (!start_mutexes(data))
	{
		free_data(data);
		return (1);
	}
	if (!start_philos(data))
	{
		free_data(data);
		return(1);
	}
	usleep(1);
	destroy_mutexes(data);
	free_data(data);
	return (0);
}

/*
void* thread_run(void *arg)
{
	t_data *var = (t_data*)arg;
	var = (t_data *)var;
	sleep(2); 
	printf("[TH]: Hello from the thread number %d\n", var->j);
	pthread_mutex_lock(&(var->mutex));
	printf("[TH]: Hello from the thread, data was = %d \n", var->data);
	sleep(2);
	var->data++;
	printf("[TH]: Hello from the thread, data is = %d \n", var->data);
	pthread_mutex_unlock(&(var->mutex));
	printf("[TH]: To exit...............\n");
	return (NULL);
}

int main()
{
	t_data		*var;
	pthread_t 	thread[2];
	int	i;

	var = malloc(sizeof(t_data));
	if (var == NULL)
	{
		printf("Failed to allocate memory.\n");
		return -1;
	}
	var->data = 0;
	i = 0;
	if (pthread_mutex_init(&(var->mutex),NULL)!=0) 
		return (-1);
	while (i < 2)
	{
		printf("[MAIN: Starting............%d \n", i);
		var->j = i;
		if (pthread_create(&thread[i],NULL,thread_run,var) !=0)
		{
			printf("Error creating the thread. %d", i);
			free(var);
			return (-1);
		}
		i++;
	}
	sleep(1);
	printf("[MAIN]: Thread allocated \n");
	i = 0;
	while (i < 2)
	{
		pthread_join(thread[i],NULL);
		i++;
	}
	pthread_mutex_destroy(&(var->mutex));
	printf("[MAIN]: Thread returns %d \n", var->data);
	free(var);
	return 0;
}*/
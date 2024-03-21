#include "philo.h"


t_fork	*create_forks(int	num)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = malloc(num * sizeof(t_fork));
	if (!forks)
		return (forks);
	while (i < forks)
	{
		forks[i].fork_id = i;
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
	return(forks);
}

t_philo	*create_philos(int	num)
{
	num = num + 1;
	return(NULL);
}

t_data	*init_data(char **args)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	data->ph_number = (int)ft_tolong(args[1]);
	data->tt_die = ft_tolong(args[2]);
	data->tt_eat = ft_tolong(args[3]);
	data->tt_sleep = ft_tolong(args[4]);
	data->num_each_philo_must_eat = 0;
	if (args[5])
		data->num_each_philo_must_eat = (int)ft_tolong(args[5]);
	data->time_start = ft_timestart();
	data->end_simulation = 0;
	data->forks = create_forks(data->ph_number);
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	data->philos = create_philos(data->ph_number);
	if (!data->philos)
	{
		free(data);
		return (NULL);
	}
	return (data);
}


int main(int argc, char **argv)
{
	t_data	*data;

	if (valid_args(argc, argv) == 0) {
		printf("Todos los argumentos son enteros positivos.\n");
	} else {
		printf("Error: Argument not valid.\n");
		return (1);
	}
	data = init_data(argv);
	print_data(data);
	free(data);
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
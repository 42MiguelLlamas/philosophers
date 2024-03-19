// compile with $ gcc -Wall -g *.c -pthread -o program
// run with ./program
// check with valgrind --tool=helgrind ./program
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef	struct s_data
{
	int				data;
	pthread_mutex_t mutex;
	int				j;
	
}				t_data;


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
}
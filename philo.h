#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

typedef	struct	s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
}				t_fork;

typedef struct s_philo	t_philo;

typedef	struct	s_data
{
	int				ph_number;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	int				num_each_philo_must_eat;
	long			time_start;
	t_fork			*forks;
	t_philo			*phs;
	int				end_simulation;
}				t_data;

typedef struct	s_philo
{
	pthread_t	thrd;
	int			id;
	long		time_lastmeal;
	int			number_of_meals;
	int			full;
	int			eat;
	int			sleep;
	int			think;
	int			dead;
	t_data		*data;
}				t_philo;


int				ft_isdigit(int c);
int				ft_islong(char *str);
int 			ft_tolong(char *str);
unsigned long	ft_timestart(void);
int				valid_args(int arg_num, char **args);

t_fork			*create_forks(int	num);
t_philo			*create_philos(int	num, t_data *data);
t_data			*init_basic_data(char **args, t_data *data);
t_data			*init_data(char **args);

int				start_mutexes(t_data *data);
void			destroy_mutexes(t_data *data);
int				start_philos(t_data *data);
void			*thrd_run(void *philo);

void			print_data(t_data *data);
void 			print_philo(t_philo *philo);
void			free_data(t_data *data);

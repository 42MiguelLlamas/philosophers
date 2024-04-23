#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}			t_status;

typedef	struct	s_fork
{
	pthread_mutex_t	mutex;
	long int				fork_id;
}				t_fork;

typedef struct s_philo	t_philo;

typedef	struct	s_data
{
	long int		ph_number;
	long int		tt_die;
	long int		tt_eat;
	long int		tt_sleep;
	long int		num_each_philo_must_eat;
	long int		time_start;
	long int		all_threads;
	long int		num_thrd_run;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		watchdog;
	t_fork			*forks;
	t_philo			*phs;
	long int		end_simulation;
}				t_data;

typedef struct		s_philo
{
	pthread_t		thrd;
	long int		id;
	long int		lstmeal;
	long int		meal_counter;
	long int		full;
	long int		eat;
	long int		sleep;
	long int		think;
	long int		dead;
	pthread_mutex_t	ph_mut;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_data			*data;
}					t_philo;

int				print_error(char *str);
int				ft_isdigit(int c);
long int		ft_islong(char *str);
long int		ft_tolong(char *str);
int				valid_args(int arg_num, char **args);

t_fork			*create_forks(int	num);
t_fork			*assign_fork(int order, int id, t_data *data);
t_philo			*create_philos(int	num, t_data *data);
t_data			*init_basic_data(char **args, t_data *data);
t_data			*init_data(char **args);

void			destroy_mutexes(t_data *data);
int				write_status(t_status status, t_philo *philo);
int				start_philos(t_data *data);
void			*thrd_run(void *philo);
int				start_dinner(t_data *data);

int				wait_threads(t_data *data);
int				wait_thread_run(t_data *data);
long			ft_time(void);
void			print_data(t_data *data);
void 			print_philo(t_philo *philo);
int				free_data(t_data *data);

int				set_value(pthread_mutex_t *mutex, long int *old, long new);
long int		get_value(pthread_mutex_t *mutex, long int *value);
long int		increase_value(pthread_mutex_t *mutex, long *old);

void	*watchdog_run(void *data);
void	destroy_mutexes(t_data *data);
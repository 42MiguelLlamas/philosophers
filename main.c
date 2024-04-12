#include "philo.h"



int main(int argc, char **argv)
{
	t_data	*data;

	if (!valid_args(argc, argv))
		return (1);
	data = init_data(argv);
	if (!data)
		return (1);
	if (!start_dinner(data))
		return (1);
	free_data(data);
	return (0);
}

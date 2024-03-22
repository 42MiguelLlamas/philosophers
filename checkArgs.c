#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}


int ft_tolong(char *str)
{
    unsigned long	result;
    int				i;
	unsigned long	digit;
	
	i = 0;
	result = 0;
    while (str[i] != '\0')
	{
        digit = str[i] - '0';
        result = result * 10 + digit;
        i++;
    }
    return (result);
}


int ft_islong(char *str)
{
    unsigned long	result;
    int				i;
	unsigned long	digit;
	
	i = 0;
	result = 0;
    if (str[i] == '\0')
        return (0);
    while (str[i] != '\0')
	{
        if (!ft_isdigit(str[i]))
            return (0);
        digit = str[i] - '0';
        if (result > (LONG_MAX - digit) / 10)
            return (0);
        result = result * 10 + digit;
        i++;
    }
    return (1);
}

unsigned long	ft_timestart(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec/1000);
}


int	valid_args(int arg_num, char **args)
{
	int	i;

	i = 1;
	if (arg_num != 5 && arg_num != 6)
		return (0);
	while (i < arg_num)
	{
		if (!ft_islong(args[i]))
			return (0);
		i++;
	}
	return (1);
}

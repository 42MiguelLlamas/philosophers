#include "philo.h"

int	print_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}


long int ft_tolong(char *str)
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


long int ft_islong(char *str)
{
    unsigned long	result;
    int				i;
	unsigned long	digit;
	
	i = 0;
	result = 0;
    if (str[i] == '\0')
        return (print_error("Error: Argumento Vacío"));
    while (str[i] != '\0')
	{
        if (!ft_isdigit(str[i]))
            return (print_error("Error: Argumento No Numerico"));
        digit = str[i] - '0';
        if (result > (LONG_MAX - digit) / 10)
            return (print_error("Error: Argumento Fuera de Rango"));
        result = result * 10 + digit;
        i++;
    }
    return (1);
}


int	valid_args(int arg_num, char **args)
{
	int	i;

	i = 1;
	if (arg_num != 5 && arg_num != 6)
		return (print_error("Error: Número de argumentos no válido."));
	while (i < arg_num)
	{
		if (!ft_islong(args[i]))
			return (0);
		i++;
	}
	return (1);
}

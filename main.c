/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:18:24 by mllamas-          #+#    #+#             */
/*   Updated: 2024/04/27 10:18:26 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!valid_args(argc, argv))
		return (1);
	data = init_data(argv);
	if (!data)
		return (1);
	if (!start_dinner(data))
		return (1);
	cleanup_data(data);
	return (0);
}

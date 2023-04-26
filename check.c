/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:23:47 by macos             #+#    #+#             */
/*   Updated: 2023/04/22 23:23:48 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (1);
	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				write(1, "Wrong Argument!!", 16);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	data_assign(char **av, t_data *data)
{
	data->philo_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (data->philo_num < 1)
	{
		printf("Wrong Argument\n");
		return (1);
	}
	if (av[5])
	{
		if (ft_atoi(av[5]) < 0)
		{
			printf("Wrong Argument\n");
			return (1);
		}
		data->must_eat_num = ft_atoi(av[5]);
	}
	else
		data->must_eat_num = -1;
	return (0);
}

void	smart_sleep(int time)
{
	unsigned long	time_zone;

	time_zone = get_time() + time;
	while (get_time() <= time_zone)
		usleep(100);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

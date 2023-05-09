/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamli <bsamli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:23:55 by bsamli            #+#    #+#             */
/*   Updated: 2023/05/09 13:54:50 by bsamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_passed_time(unsigned long begin)
{
	return (get_time() - begin);
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->write_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (1);
}

int	all_philos_eating(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->write_mutex);
		if (data->philo[i].meals != data->must_eat_num)
		{
			pthread_mutex_unlock(&data->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->write_mutex);
		i++;
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

int	philo_dead(t_data *data, int index)
{
	unsigned long	time;

	pthread_mutex_lock(&data->write_mutex);
	time = get_passed_time(data->philo[index].last_eat);
	if (time >= (unsigned long)data->die_time
		&& !(data->philo[index].meals == data->must_eat_num))
	{
		printf("%-10lu   %d %s\n", time, data->philo[index].id_philo, "died");
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

void	*dead(void *data_a)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)data_a;
	while (1)
	{
		i = 0;
		if (!is_dead(data) || !all_philos_eating(data))
			break ;
		while (i < data->philo_num)
		{
			if (!all_philos_eating(data) || philo_dead(data, i))
				break ;
			i++;
		}
	}
	return (NULL);
}

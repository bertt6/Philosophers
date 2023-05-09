/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamli <bsamli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:23:58 by bsamli            #+#    #+#             */
/*   Updated: 2023/05/08 12:42:23 by bsamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_data *data, int index, char *text)
{
	pthread_mutex_lock(&data->write_mutex);
	if (data->must_eat_num == data->philo[index].meals)
	{
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->philo_num]);
		return (1);
	}
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->philo_num]);
		return (1);
	}
	printf("%-10lu %d %s\n", get_passed_time(data->start_time),
		data->philo[index].id_philo, text);
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

int	eating(t_data *data, int index)
{
	if (is_dead(data))
	{
		pthread_mutex_lock(&data->forks[index]);
		if (print_status(data, index, "has taken a fork"))
			return (1);
		pthread_mutex_lock(&data->forks[(index + 1) % data->philo_num]);
		if (print_status(data, index, "has taken a fork"))
			return (1);
		if (print_status(data, index, "is eating"))
			return (1);
		pthread_mutex_lock(&data->write_mutex);
		data->philo[index].meals++;
		data->philo[index].last_eat = get_time();
		pthread_mutex_unlock(&data->write_mutex);
		smart_sleep(data->eat_time);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->philo_num]);
	}
	else
		return (1);
	return (0);
}

int	thinking(t_data *data, int index)
{
	if (print_status(data, index, "is thinking"))
		return (1);
	return (0);
}

int	sleeping(t_data *data, int index)
{
	if (print_status(data, index, "is sleeping"))
		return (1);
	smart_sleep(data->sleep_time);
	return (0);
}

void	*routine(void *data_a)
{
	int		index;
	t_data	*data;

	data = (t_data *)data_a;
	pthread_mutex_lock(&data->write_mutex);
	index = data->thread_index;
	pthread_mutex_unlock(&data->write_mutex);
	while (1)
	{
		if (data->must_eat_num != data->philo[index].meals)
		{
			if (!is_dead(data) || eating(data, index))
				break ;
			if (!is_dead(data) || sleeping(data, index))
				break ;
			if (!is_dead(data) || thinking(data, index))
				break ;
		}
		else
			break ;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamli <bsamli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:23:49 by macos             #+#    #+#             */
/*   Updated: 2023/05/03 19:05:08 by bsamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc (sizeof(pthread_mutex_t) * data->philo_num);
	while (i < data->philo_num)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc (sizeof(t_philo) * data->philo_num);
	while (i < data->philo_num)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].last_eat = get_time();
		i++;
	}
	data->philo_dead = 0;
	data->thread_index = 0;
}

void	*one_philo(void *data_a)
{
	t_data	*data;

	data = (t_data *)data_a;
	print_status(data, 0, "has taken fork");
	smart_sleep(data->die_time);
	printf("0 died\n");
	return (NULL);
}

void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->dead, NULL);
}

void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	if (data->philo_num == 1)
	{
		pthread_create(&data->philo[0].thread, NULL, &one_philo, data);
		thread_join(data);
	}
	else
	{
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->write_mutex);
			data->thread_index = i;
			pthread_mutex_unlock(&data->write_mutex);
			pthread_create(&data->philo[i].thread, NULL, routine, data);
			usleep(100);
			i++;
		}
		pthread_create(&data->dead, NULL, &dead, data);
		thread_join(data);
	}
}

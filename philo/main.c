/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamli <bsamli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:18:49 by bsamli            #+#    #+#             */
/*   Updated: 2023/05/30 16:15:44 by bsamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (arg_check(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (data_assign(av, data))
		return (1);
	init_mutex(data);
	init_philo(data);
	create_thread(data);
	system("leaks philo");
}

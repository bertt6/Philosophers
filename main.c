/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:18:49 by macos             #+#    #+#             */
/*   Updated: 2023/04/26 23:56:25 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	if (arg_check(ac, av))
		return (1);
	data = malloc (sizeof(t_data));
	if (data_assign(av, data))
		return (1);
	init_mutex(data);
	init_philo(data);
	create_thread(data);
}

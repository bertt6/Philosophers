/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamli <bsamli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:23:52 by bsamli            #+#    #+#             */
/*   Updated: 2023/05/08 12:42:15 by bsamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id_philo;
	int				meals;
	int				must_meal_num;
	unsigned long	last_eat;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_num;
	int				philo_dead;
	int				thread_index;
	unsigned long	start_time;
	pthread_t		dead;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_data;

int					ft_atoi(const char *str);
int					arg_check(int ac, char **av);
int					data_assign(char **av, t_data *data);
void				smart_sleep(int time);
unsigned long		get_time(void);
void				init_mutex(t_data *data);
void				init_philo(t_data *data);
void				*one_philo(void *data_a);
void				thread_join(t_data *data);
void				create_thread(t_data *data);
unsigned long		get_passed_time(unsigned long begin);
int					is_dead(t_data *data);
int					all_philos_eating(t_data *data);
int					philo_dead(t_data *data, int index);
void				*dead(void *data_a);
int					print_status(t_data *data, int index, char *text);
int					eating(t_data *data, int index);
int					thinking(t_data *data, int index);
int					sleeping(t_data *data, int index);
void				*routine(void *data_a);

#endif

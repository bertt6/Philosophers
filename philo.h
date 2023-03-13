
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

pthread_t *a;

typedef struct s_philo
{
     int philo_num;
     int dead_time;
     int eat_time;
     int sleep_time;
     int eat_num;
     int fork_num;
     int *fork;
     int *philo;
}              t_philo;

int arg_control(char **av);
void data_assign(t_philo *data, char **av, int ac);
int	ft_atoi(const char *str);
void create_thread(t_philo *data);
void *philo(void *data);
void mutex_init(t_philo *data);     

#endif

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
     int philo;
     int meal;
     pthread_t thread;
     int last_meal;
     struct s_data *data;
     pthread_mutex_t meal_mutex;

}              t_philo;

typedef struct s_data
{
     int philo_num;
     int dead_time;
     int eat_time;
     int sleep_time;
     int eat_num;
     int fork_num;
     int *fork;
     pthread_mutex_t *fork_mutex;
     t_philo *philo;
     int dead;
     int start_time; // yeni start_time değişkeni eklendi
     pthread_mutex_t print_mutex; // yeni print_mutex ekledim
}              t_data;

int arg_control(char **av);
void data_assign(t_philo *data, char **av, int ac);
int	ft_atoi(const char *str);
void create_thread(t_philo *data);
void mutex_init(t_philo *data);     
void print_status(t_philo *philo, char *status);
void take_forks(t_philo *philo);
void eat(t_philo *philo);
void put_forks(t_philo *philo);
void think(t_philo *philo);
void *routine(void *philo_ptr);
void cleanup(t_philo *data);
void *monitor_thread(void *arg);
unsigned long long get_time();

#endif
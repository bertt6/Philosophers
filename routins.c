#include "philo.h"

void print_status(t_philo *philo, char *status)
{
    int curr_time;

    pthread_mutex_lock(&philo->data->print_mutex); // print_mutex kilitlendi
    curr_time = get_time() - philo->data->start_time;
    printf("%d %d %s\n", curr_time, philo->philo + 1, status);
    pthread_mutex_unlock(&philo->data->print_mutex); // print_mutex kilidi açıldı
}

void take_forks(t_philo *philo)
{
     pthread_mutex_lock(&philo->data->fork_mutex[philo->philo]);
     print_status(philo, "has taken a fork");
     pthread_mutex_lock(&philo->data->fork_mutex[philo->philo + 1]);
     print_status(philo, "has taken a fork");     
}

void eat(t_philo *philo)
{
     pthread_mutex_lock(&philo->meal_mutex);
     philo->last_meal = get_time();
     pthread_mutex_unlock(&philo->meal_mutex);
     print_status(philo, "is eating");
     usleep(philo->data->eat_time * 1000);
     pthread_mutex_lock(&philo->meal_mutex);
     philo->meal++;
     pthread_mutex_unlock(&philo->meal_mutex);
}

void put_forks(t_philo *philo)
{
     pthread_mutex_unlock(&philo->data->fork_mutex[philo->philo % philo->data->fork_num]);
     pthread_mutex_unlock(&philo->data->fork_mutex[(philo->philo + 1) % philo->data->fork_num]);
     print_status(philo, "has put down the forks");
}

void think(t_philo *philo)
{
     print_status(philo, "is thinking");
     usleep(philo->data->sleep_time * 1000);
}

void *routine(void *d)
{
     
     t_philo *philo;
     philo = (t_philo *) d;
     

     
     while (!philo->data->dead)
     {
          take_forks(philo);
          eat(philo);
          put_forks(philo);
          think(philo);
     }

     pthread_mutex_lock(&(philo->data->print_mutex));
     printf("Thread %d is dead\n", philo->philo);
     pthread_mutex_unlock(&(philo->data->print_mutex));
     
     return (NULL);
}
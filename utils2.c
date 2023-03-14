#include "philo.h"
void cleanup(t_philo *data)
{
    int i;

    i = 0;
    while (i < data->data->philo_num)
    {
        pthread_mutex_destroy(&(data->data->philo[i].meal_mutex));
        i++;
    }
    i = 0;
    while (i < data->data->fork_num)
    {
        pthread_mutex_destroy(&(data->data->fork_mutex[i]));
        i++;
    }
    free(data->data->philo);
    free(data->data->fork_mutex);
    free(data->data->fork);
    free(data->data);
}

void *monitor_thread(void *arg)
{
     t_philo *data = (t_philo *)arg;
     int i;
     int full;

     while(1)
     {
          i = 0;
          full = 0;
          while(i < data->data->philo_num)
          {
               pthread_mutex_lock(&data->data->philo[i].meal_mutex);
               if(get_time() - data->data->philo[i].last_meal < (unsigned long long)data->data->dead_time)
               {
                    print_status(&data->data->philo[i], " died\n");
                    cleanup(data);
               }
               if(data->data->eat_num != -1 && data->data->philo[i].meal >= data->data->eat_num)
                    full++;
               pthread_mutex_unlock(&data->data->philo[i].meal_mutex);
               i++;
          }
          if(full == data->data->philo_num)
               cleanup(data);
     }
     return (NULL);
}

unsigned long long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
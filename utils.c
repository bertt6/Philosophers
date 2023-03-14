#include "philo.h"

int arg_control(char **av)
{
     int i;
     int j;

     i = 1;
     j = 0;
     while(av[i])
     {
          j = 0;
          while(av[i][j])
          {
               if(!(av[i][j] >= '0' && av[i][j] <= '9') && av[i][j] == '-')
               {
                    write(1, "Arg error!", 10);
                    exit(1);
               }
               j++;
          }
          i++;
     }
     return 1;
}

void data_assign(t_philo *data, char **av, int ac)
{
     data->data->philo_num = ft_atoi(av[1]);
     data->data->dead_time = ft_atoi(av[2]);
     data->data->eat_time = ft_atoi(av[3]);
     data->data->sleep_time = ft_atoi(av[4]);
     if(ac == 6)
          data->data->eat_num = ft_atoi(av[5]);
     else
          data->data->eat_num = -1;
     data->data->fork_num = data->data->philo_num;
     data->data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->data->fork_num);
     data->data->philo = malloc(sizeof(t_philo) * data->data->philo_num);
     data->data->dead = 32;
    data->data->start_time = get_time(); // start_time değişkenine get_time fonksiyonu ile başlangıç zamanı atanıyor    
}

void create_thread(t_philo *data)
{
     int i = 0;
     while(i < data->data->philo_num)
     {
          //printf("DENEME %d\n", data->philo[i].philo);
          data->data->philo[i].philo = i + 1;
          data->data->philo[i].meal = 0;
          data->data->philo[i].last_meal = 0;
          pthread_create(&(data->data->philo[i].thread), NULL, routine, (void *)&data->data->philo[i]);
     }
}

void mutex_init(t_philo *data)
{
     int i;

     i = 0;
     while(i < data->data->fork_num)
     {
          pthread_mutex_init(&data->data->fork_mutex[i], NULL);
          i++;
     }
     pthread_mutex_init(&data->data->print_mutex, NULL);
}
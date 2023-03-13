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
     data->philo_num = ft_atoi(av[1]);
     data->dead_time = ft_atoi(av[2]);
     data->eat_time = ft_atoi(av[3]);
     data->sleep_time = ft_atoi(av[4]);
     data->fork_num = ft_atoi(av[1]);
     if(ac == 6)
          data->eat_num = ft_atoi(av[5]);
     data->fork = malloc(sizeof(int) * data->fork_num);
     data->philo = malloc(sizeof(int) * data->philo_num);
}

void *philo(void *data)
{
     t_philo *d;
     d = (t_philo *)data;
     printf("BUNEY %d\n", d->philo_num);
     return NULL;
}

void create_thread(t_philo *data)
{
     pthread_t *thread;
     int i;

     i = 0;
     thread = malloc(sizeof(pthread_t) * data->philo_num);
     while(i < data->philo_num)
     {
          pthread_create(&thread[i], NULL, philo, (void *)data);
          i++;
     }
     i = 0;
     while(i < data->philo_num)
     {
          pthread_join(thread[i], NULL);
          i++;
     }
}

void mutex_init(t_philo *data)
{
     int i;

     i = 0;
     while(i < data->fork_num)
     {
          pthread_mutex_init(&data->fork[i], NULL);
          i++;
     }
}

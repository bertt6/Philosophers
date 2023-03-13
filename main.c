#include "philo.h"

int main(int ac, char **av)
{
    if((ac == 5 || ac == 6) && arg_control(av))
    {
        t_philo *data;
        data = malloc (sizeof(t_philo));
        data_assign(data, av, ac);
        create_thread(data);
        mutex_init(data);
        
    }
}
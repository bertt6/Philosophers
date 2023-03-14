#include "philo.h"

int main(int ac, char **av)
{
    if ((ac == 5 || ac == 6) && arg_control(av))
    {
        t_philo *data;
        data = malloc(sizeof(t_philo));
        data_assign(data, av, ac);
        create_thread(data);
        mutex_init(data);
        monitor_thread(data);
        cleanup(data);
    }
    else
    {
        write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 121);
        return (1);
    }
    return (0);
}
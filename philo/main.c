#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac == 5 || ac == 6)
    {
        if (parse_args(ac, av, &data) == -1)
            return (EXIT_FAILURE);

        printf("n_ph: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\nrequired_meals: %d\n", data.n_ph, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.required_meals);
    }
    return (EXIT_SUCCESS);
}
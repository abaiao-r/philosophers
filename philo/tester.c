
#include <stdio.h>
#include <stdlib.h>
#include "includes/philo.h"

void run_test(int ac, char **av)
{
    printf("Arguments: ");
    for (int i = 0; i < ac; i++) {
        printf("%s ", av[i]);
    }
    printf("\n");

    if (!arg_check(ac, av)) {
        printf("Argument check failed\n");
        return;
    }

    t_philo *philo = init_philo_data(ac, av);

    printf("Number of philosophers: %d\n", philo->num_philos);
    printf("Time to die: %d\n", philo->time_to_die);
    printf("Time to eat: %d\n", philo->time_to_eat);
    printf("Time to sleep: %d\n", philo->time_to_sleep);
    printf("Number of meals: %d\n", philo->num_meals);

    free(philo);
}

int main()
{
    char *args1[] = {"./philo", "5", "200", "100", "150"};
    char *args2[] = {"./philo", "3", "400", "150", "200", "5"};
    char *args3[] = {"./philo", "1", "1000", "500", "250", "10"};
    char *args4[] = {"./philo", "6", "300", "200", "100", "0"};
    char *args5[] = {"./philo", "4a", "300", "200", "100"};
    char *args6[] = {"./philo", "4", "-300", "200", "100"};
    char *args7[] = {"./philo", "7", "2000000000000000000000", "200", "100"};

    run_test(5, args1);
    printf("\n");
    run_test(6, args2);
    printf("\n");
    run_test(6, args3);
    printf("\n");
    run_test(6, args4);
    printf("\n");
    run_test(5, args5);
    printf("\n");
    run_test(5, args6);
    printf("\n");
    run_test(5, args7);
    printf("\n");

    return 0;
}
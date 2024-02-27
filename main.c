/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:36:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/27 20:57:22 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *live(void *arg)
{
    t_philo  *philo;
    t_data  *data;
    
    if (!arg)
        return (NULL);
    philo = (t_philo *)arg;
    philo->t0 = now();
    if (philo->i % 2 == 1)
            usleep(200);
    data = ((t_data *)(philo->data));
    while (data->info->dead == 0 && data->info->meals > 0)
    {
        eating(data, philo->i);
        if (data->info->dead == 0)
            sleeping(data, philo->i);
    }
    return (NULL);
}

int    create_philosophers(t_data *data)
{
    int             i;
    int             ret;
    
    if (data->info->n == 0)
        return (0);
    data->philos = malloc(data->info->n * sizeof(t_philo));
    if (!data->philos)
        return (1);    
    i = 0;
    while (i < data->info->n)
    {
        data->philos[i].fork = malloc(1 * sizeof(t_fork));
        pthread_mutex_init(&(data->philos[i].fork->mut), NULL);
        set_philo(data, i);
        ret = pthread_create(&data->philos[i].id, NULL, live, &(data->philos[i]));
        if (ret != 0)
            printf("Fail\n");
        i++;
    }
    while (i >= 0)
        pthread_join(data->philos[i--].id, NULL);
    i = 0;
    while (i < data->info->n)
        free(data->philos[i++].fork);
    free(data->philos);
    return (0);
}

/*
void show_leaks(void)
{
    system("leaks philo");
}
*/

int	main(int argc, char **argv)
{
    t_data  *data;

    //atexit(show_leaks);
	if (validate(argc, argv) != 0)
		return(1);
    data = malloc(1 * sizeof(t_data));
    if (!data)
        return(2);
    data->info = malloc(1 * sizeof(t_info));
    if (!data->info)
    {
        free(data);
        return(3);
    }
    set_info(data->info, argc, argv);
    if (create_philosophers(data) != 0)
        return(4);
    free(data->info);
    free(data);
    return(0);
}
/*
pthread_mutex_destroy(&(data->philos[i].fork->mut));

-fsanitize=address -g3 
The -fsanitize=thread -g flag we can add at compilation. The -g option displays the specific files and line numbers involved.
The thread error detection tool Helgrind that we can run our program with, like this: valgrind --tool=helgrind ./philo <args>.
DRD, another thread error detection tool that we can also run our program with, like this: valgrind --tool=drd ./philo <args>.

number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

memset, malloc, free
write, printf
suspend, gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
*/
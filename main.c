/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:36:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/05 22:27:07 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *say_hello(void *arg)
{
    pthread_mutex_lock(arg);
    sleep(3);
    printf("Hello\n");
    if (!arg)
        printf("Bye...\n");
    //pthread_mutex_unlock(arg);
    printf()
    return (NULL);
}

int    create_philosophers(t_data *data)
{
    int             i;
    int             ret;
    
    data->philos = malloc(data->info->n * sizeof(t_philo));
    if (!data->philos)
        return (1);
    i = 0;
    while (i < data->info->n)
    {
        if (pthread_mutex_init(&data->philos[i].fork, NULL) != 0)
        {
        printf("Mutex initialization failed.\n");
        free(data->philos);
        return (1);
        }
        ret = pthread_create(&data->philos[i].id, NULL, say_hello, &data->philos[i].fork);
        if (ret != 0)
            printf("Fail\n");
        i++;
    }
    while (i >= 0)
    {
        pthread_join(data->philos[i].id, NULL);
        pthread_mutex_destroy(&data->philos[i].fork);
        i--;
    }
    free(data->philos);
    return (0);
}

int	main(int argc, char **argv)
{
    t_data  *data;

	if (validate(argc, argv) != 0)
		exit(1);
    data = malloc(1 * sizeof(t_data));
    if (!data)
        exit(1);
    data->info = malloc(1 * sizeof(t_info));
    if (!data->info)
    {
        free(data);
        exit(1);
    }
    set_info(data->info, argc, argv);
    create_philosophers(data);
    exit(0);
}
/*
- Idea: estructura con la información de argv
- Los filosofos son hilos

- Cada filósofo tiene: identificación (pthread_t), last time eat, eating times available, state, fork(mutex)

philo
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
memset, malloc, free
write, printf
usleep, gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
*/
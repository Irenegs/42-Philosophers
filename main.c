/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:36:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/21 21:26:44 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int  end_simulation(t_data *data)
{
    pthread_mutex_lock(&(data->info->death_mut));
    if (data->info->dead != 0)
    {
        pthread_mutex_unlock(&(data->info->death_mut));
        return (1);
    }
    pthread_mutex_unlock(&(data->info->death_mut));
    if (data->info->times == -1)
        return (0);
    pthread_mutex_lock(&(data->info->meals_mut));
    if (data->info->meals <= 0)
    {
        pthread_mutex_unlock(&(data->info->meals_mut));
        return (1);
    }
    pthread_mutex_unlock(&(data->info->meals_mut));
    return (0);
}

void    create_philosophers(t_data *data)
{
    int i;
    int ret;

    if (data->info->n == 0)
        return ;
    data->philos = malloc(data->info->n * sizeof(t_philo));
    if (!data->philos)
        return ;   
    i = -1;
    while (++i < data->info->n)
        set_philo(data, i);
    i = 0;
    while (i < data->info->n)
    {
        ret = pthread_create(&data->philos[i].id, NULL, live, &(data->philos[i]));
        if (ret != 0)
        {
            data->info->dead = 1;
            break ;
        }
        i++;
    }
    while (end_simulation(data) == 0)
        usleep(100);
    while (i > 0)
        pthread_join(data->philos[--i].id, NULL);
    free(data->philos);
    return ;
}

/*
void show_leaks(void)
{
    system("leaks philo");
}
*/

static void clear(t_data *data)
{
    int i = 0;

    pthread_mutex_destroy(&(data->info->death_mut));
    pthread_mutex_destroy(&(data->info->meals_mut));
    while (i < data->info->n)
    {
        pthread_mutex_destroy(&(data->fork[i].mut));
        i++;
    }
    free(data->fork);
    free(data->info);
    free(data);
}

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
    initialize_mutexes(data);
    create_philosophers(data);
    clear(data);
    return(0);
}


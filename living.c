/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:44:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/29 20:17:42 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    manage_meals(t_data *data, int i)
{
    if (data->philos[i].meals_av < 0)
        return ;
    data->philos[i].meals_av--;
    pthread_mutex_lock(&(data->info->mut));
    data->info->meals--;
    pthread_mutex_unlock(&(data->info->mut));
}

void    eating(t_data *data, int i)
{
	pthread_mutex_lock(&(data->philos[i].mut));
    display_message(data, i, FORK);
    if (i + 1 == data->info->n)
        pthread_mutex_lock(&(data->philos[0].mut));
    else
        pthread_mutex_lock(&(data->philos[i + 1].mut));
    display_message(data, i, FORK);
    display_message(data, i, EAT);
    manage_meals(data, i);
    suspend(data, EAT);
    data->philos[i].last_meal = now();
    pthread_mutex_unlock(&(data->philos[i].mut));
	if (i + 1 == data->info->n)
        pthread_mutex_unlock(&(data->philos[0].mut));
    else
        pthread_mutex_unlock(&(data->philos[i + 1].mut));
    display_message(data, i, LEAVES_FORK);
}

void    sleeping(t_data *data, int i)
{
    display_message(data, i, SLEEP);
    if (data->info->t_die <= data->info->t_sleep)
    {
        suspend(data, DEAD);
        pthread_mutex_lock(&(data->info->mut));
        data->info->dead++;
        pthread_mutex_unlock(&(data->info->mut));
        display_message(data, i, DEAD);
        return ;
    }
    suspend(data, SLEEP);
    display_message(data, i, THINK);
}

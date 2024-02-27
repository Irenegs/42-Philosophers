/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:44:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/27 20:44:00 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    manage_meals(t_data *data, int i)
{
    if (data->philos[i].meals_av < 0)
        return ;
    data->philos[i].meals_av--;
    data->info->meals--;
}

void    eating(t_data *data, int i)
{
	pthread_mutex_lock(&(data->philos[i].fork->mut));
	data->philos[i].fork->used = 1;
    display_message(data, i, FORK);
    if (data->philos[i].i + 1 == data->info->n)
        pthread_mutex_lock(&(data->philos[0].fork->mut));
    else
        pthread_mutex_lock(&(data->philos[i + 1].fork->mut));
    display_message(data, i, FORK);
    display_message(data, i, EAT);
    manage_meals(data, i);
    suspend(data->info->t_eat);
    data->philos[i].last_meal = now();
    data->philos[i].fork->used = 0;
    pthread_mutex_unlock(&(data->philos[i].fork->mut));
	if (i + 1 == data->info->n)
        pthread_mutex_unlock(&(data->philos[0].fork->mut));
    else
        pthread_mutex_unlock(&(data->philos[i + 1].fork->mut));
    display_message(data, i, LEAVES_FORK);
}

void    sleeping(t_data *data, int i)
{
    display_message(data, i, SLEEP);
    if (data->info->t_die <= data->info->t_sleep)
    {
        suspend(data->info->t_eat);
        data->info->dead++;
        display_message(data, i, DEAD);
        return ;
    }
    suspend(data->info->t_eat);
    display_message(data, i, THINK);
}

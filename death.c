/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:35:29 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/09 17:52:43 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_data *data, int i)
{
	pthread_mutex_lock(&(data->info->mut));
    data->info->dead++;
	if (data->info->dead == 1)
		display_message(data, i, DEAD);
    pthread_mutex_unlock(&(data->info->mut));
}

void	is_philo_dead(t_data *data, int i)
{
	if (since(data->philos[i].last_meal) > data->philos[i].t_die)
		philo_died(data, i);
}

int  nobody_dead(t_data *data)
{
    int dead;

    pthread_mutex_lock(&(data->info->mut));
    dead = data->info->dead;
    pthread_mutex_unlock(&(data->info->mut));
	return (dead);
}

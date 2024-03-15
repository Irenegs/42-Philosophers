/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:35:29 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/15 17:04:02 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_data *data, int i)
{
	pthread_mutex_lock(&(data->info->death_mut));
	data->info->dead++;
	if (data->info->dead == 1)
		display_message(data, i, DEAD);
	pthread_mutex_unlock(&(data->info->death_mut));
}

int	is_philo_dead(t_data *data, int i)
{
	if (since(data->philos[i].last_meal) > data->philos[i].t_die)
	{
		philo_died(data, i);
		return (1);
	}
	return (0);
}

int	nobody_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&(data->info->death_mut));
	dead = data->info->dead;
	pthread_mutex_unlock(&(data->info->death_mut));
	return (dead);
}

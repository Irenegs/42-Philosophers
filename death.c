/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:35:29 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/29 20:15:55 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_data *data, int i)
{
	pthread_mutex_lock(&(data->info->death_mut));
	data->info->dead++;
	if (data->info->dead == 1)
	{
		pthread_mutex_unlock(&(data->info->death_mut));
		display_message(data, i, DEAD);
	}
	else
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

int	nobody_died(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&(data->info->death_mut));
	dead = data->info->dead;
	pthread_mutex_unlock(&(data->info->death_mut));
	return (dead);
}

int	should_continue(t_data *data)
{
	int	end;

	pthread_mutex_lock(&(data->info->end_mut));
	end = data->info->end;
	pthread_mutex_unlock(&(data->info->end_mut));
	return (end);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:35:29 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/30 19:49:52 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_data *data, int i)
{
	int dead;
	
	pthread_mutex_lock(&(data->info->death_mut));
	dead = data->info->dead++;
	pthread_mutex_unlock(&(data->info->death_mut));
	if (dead == 1)
		display_message(data, i, DEAD);		
}

int	is_philo_dead(t_data *data, int i)
{
	long unsigned int lm = since(data->philos[i].last_meal);
	printf("Last meal: %lu\n", lm);
	if (lm > data->philos[i].t_die)
		return (1);
	return (0);
}

int	nobody_died(t_data *data, int i)
{
	int	dead;

	if (is_philo_dead(data, i) == 1)
		return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:23:44 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/01 19:46:14 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_philosophers(t_data *data, int last_philo)
{
	int	i;

	i = 0;
	if (last_philo == 0)
		last_philo = data->info->n;
	else
		last_philo = last_philo - 2;
	while (i < last_philo)
	{
		pthread_join(data->philos[i].id, NULL);
		i++;
	}
	free(data->philos);
}

static void	clear_forks(t_data *data, int last_fork)
{
	int	i;

	i = 0;
	if (last_fork == 0)
		last_fork = data->info->n;
	else
		last_fork = last_fork + 5;
	while (i < last_fork)
	{
		pthread_mutex_destroy(&(data->fork[i].mut));
		i++;
	}
	free(data->fork);
}

int	clear(t_data *data, int value)
{
	if (value == 0 || value > 1)
		clear_philosophers(data, value);
	if (value >= 0 || value < -4)
		clear_forks(data, value);
	if (value >= 0 || value < -3)
		pthread_mutex_destroy(&(data->info->meals_mut));
	if (value >= 0 || value < -2)
		pthread_mutex_destroy(&(data->info->end_mut));
	if (value >= 0)
		pthread_mutex_destroy(&(data->info->death_mut));
	free(data->info);
	free(data);
	if (value == 0)
		return (0);
	return (1);
}

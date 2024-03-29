/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:06:54 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/26 18:07:34 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	manage_meals(t_data *data, int i)
{
	data->philos[i].last_meal = now();
	if (data->philos[i].meals_av <= 0)
		return ;
	data->philos[i].meals_av--;
	pthread_mutex_lock(&(data->info->meals_mut));
	data->info->meals--;
	pthread_mutex_unlock(&(data->info->meals_mut));
}

static void	leave_forks(t_data *data, int i)
{
	data->philos[i].forks = 0;
	pthread_mutex_lock(&(data->fork[i].mut));
	data->fork[i].used = 0;
	pthread_mutex_unlock(&(data->fork[i].mut));
	pthread_mutex_lock(&(data->fork[(i + 1) % data->info->n].mut));
	data->fork[(i + 1) % data->info->n].used = 0;
	pthread_mutex_unlock(&(data->fork[(i + 1) % data->info->n].mut));
}

static void	take_one_fork(t_data *data, int i, int f)
{
	pthread_mutex_lock(&(data->fork[f].mut));
	if (data->fork[f].used == 0)
	{
		data->fork[f].used = 1;
		pthread_mutex_unlock(&(data->fork[f].mut));
		data->philos[i].forks++;
		display_message(data, i, FORK);
	}
	else
	{
		pthread_mutex_unlock(&(data->fork[f].mut));
		usleep(2);
	}
	is_philo_dead(data, i);
}

static void	take_forks(t_data *data, int i)
{
	while (data->philos[i].forks != 1 && is_philo_dead(data, i) == 0)
		take_one_fork(data, i, (i + (i + 1) % 2) % data->info->n);
	while (data->philos[i].forks != 2 && is_philo_dead(data, i) == 0)
		take_one_fork(data, i, (i + i % 2) % data->info->n);
}

int	eating(t_data *data, int i)
{
	take_forks(data, i);
	if (is_philo_dead(data, i) != 0)
		return (1);
	display_message(data, i, EAT);
	manage_meals(data, i);
	suspend(data->philos[i].t_eat);
	data->philos[i].last_meal = now();
	leave_forks(data, i);
	return (0);
}

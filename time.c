/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:18:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/01 18:43:08 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long unsigned int timestamp(t_data *data)
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000 - data->info->t0);
}

long unsigned int	now(void)
{
	struct timeval	t;
	
	gettimeofday(&t, 0);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

long unsigned int	since(long int t0)
{
	struct timeval	t;
	
	gettimeofday(&t, 0);
	return (t.tv_sec * 1000 + t.tv_usec / 1000 - t0);
}

void	suspend(t_data *data, int action)
{
	useconds_t	usec;
	
	pthread_mutex_lock(&(data->info->mut));
	if (action == EAT)
		usec = data->info->t_eat * 1000;
	else if (action == SLEEP)
		usec = data->info->t_sleep * 1000;
	else
		usec = data->info->t_die * 1000;
	pthread_mutex_unlock(&(data->info->mut));
	usleep(usec);
}

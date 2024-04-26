/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/01 19:42:48 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_message(t_data *data, int i, int action)
{
	long	time;
	int		dead;

	time = timestamp(data);
	if (action == DEAD)
		return (printf("%ld %d died.\n", time, i + 1));
	pthread_mutex_lock(&data->info->death_mut);
	dead = data->info->dead;
	if (dead != 0)
		return (pthread_mutex_unlock(&data->info->death_mut));
	if (action == FORK)
		printf("%ld %d has taken a fork.\n", time, i + 1);
	else if (action == EAT)
		printf("%ld %d is eating.\n", time, i + 1);
	else if (action == SLEEP)
		printf("%ld %d is sleeping.\n", time, i + 1);
	else if (action == THINK)
		printf("%ld %d is thinking.\n", time, i + 1);
	return (pthread_mutex_unlock(&data->info->death_mut));
}

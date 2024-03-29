/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/26 18:14:11 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_data *data, int i, int action)
{
	long	time;

	time = timestamp(data);
	if (action == DEAD)
	{
		printf("%ld %d died.\n", time, i);
		return ;
	}
	pthread_mutex_lock(&data->info->death_mut);
	if (action == FORK && data->info->dead == 0)
		printf("%ld %d has taken a fork.\n", time, i);
	else if (action == EAT && data->info->dead == 0)
		printf("%ld %d is eating.\n", time, i);
	else if (action == SLEEP && data->info->dead == 0)
		printf("%ld %d is sleeping.\n", time, i);
	else if (action == THINK && data->info->dead == 0)
		printf("%ld %d is thinking.\n", time, i);
	pthread_mutex_unlock(&data->info->death_mut);
}

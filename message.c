/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/25 21:20:33 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_data *data, int i , int action)
{
	long time;
	
	time = timestamp(data);
	if (action == DEAD)
	{
		printf("%ld %d died.\n", time, i);
		return ;
	}
	pthread_mutex_lock(&data->info->end_mut);
	if (action == FORK && data->info->end == 0)
		printf("%ld %d has taken a fork.\n", time, i);
	else if (action == EAT && data->info->end == 0)
		printf("%ld %d is eating.\n", time, i);
	else if (action == SLEEP && data->info->end == 0)
		printf("%ld %d is sleeping.\n", time, i);
	else if (action == THINK && data->info->end == 0)
		printf("%ld %d is thinking.\n", time, i);
	pthread_mutex_unlock(&data->info->end_mut);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:18:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/01 18:38:21 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long unsigned int	timestamp(t_data *data)
{
	struct timeval	t;

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

int	suspend(int time, t_data *data, int i)
{
	long unsigned int	usec_max;

	usec_max = now() + (long unsigned int)time;
	if (i % 2 == ((data->info->n + 1) % 2))
		usleep(900);
	while (should_continue(data) == 0)
	{
		if (now() >= usec_max)
			return (0);
		usleep(900);
	}
	return (2);
}

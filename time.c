/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:18:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/31 18:13:22 by irene            ###   ########.fr       */
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
	long unsigned int	time_sleep;
	long unsigned int	max_sleep;

	max_sleep = 900;
	usec_max = now() + (long unsigned int)time;
	if (i % 2 == ((data->info->n + 1) % 2))
		usleep(max_sleep);
	while (should_continue(data) == 0)
	{
		if (now() >= usec_max)
			return (0);
		time_sleep = (usec_max - now()) * 1000;
		if (time_sleep > max_sleep)
			time_sleep = max_sleep;
		usleep(time_sleep);
	}
	return (1);
}

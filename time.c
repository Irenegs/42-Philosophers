/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:18:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/26 18:23:50 by irgonzal         ###   ########.fr       */
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

void	suspend(int time)
{
	useconds_t	usec;

	usec = (long unsigned int)(time * 1000);
	usleep(usec);
}

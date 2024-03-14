/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/14 17:55:17 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_data *data, int i , int action)
{
	long time;
	
	time = timestamp(data);
	if (action == DEAD)
		printf("%ld %d died.\n", time, i);
	else if (end_simulation(data) == 0)
	{
		if (action == FORK)
			printf("%ld %d has taken a fork.\n", time, i);
		else if (action == EAT)
			printf("%ld %d is eating.\n", time, i);
		else if (action == SLEEP)
			printf("%ld %d is sleeping.\n", time, i);
		else if (action == THINK)
			printf("%ld %d is thinking.\n", time, i);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/09 17:47:17 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_data *data, int i , int action)
{
	long time;
	
	time = timestamp(data);
	if (action == DEAD)
		printf("%ld %d died.\n", time, i + 1);
	else if (end_simulation(data) == 0)
	{
		if (action == FORK)
			printf("%ld %d has taken a fork.\n", time, i + 1);
		else if (action == EAT)
			printf("%ld %d is eating.\n", time, i + 1);
		else if (action == SLEEP)
			printf("%ld %d is sleeping.\n", time, i + 1);
		else if (action == THINK)
			printf("%ld %d is thinking.\n", time, i + 1);
		//else if (action == LEAVES_FORK)
		//	printf("%ld %d leaves forks.\n", time, i + 1);
	}
}

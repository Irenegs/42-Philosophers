/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/04 16:56:33 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(int philo, int action)
{
	printf("TIMESTAMP %d", philo);
	if (action == 0)
		printf("TIMESTAMP %d died\n", philo);
	else if (action == 1)
		printf("TIMESTAMP %d has taken a fork\n", philo);
	else if (action == 2)
		printf("TIMESTAMP %d is eating\n", philo);
	else if (action == 3)
		printf("TIMESTAMP %d is sleeping\n", philo);
	else if (action == 4)
		printf("TIMESTAMP %d is thinking\n", philo);
}
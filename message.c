/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:52:36 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/20 22:19:22 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_philo *philo, int action)
{
	if (action == DEAD)
		printf("%ld %d died\n", since(philo->t0), philo->i);
	else if (action == FORK)
		printf("%ld %d has taken a fork\n", since(philo->t0), philo->i);
	else if (action == EAT)
		printf("%ld %d is eating\n", since(philo->t0), philo->i);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", since(philo->t0), philo->i);
	else if (action == THINK)
		printf("%ld %d is thinking\n", since(philo->t0), philo->i);
}
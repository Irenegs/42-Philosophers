/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::   	  */
/*   living.c										   :+:	  :+:	:+:   	  */
/*													+:+ +:+		 +:+	 	  */
/*   By: irgonzal <irgonzal@student.42.fr>		  +#+  +:+	   +#+			  */
/*												+#+#+#+#+#+   +#+		   	  */
/*   Created: 2024/02/20 20:44:03 by irgonzal		  #+#	#+#			 	  */
/*   Updated: 2024/03/26 12:59:20 by irgonzal		 ###   ########.fr	   	  */
/*																			  */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_data *data, int i)
{
	long unsigned int	since_last_meal;

	since_last_meal = since(data->philos[i].last_meal);
	display_message(data, i, SLEEP);
	if (data->philos[i].t_die <= data->philos[i].t_sleep + since_last_meal)
	{
		suspend(data->philos[i].t_die - since_last_meal, data);
		return (1);
	}
	if (suspend(data->philos[i].t_sleep, data) != 0)
		return (1);
	display_message(data, i, THINK);
	if (data->info->n % 2 == 1 && data->info->t_sleep == data->info->t_eat)
		usleep(1000);
	return (0);
}

void	*live(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	philo->last_meal = now();
	data = ((t_data *)(philo->data));
	if (philo->i % 2 == 1)
		usleep(1000);
	while (should_continue(data) == 0)
	{
		if (eating(data, philo->i) != 0)
			break ;
		if (should_continue(data) != 0 || sleeping(data, philo->i) != 0)
			break ;
	}
	if (should_continue(data) == 0)
		philo_died(data, philo->i);
	return (NULL);
}

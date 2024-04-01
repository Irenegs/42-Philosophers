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

int	eating(t_data *data, int i)
{
	int	ok;

	if (take_forks(data, i) != 0)
		return (1);
	display_message(data, i, EAT);
	manage_meals(data, i);
	if (data->info->t_eat >= data->info->t_die)
	{
		if (suspend(data->philos[i].t_die, data, i) == 0)
			return (1);
		return (2);
	}
	else
		ok = suspend(data->philos[i].t_eat, data, i);
	leave_forks(data, i);
	return (ok);
}

int	sleeping(t_data *data, int i)
{
	long unsigned int	since_last_meal;

	display_message(data, i, SLEEP);
	if (data->info->t_die <= data->info->t_eat + data->info->t_sleep)
	{
		since_last_meal = since(data->philos[i].last_meal);
		if (data->philos[i].t_die <= data->philos[i].t_sleep + since_last_meal)
		{
			suspend(data->philos[i].t_die - since_last_meal, data, i);
			return (1);
		}
	}
	if (suspend(data->philos[i].t_sleep, data, i) != 0)
		return (2);
	display_message(data, i, THINK);
	if (data->info->n % 2 == 1)
	{
		if (data->info->t_eat == data->info->t_sleep)
			usleep(2000);
	}
	return (0);
}

int	do_philo_things(t_data *data, int i)
{
	long signed int	max_wait;
	int				ret;

	max_wait = data->philos[i].t_die - data->philos[i].t_eat - \
		data->philos[i].t_sleep;
	if (max_wait > 0 && (i % 2 != 0))
		usleep((max_wait / 2) * 1000);
	while (1)
	{
		ret = eating(data, i);
		if (ret != 0)
			return (ret);
		if (should_continue(data) != 0)
			return (0);
		ret = sleeping(data, i);
		if (ret != 0)
			return (ret);
		if (should_continue(data) != 0)
			return (0);
	}
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
	if (do_philo_things(data, philo->i) == 1)
		philo_died(data, philo->i);
	return (NULL);
}

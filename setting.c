/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::   	  */
/*   setting.c										  :+:	  :+:	:+:   	  */
/*													+:+ +:+		 +:+	 	  */
/*   By: irgonzal <irgonzal@student.42.fr>		  +#+  +:+	   +#+			  */
/*												+#+#+#+#+#+   +#+		   	  */
/*   Created: 2024/02/20 08:45:37 by irgonzal		  #+#	#+#			 	  */
/*   Updated: 2024/03/26 17:37:59 by irgonzal		 ###   ########.fr	   	  */
/*																			  */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->info->n)
	{
		if (pthread_mutex_init(&(data->fork[i].mut), NULL) != 0)
			return (i);
		data->fork[i].used = 0;
		i++;
	}
	return (-1);
}

int	initialize_mutexes(t_data *data)
{
	int	forks_init;

	if (pthread_mutex_init(&(data->info->death_mut), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(data->info->end_mut), NULL) != 0)
		return (-2);
	if (pthread_mutex_init(&(data->info->meals_mut), NULL) != 0)
		return (-3);
	data->fork = malloc(data->info->n * sizeof(t_fork));
	if (!data->fork)
		return (-4);
	forks_init = initialize_forks(data);
	if (forks_init != -1)
		return (-(forks_init + 5));
	return (0);
}

void	set_info(t_info *info, int argc, char **argv)
{
	info->n = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->end = 0;
	if (argc == 6)
	{
		info->times = ft_atoi(argv[5]);
		info->meals = info->n * info->times;
	}
	else
	{
		info->times = -1;
		info->meals = 1;
	}
	info->dead = 0;
}

void	set_philo(t_data *data, int i)
{
	data->philos[i].i = i;
	data->philos[i].meals_av = data->info->times;
	data->philos[i].data = data;
	data->philos[i].t_die = data->info->t_die;
	data->philos[i].t_sleep = data->info->t_sleep;
	data->philos[i].t_eat = data->info->t_eat;
}

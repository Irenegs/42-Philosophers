/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::   	  */
/*   main.c											 :+:	  :+:	:+:   	  */
/*													+:+ +:+		 +:+	 	  */
/*   By: irgonzal <irgonzal@student.42.fr>		  +#+  +:+	   +#+			  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/01/29 22:36:06 by irgonzal		  #+#	#+#			 	  */
/*   Updated: 2024/03/26 13:22:50 by irgonzal		 ###   ########.fr	   	  */
/*																			  */
/* ************************************************************************** */

#include "philo.h"

int	end_simulation(t_data *data)
{
	int	check;

	pthread_mutex_lock(&(data->info->death_mut));
	check = data->info->dead;
	pthread_mutex_unlock(&(data->info->death_mut));
	if (check != 0)
		return (1);
	if (data->info->times == -1)
		return (0);
	pthread_mutex_lock(&(data->info->meals_mut));
	check = data->info->meals;
	pthread_mutex_unlock(&(data->info->meals_mut));
	if (check == 0)
		return (1);
	return (0);
}

static void	simulate(t_data *data)
{
	while (end_simulation(data) == 0)
		usleep(100);
	pthread_mutex_lock(&(data->info->end_mut));
	data->info->end = 1;
	pthread_mutex_unlock(&(data->info->end_mut));
}

void	create_philosophers(t_data *data)
{
	int	i;
	int	ret;

	data->philos = malloc(data->info->n * sizeof(t_philo));
	if (!data->philos)
		return ;
	i = -1;
	while (++i < data->info->n)
		set_philo(data, i);
	i = -1;
	while (++i < data->info->n)
	{
		ret = pthread_create(&data->philos[i].id, \
		NULL, live, &(data->philos[i]));
		if (ret != 0)
		{
			data->info->dead = 1;
			break ;
		}
	}
	if (i == data->info->n)
		simulate(data);
	while (i > 0)
		pthread_join(data->philos[--i].id, NULL);
	return ;
}

static void	clear(t_data *data)
{
	int	i;

	free(data->philos);
	pthread_mutex_destroy(&(data->info->death_mut));
	pthread_mutex_destroy(&(data->info->meals_mut));
	pthread_mutex_destroy(&(data->info->end_mut));
	i = 0;
	while (i < data->info->n)
	{
		pthread_mutex_destroy(&(data->fork[i].mut));
		i++;
	}
	free(data->fork);
	free(data->info);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (validate(argc, argv) != 0)
		return (1);
	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (2);
	data->info = malloc(1 * sizeof(t_info));
	if (!data->info)
	{
		free(data);
		return (3);
	}
	set_info(data->info, argc, argv);
	initialize_mutexes(data);
	create_philosophers(data);
	clear(data);
	return (0);
}

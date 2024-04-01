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
		usleep(900);
	pthread_mutex_lock(&(data->info->end_mut));
	data->info->end = 1;
	pthread_mutex_unlock(&(data->info->end_mut));
}

int	create_philosophers(t_data *data)
{
	int	i;
	int	ret;

	data->philos = malloc(data->info->n * sizeof(t_philo));
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->info->n)
		set_philo(data, i);
	i = -1;
	data->info->t0 = now();
	while (++i < data->info->n)
	{
		ret = pthread_create(&data->philos[i].id, \
		NULL, live, &(data->philos[i]));
		if (ret != 0)
		{
			pthread_mutex_lock(&(data->info->death_mut));
			data->info->dead = 1;
			pthread_mutex_unlock(&(data->info->death_mut));
			return (i + 2);
		}
	}
	simulate(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		value;

	if (validate(argc, argv) != 0)
		return (1);
	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (12);
	data->info = malloc(1 * sizeof(t_info));
	if (!data->info)
	{
		free(data);
		return (12);
	}
	set_info(data->info, argc, argv);
	value = initialize_mutexes(data);
	if (value == 0)
		value = create_philosophers(data);
	return (clear(data, value));
}

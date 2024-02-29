/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:45:37 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/29 19:42:45 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_info(t_info *info, int argc, char **argv)
{
    info->n = ft_atoi(argv[1]);
    info->t_die = ft_atoi(argv[2]);
    info->t_eat = ft_atoi(argv[3]);
    info->t_sleep = ft_atoi(argv[4]);
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
    pthread_mutex_init(&(info->mut), NULL);
}

void	set_philo(t_data *data, int i)
{
	data->philos[i].i = i;
	data->philos[i].last_meal = 0;
	data->philos[i].meals_av = data->info->times;
    data->philos[i].data = data;
}
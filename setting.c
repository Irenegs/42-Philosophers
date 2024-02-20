/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:45:37 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/20 20:55:32 by irgonzal         ###   ########.fr       */
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
        info->times = ft_atoi(argv[5]);
    else
        info->times = -1;
    info->dead = 0;
}

void	set_philo(t_data *data, int i)
{
	data->philos[i].i = i;
	data->philos[i].last_meal = 0;
	data->philos[i].meals_av = data->info->times;
    data->philos[i].fork.used = 0;
    data->philos[i].t_die = data->info->t_die;
    data->philos[i].t_eat = data->info->t_eat;
    data->philos[i].t_sleep = data->info->t_sleep;
    data->philos[i].data = data;
}
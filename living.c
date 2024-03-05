/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:44:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/05 20:37:28 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    manage_meals(t_data *data, int i)
{
    if (data->philos[i].meals_av <= 0)
        return ;
    data->philos[i].meals_av--;
    pthread_mutex_lock(&(data->info->mut));
    data->info->meals--;
    pthread_mutex_unlock(&(data->info->mut));
}

static void leave_forks(t_data *data, int i)
{
    display_message(data, i, LEAVES_FORK);
    data->philos[i].forks = 0;
    pthread_mutex_lock(&(data->fork[i].mut));
    data->fork[i].used = 0;
    pthread_mutex_unlock(&(data->fork[i].mut));
    pthread_mutex_lock(&(data->fork[i + 1 % data->info->n].mut));
    data->fork[i + 1 % data->info->n].used = 0;
	pthread_mutex_unlock(&(data->fork[i + 1 % data->info->n].mut));
}

static void    take_one_fork(t_data *data, int i, int f)
{
    pthread_mutex_lock(&(data->fork[(i + f) % data->info->n].mut));
    if (data->fork[(i + f) % data->info->n].used == 0)
    {
        //printf("Fork %d - %d\n", (i + f )% data->info->n, data->fork[(i + f) % data->info->n].used);
        data->fork[(i + f) % data->info->n].used = 1;
        data->philos[i].forks++;
        pthread_mutex_unlock(&(data->fork[(i + f) % data->info->n].mut));
        display_message(data, i, FORK);
    }
    else
    {
        //printf("Waiting %d %d\n", i, 1 + 1 * f);
        pthread_mutex_unlock(&(data->fork[i + f].mut));
        usleep(2);
    }
    is_philo_dead(data, i);
}

static void take_forks(t_data *data, int i)
{
    while(data->philos[i].forks != 1 && nobody_dead(data) == 0)
        take_one_fork(data, i, i % 2);
    while(data->philos[i].forks != 2 && nobody_dead(data) == 0)
        take_one_fork(data, i, i % 2 + 1);
}

int eating(t_data *data, int i)
{
    take_forks(data, i);
	if (end_simulation(data) == 1)
        return (1);
    display_message(data, i, EAT);
    manage_meals(data, i);
    if (since(data->philos[i].last_meal) + data->philos[i].t_eat > data->philos[i].t_die)
    {
        suspend(data->philos[i].t_die - since(data->philos[i].last_meal));
        philo_died(data, i);
        return (1);
    }
    suspend(data->philos[i].t_eat);
    data->philos[i].last_meal = now();
    leave_forks(data, i);
    return (0);
}

void sleeping(t_data *data, int i)
{
    display_message(data, i, SLEEP);
    if (data->philos[i].t_die <= data->philos[i].t_sleep)
    {
        suspend(data->philos[i].t_die);
        philo_died(data, i);
    }
    suspend(data->philos[i].t_sleep);
    display_message(data, i, THINK);
}

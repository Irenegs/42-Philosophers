/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:44:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/03/25 22:17:50 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void manage_meals(t_data *data, int i)
{
    data->philos[i].last_meal = now();
    if (data->philos[i].meals_av <= 0)
        return ;
    data->philos[i].meals_av--;
    pthread_mutex_lock(&(data->info->meals_mut));
    data->info->meals--;
    pthread_mutex_unlock(&(data->info->meals_mut));
}

static void leave_forks(t_data *data, int i)
{
    data->philos[i].forks = 0;
    pthread_mutex_lock(&(data->fork[i].mut));
    data->fork[i].used = 0;
    pthread_mutex_unlock(&(data->fork[i].mut));
    pthread_mutex_lock(&(data->fork[(i + 1) % data->info->n].mut));
    data->fork[(i + 1) % data->info->n].used = 0;
	pthread_mutex_unlock(&(data->fork[(i + 1) % data->info->n].mut));
}

static void    take_one_fork(t_data *data, int i, int f)
{
    pthread_mutex_lock(&(data->fork[f].mut));
    if (data->fork[f].used == 0)
    {
        data->fork[f].used = 1;
        pthread_mutex_unlock(&(data->fork[f].mut));
        data->philos[i].forks++;
        display_message(data, i, FORK);
    }
    else
    {
        pthread_mutex_unlock(&(data->fork[f].mut));
        usleep(2);
    }
    is_philo_dead(data, i);
}

static void take_forks(t_data *data, int i)
{
    while(data->philos[i].forks != 1 && is_philo_dead(data, i) == 0)
        take_one_fork(data, i, (i + (i + 1) % 2) % data->info->n);
    while(data->philos[i].forks != 2 && is_philo_dead(data, i) == 0)
        take_one_fork(data, i, (i + i % 2) % data->info->n);
}

int eating(t_data *data, int i)
{
    take_forks(data, i);
    if (is_philo_dead(data, i) != 0)
        return (1);
    display_message(data, i, EAT);
    manage_meals(data, i);
    suspend(data->philos[i].t_eat);
    data->philos[i].last_meal = now();
    leave_forks(data, i);
    return (0);
}

int sleeping(t_data *data, int i)
{
    display_message(data, i, SLEEP);
    if (data->philos[i].t_die <= data->philos[i].t_sleep)
    {
        suspend(data->philos[i].t_die);
        return (1);
    }
    suspend(data->philos[i].t_sleep);
    display_message(data, i, THINK);
    if (data->info->n % 2 == 1)
        suspend(5);
    return (0);
}

void    *live(void *arg)
{
    t_philo  *philo;
    t_data  *data;
    
    if (!arg)
        return (NULL);
    philo = (t_philo *)arg;
    philo->t0 = now();
    data = ((t_data *)(philo->data));
    while (should_continue(data) == 0)
    {
        if (eating(data, philo->i) == 0)
        {
            if (should_continue(data) != 0 || sleeping(data, philo->i) == 1)
                break;
        }
        else
            break ;
    }
    if (should_continue(data) == 0)
        philo_died(data, philo->i);
    return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:44:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/20 22:22:26 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    eating(t_philo *philo)
{
    //eat: coger tenedores comprobar si muere esperando, comer, lastmeal, soltar tenedores
	pthread_mutex_lock(&(philo->fork.mut));
	philo->fork.used = 1;
    display_message(philo, FORK);
	pthread_mutex_lock(&(((t_data *)(philo->data))->philos[philo->i + 1].fork.mut));
    display_message(philo, FORK);
    display_message(philo, EAT);
    philo->meals_av--;//hacer que el bucle sea infinito, no forzando al 0
	philo->fork.used = 0;
    pthread_mutex_unlock(&(philo->fork.mut));
	pthread_mutex_unlock(&(((t_data *)(philo->data))->philos[philo->i + 1].fork.mut));
	suspend(philo->t_eat);
    philo->last_meal = now();
}

void    sleeping(t_philo *philo)
{
    display_message(philo, SLEEP);
    if (philo->t_die <= philo->t_sleep)
    {
        suspend(philo->t_die);
        ((t_data *)(philo->data))->info->dead++;
        display_message(philo, DEAD);
        return ;
    }
    suspend(philo->t_sleep);
    display_message(philo, THINK);
}
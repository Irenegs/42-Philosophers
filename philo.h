/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:19:12 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/05 21:54:18 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3

typedef struct s_info
{
	int	sleep;
	int	n;
	int eat;
	int	die;
	int times;
}		t_info;

typedef struct s_philo
{
	pthread_t		id;
	int				last_meal;
	int				meals_av;
	pthread_mutex_t	fork;
	int				state;
}					t_philo;

typedef struct s_data
{
	t_philo	*philos;
	t_info	*info;
}			t_data;

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		validate(int argc, char **argv);
void	display_message(int philo, int action);
void	set_info(t_info *info, int argc, char **argv);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:19:12 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/20 20:46:22 by irgonzal         ###   ########.fr       */
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
# define FORK 4

typedef struct s_info
{
	int	t_sleep;
	int	n;
	int t_eat;
	int	t_die;
	int times;
	int dead;
}		t_info;

typedef struct s_fork
{
	pthread_mutex_t	mut;
	int				used;
}	t_fork;

typedef struct s_philo
{
	pthread_t	id;
	t_fork		fork;
	int			last_meal;
	int			meals_av;
	int			i;
	int			t_sleep;
	int 		t_eat;
	int			t_die;
	void		*data;
	long int	t0;
}					t_philo;

typedef struct s_data
{
	t_philo	*philos;
	t_info	*info;
}			t_data;

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		validate(int argc, char **argv);
void	display_message(t_philo *philo, int action);
void	set_info(t_info *info, int argc, char **argv);
void	set_philo(t_data *data, int i);
int	philo_died(t_philo philo);
void	suspend(int time);
long int	since(long int t0);
long int	now(void);
void    eating(t_philo *philo);
void    sleeping(t_philo *philo);
#endif

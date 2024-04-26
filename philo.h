/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:19:12 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/01 19:25:01 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3
# define FORK 4

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	mut;
}	t_fork;

typedef struct s_info
{
	long unsigned int	t0;
	long unsigned int	t_sleep;
	long unsigned int	t_eat;
	long unsigned int	t_die;
	int					n;
	int					times;
	int					dead;
	int					meals;
	int					end;
	pthread_mutex_t		death_mut;
	pthread_mutex_t		meals_mut;
	pthread_mutex_t		end_mut;
}		t_info;

typedef struct s_philo
{
	pthread_t			id;
	long unsigned int	last_meal;
	int					meals_av;
	int					i;
	int					forks;
	void				*data;
	long unsigned int	t_sleep;
	long unsigned int	t_eat;
	long unsigned int	t_die;
}					t_philo;

typedef struct s_data
{
	t_philo	*philos;
	t_info	*info;
	t_fork	*fork;
}			t_data;

char				*ft_itoa(int n);
int					ft_atoi(const char *str);
int					validate(int argc, char **argv);

void				set_info(t_info *info, int argc, char **argv);
void				set_philo(t_data *data, int i);
int					initialize_mutexes(t_data *data);
int					clear(t_data *data, int value);

int					suspend(int time, t_data *data, int i);
long unsigned int	timestamp(t_data *data);
long unsigned int	since(long int t0);
long unsigned int	now(void);

int					eating(t_data *data, int i);
int					take_forks(t_data *data, int i);
void				leave_forks(t_data *data, int i);
void				manage_meals(t_data *data, int i);
int					sleeping(t_data *data, int i);
void				*live(void *arg);

void				philo_died(t_data *data, int i);
int					is_philo_dead(t_data *data, int i);
int					should_continue(t_data *data);
int					end_simulation(t_data *data);

int					display_message(t_data *data, int i, int action);
#endif

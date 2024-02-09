/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:27:57 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/04 17:52:33 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int arg_isint(char *str, int value)
{
    char    *numberstr;
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i]  == '0')
        i++;
    if (str[i] == '\0' && value == 0)
        return (0);
    numberstr = ft_itoa(value);
    if (!numberstr)
        return (1);
    if (numberstr[0] == '-')
    {
        j++;
        i--;
    }
    while (str[i + j] == numberstr[j] && numberstr[j] != '\0')
        j++;
    i = str[i + j] - numberstr[j];
    free(numberstr);
    return (i);
}

int	validate(int argc, char **argv)
{
	int i;
	int n;
	
	if (argc < 5 || argc > 6)
	{
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		n = ft_atoi(argv[i]);
		if (arg_isint(argv[i], n) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void    set_info(t_info *info, int argc, char **argv)
{
    info->n = ft_atoi(argv[1]);
    info->die = ft_atoi(argv[2]);
    info->eat = ft_atoi(argv[3]);
    info->sleep = ft_atoi(argv[4]);
    if (argc == 6)
        info->times = ft_atoi(argv[5]);
    else
        info->times = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:36:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/01/29 22:55:21 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int arg_isint(char *str, int value)
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
	i = 0;
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

int	main(int argc, char **argv)
{
	if (validate(argc, argv) != 0)
		exit(1);
	exit(0);
}
/*
- Idea: estructura con la información de argv
- Los filosofos son estructuras o directamente hilos?

*/
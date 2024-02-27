/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:27:57 by irgonzal          #+#    #+#             */
/*   Updated: 2024/02/27 20:03:40 by irgonzal         ###   ########.fr       */
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
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		n = ft_atoi(argv[i]);
		if (arg_isint(argv[i], n) != 0 || n < 0)
			return (1);
		i++;
	}
	return (0);
}

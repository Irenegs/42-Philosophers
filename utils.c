/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:38:00 by irgonzal          #+#    #+#             */
/*   Updated: 2024/01/29 22:45:24 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	nbrlen(long long int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		l++;
		n /= 10;
	}
	return (l);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*res;

	l = nbrlen(n);
	res = malloc((l + 1 + (n < 0)) * sizeof(char));
	if (!res)
		return (NULL);
	res[l + (n < 0)] = '\0';
	if (n < 0)
		res[0] = '-';
	while (--l >= 0)
	{
		res[l + (n < 0)] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (res);
}

static int	ft_isspace(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;
	int			s;

	i = 0;
	s = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s = -1;
		i++;
	}
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n > 2147483647 && s == 1)
			return (-1);
		if (n > 2147483648 && s == -1)
			return (0);
		i++;
	}
	return ((int )(n * s));
}

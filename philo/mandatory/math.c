/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:45:25 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/21 01:17:58 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	negative;
	int	res;

	negative = 1;
	res = 0;
	while ((8 < *str && *str < 14) || *str == 32)
		str++;
	if (*str == '-' )
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			break ;
		res *= 10;
		res += negative * (*str - 48);
		str++;
	}
	return (res);
}

float	time_diff(struct timeval *start, struct timeval *end)
{
	float	res;

	res = 1e+3 * (end->tv_sec - start->tv_sec);
	res += 1e-3 * (end->tv_usec - start->tv_usec);
	return (res);
}

long long	ft_atoi_long(const char *str)
{
	int			negative;
	long long	res;

	negative = 1;
	res = 0;
	while ((8 < *str && *str < 14) || *str == 32)
		str++;
	if (*str == '-' )
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			break ;
		res *= 10;
		res += negative * (*str - 48);
		str++;
	}
	return (res);
}

int	all_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

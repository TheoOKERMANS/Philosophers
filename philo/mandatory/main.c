/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:11 by tokerman          #+#    #+#             */
/*   Updated: 2022/07/12 20:19:28 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
norminette
tests
faire pour que pour 4 args ca fonctionne
faire le makefile propre
faire que des qu'un philo meurt le programme s'arrete
verifier le truc des 10ms apres la mort car la on dit qu'il meurt des qu'il a les fourchettes
*/

#include "../includes/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	res;

	res = 0;
	if (str)
	{
		while (*str != '\0')
		{
			res++;
			str++;
		}	
	}
	return (res);
}

long long	ft_atoi_long(const char *str)
{
	int	negative;
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

int all_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	test_args(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		if (all_num(argv[i]) == 0)
			return (0);
		if (ft_strlen(argv[i]) > 10)
			return (0);
		if (ft_atoi_long(argv[i]) > 2147483647)
			return (0);
		i++;
	}
	return (1);
	(void)argv;
}

int	main(int argc, char **argv)
{
	if (test_args(argc, argv) == 1)
	{
		philo(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), ft_atoi(argv[5]));
	}
	else
	{
		write(2, "Error\n", 6);
	}
	return (1);
	(void)argc;
	(void)argv;
}

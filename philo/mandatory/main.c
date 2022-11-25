/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:11 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/25 09:13:32 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	test_args_value(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1)
	{
		write(2, "Not enough philosophers\n", 25);
		return (0);
	}
	if (ft_atoi(argv[2]) < 1)
	{
		write(2, "Time to die must be higher than 0\n", 34);
		return (0);
	}
	if (ft_atoi(argv[3]) < 1)
	{
		write(2, "Time to eat must be higher than 0\n", 34);
		return (0);
	}
	if (ft_atoi(argv[4]) < 1)
	{
		write(2, "Time to sleep must be higher than 0\n", 36);
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		write(2, "Number of times each philosopher must", 37);
		write(2, " eat must be higher than 0\n", 27);
		return (0);
	}
	return (1);
}

int	test_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (all_num(argv[i]) == 0)
		{
			write(2, "Not a unsigned int\n", 13);
			return (0);
		}
		if (ft_strlen(argv[i]) > 10)
		{
			write(2, "Number too long\n", 16);
			return (0);
		}
		if (ft_atoi_long(argv[i]) > 2147483647)
		{
			write(2, "Number is highter than INT MAX\n", 31);
			return (0);
		}
		i++;
	}
	return (test_args_value(argc, argv));
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Not enought arguments\n", 22);
		return (0);
	}
	if (test_args(argc, argv) == 1)
	{
		if (argc == 6)
			philo(argv, ft_atoi(argv[5]));
		else if (argc == 5)
			philo(argv, 2147483647);
	}
	return (1);
}

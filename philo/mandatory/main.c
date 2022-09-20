/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:11 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/20 18:50:35 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	test_args(int argc, char **argv)
{
	int	i;

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
		if (argc == 6)
			philo(argv, ft_atoi(argv[5]));
		else if (argc == 5)
			philo(argv, 2147483647);
	}
	else
	{
		write(2, "Error\n", 6);
	}
	return (1);
	(void)argc;
	(void)argv;
}

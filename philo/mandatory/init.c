/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:54:49 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/25 09:48:31 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_id	*init_all_tid(char **argv, t_game *game)
{
	t_id	*res;
	int		i;

	res = NULL;
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		game->fork_lst[i] = malloc(sizeof(t_fork));
		pthread_mutex_init(&(game->fork_lst[i]->mutex), NULL);
		game->fork_lst[i]->id = i + 1;
		add_back_tid(&res, new_tid(i + 1, game));
		gettimeofday(&((get_id_by_id(res, i + 1)->lst_eat)), NULL);
		pthread_mutex_init(&(get_id_by_id(res, i + 1)->eatcount_mtx), NULL);
		pthread_mutex_init(&(get_id_by_id(res, i + 1)->lsteat_mtx), NULL);
	}
	return (res);
}

t_id	*init_all(char **argv, int num_phi_eat)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->num_philo = ft_atoi(argv[1]);
	game->time2die = ft_atoi(argv[2]);
	game->time2eat = ft_atoi(argv[3]);
	game->time2sleep = ft_atoi(argv[4]);
	game->num_phi_eat = num_phi_eat;
	game->fork_lst = malloc(sizeof(t_fork *) * (ft_atoi(argv[1])));
	game->philo_died = 0;
	pthread_mutex_init(&(game->prt_mtx), NULL);
	pthread_mutex_init(&(game->eat_mtx), NULL);
	pthread_mutex_init(&(game->philodied_mtx), NULL);
	return (init_all_tid(argv, game));
}

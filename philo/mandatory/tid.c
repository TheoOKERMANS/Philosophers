/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:41:43 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/20 18:47:28 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_id	*lst_tid(t_id *tid)
{
	t_id	*temp;

	if (tid)
	{
		temp = tid;
		while (temp->next != NULL)
			temp = temp->next;
		return (temp);
	}
	else
		return (NULL);
}

t_id	*new_tid(int id, t_game *game)
{
	t_id	*res;

	res = malloc(sizeof(t_id));
	res->id = id;
	res->eat_count = 0;
	res->next = NULL;
	res->game = game;
	return (res);
}

t_id	*get_id_by_id(t_id *tid, int id)
{
	t_id	*temp;

	temp = tid;
	while (temp)
	{
		if (temp->id == id)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_id	*init_all(char **argv, int num_phi_eat)
{
	t_game	*game;
	t_id	*res;
	int		i;

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
	res = NULL;
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		game->fork_lst[i] = malloc(sizeof(t_fork));
		game->fork_lst[i]->id = i + 1;
		pthread_mutex_init(&(game->fork_lst[i]->mutex), NULL);
		add_back_tid(&res, new_tid(i + 1, game));
		gettimeofday(&((get_id_by_id(res, i + 1)->lst_eat)), NULL);
	}
	return (res);
}

void	add_back_tid(t_id **tid, t_id *new)
{
	t_id	*temp;

	if (tid)
	{
		if (*tid)
		{
			temp = lst_tid(*tid);
			temp->next = new;
		}
		else
		{
			*tid = new;
		}
	}
}

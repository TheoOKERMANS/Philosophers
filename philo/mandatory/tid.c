/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:41:43 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/21 01:52:51 by tokerman         ###   ########.fr       */
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

int	tid_finish_eat(t_id *tmp)
{
	int	res;

	pthread_mutex_lock(&(tmp->eatcount_mtx));
	if (tmp->eat_count < tmp->game->num_phi_eat)
		res = 0;
	else
		res = 1;
	pthread_mutex_unlock(&(tmp->eatcount_mtx));
	return (res);
}

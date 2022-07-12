/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:09:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/07/12 19:18:30 by tokerman         ###   ########.fr       */
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

t_id	*new_tid(int id, t_game *game)
{
	t_id	*res;

	res = malloc(sizeof(t_id));
	res->id	= id;
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

t_fork	*get_fork_by_id(t_game *game, int id)
{
	if (id < 1)
		return (game->fork_lst[game->numPhilo - 1]);
	else if (id > game->numPhilo)
		return (game->fork_lst[0]);
	else
		return (game->fork_lst[id - 1]);
}

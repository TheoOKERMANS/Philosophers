/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:32:52 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/25 10:43:29 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*get_first_fork(t_id *tid)
{
	if (tid->id % 2 == 0)
		return (&(tid->game->fork_lst[tid->id - 1]->mutex));
	else
	{
		if (tid->id == tid->game->num_philo)
			return (&(tid->game->fork_lst[0]->mutex));
		else
			return (&(tid->game->fork_lst[tid->id]->mutex));
	}
}

pthread_mutex_t	*get_second_fork(t_id *tid)
{
	if (tid->id % 2 == 0)
	{
		if (tid->id == tid->game->num_philo)
			return (&(tid->game->fork_lst[0]->mutex));
		else
			return (&(tid->game->fork_lst[tid->id]->mutex));
	}
	else
		return (&(tid->game->fork_lst[tid->id - 1]->mutex));
}

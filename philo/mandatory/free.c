/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:25:28 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/20 18:27:30 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_tid(t_id *tid)
{
	if (tid->next)
		free_tid(tid->next);
	free(tid);
}

void	free_all(t_id *tid)
{
	int	i;

	i = 0;
	while (i < tid->game->num_philo)
	{
		pthread_mutex_destroy(&(tid->game->fork_lst[i]->mutex));
		free(tid->game->fork_lst[i]);
		i++;
	}
	free(tid->game->fork_lst);
	pthread_mutex_destroy(&(tid->game->prt_mtx));
	pthread_mutex_destroy(&(tid->game->eat_mtx));
	free(tid->game);
	free_tid(tid);
}

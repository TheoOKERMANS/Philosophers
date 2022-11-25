/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoeat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:23:19 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/25 11:12:27 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_incr_eat(t_id *tid)
{
	pthread_mutex_lock(&(tid->eatcount_mtx));
	tid->eat_count++;
	if (tid->eat_count < tid->game->num_phi_eat)
	{
		pthread_mutex_unlock(&(tid->eatcount_mtx));
		mutex_print(tid, "is sleeping");
		split_sleep(tid, tid->game->time2sleep);
		mutex_print(tid, "is thinking");
		if (tid->game->time2eat >= tid->game->time2sleep)
			split_sleep(tid, tid->game->time2eat - tid->game->time2sleep + 1);
	}
	else
		pthread_mutex_unlock(&(tid->eatcount_mtx));
}

int	check_lsteat(t_id *tid)
{
	int	res;
	struct timeval	time;

	res = 0;
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&(tid->lsteat_mtx));
	if (time_diff(&(tid->lst_eat), &(time)) > tid->game->time2die)
		res = 1;
	pthread_mutex_unlock(&(tid->lsteat_mtx));
	return (res);
}
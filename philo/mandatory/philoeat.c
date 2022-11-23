/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoeat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:23:19 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/23 12:25:11 by tokerman         ###   ########.fr       */
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
	}
	else
		pthread_mutex_unlock(&(tid->eatcount_mtx));
}

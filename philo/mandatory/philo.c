/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:06:03 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/20 18:51:39 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_eat(t_id *tid)
{
	pthread_mutex_lock(&(get_fork_by_id(tid->game, tid->id - 1)->mutex));
	mutex_print(tid, "has taken a fork");
	pthread_mutex_lock(&(get_fork_by_id(tid->game, tid->id)->mutex));
	mutex_print(tid, "has taken a fork");
	mutex_print(tid, "is eating");
	pthread_mutex_lock(&(tid->game->eat_mtx));
	gettimeofday(&(tid->lst_eat), NULL);
	pthread_mutex_unlock(&(tid->game->eat_mtx));
	split_sleep(tid, tid->game->time2eat);
	pthread_mutex_unlock(&(get_fork_by_id(tid->game, tid->id - 1)->mutex));
	pthread_mutex_unlock(&(get_fork_by_id(tid->game, tid->id)->mutex));
}

void	*thread_func(void *args)
{
	t_id	*tid;

	tid = (t_id *)args;
	if (tid->id % 2 == 0)
		usleep(15000);
	while (tid->eat_count < tid->game->num_phi_eat)
	{
		thread_eat(tid);
		tid->eat_count++;
		if (tid->eat_count < tid->game->num_phi_eat)
		{
			mutex_print(tid, "is sleeping");
			split_sleep(tid, tid->game->time2sleep);
			mutex_print(tid, "is thinking");
		}
	}
	return (NULL);
}

void	waiting_allchild(t_id *tid)
{
	int	i;

	i = 1;
	while (i <= tid->game->num_philo)
	{
		pthread_join(get_id_by_id(tid, i)->thread, NULL);
		i++;
	}
	free_all(tid);
}

void	waiting_death(t_id *tid)
{
	int				i;
	struct timeval	time;

	while (tid->game->philo_died == 0)
	{
		i = 0;
		while (++i < tid->game->num_philo)
		{
			pthread_mutex_lock(&(tid->game->eat_mtx));
			gettimeofday(&time, NULL);
			if (time_diff(&(get_id_by_id(tid, i)->lst_eat), &(time))
				> tid->game->time2die)
			{
				mutex_print(tid, "died");
				tid->game->philo_died = 1;
			}
			pthread_mutex_unlock(&(tid->game->eat_mtx));
			usleep(100);
		}
		if (all_eat(tid))
			break ;
	}
}

void	philo(char **argv, int num_phi_eat)
{
	t_id	*temp;
	t_id	*tid;
	int		i;

	tid = init_all(argv, num_phi_eat);
	i = 1;
	gettimeofday(&(tid->game->start), NULL);
	while (i <= ft_atoi(argv[1]))
	{
		temp = get_id_by_id(tid, i);
		pthread_create(&(temp->thread), NULL, thread_func, temp);
		i++;
	}
	waiting_death(tid);
	waiting_allchild(tid);
	return ;
}

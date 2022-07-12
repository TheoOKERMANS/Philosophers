/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:06:03 by tokerman          #+#    #+#             */
/*   Updated: 2022/07/12 19:41:27 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

float	time_diff(struct timeval *start, struct timeval *end)
{
    return 1e+3*(end->tv_sec - start->tv_sec) + 1e-3*(end->tv_usec - start->tv_usec);
}

void	*thread_func(void *args)
{
	t_id	*tid = (t_id *)args;
	struct timeval	start;
	struct timeval	update;
	struct timeval	end;
	while (tid->eat_count < tid->game->numPhiEat)
	{
		gettimeofday(&start, NULL);
		printf("%0.0fms %d is thinking\n", time_diff(&(tid->game->start), &start), tid->id);
		pthread_mutex_lock(&(get_fork_by_id(tid->game, tid->id - 1)->mutex));
		gettimeofday(&update, NULL);
		printf("%0.0fms %d has taken a fork\n", time_diff(&(tid->game->start), &update), tid->id);
		pthread_mutex_lock(&(get_fork_by_id(tid->game, tid->id)->mutex));
		gettimeofday(&update, NULL);
		printf("%0.0fms %d has taken a fork\n", time_diff(&(tid->game->start), &update), tid->id);
		gettimeofday(&end, NULL);
		if (time_diff(&start, &end) > tid->game->time2die)
		{
			pthread_mutex_unlock(&(get_fork_by_id(tid->game, tid->id - 1)->mutex));
			pthread_mutex_unlock(&(get_fork_by_id(tid->game, tid->id)->mutex));
			printf("%0.0fms %d died\n", time_diff(&(tid->game->start), &end), tid->id);
			pthread_exit(NULL);
		}
		gettimeofday(&update, NULL);
		printf("%0.0fms %d is eating\n", time_diff(&(tid->game->start), &update), tid->id);
		usleep(tid->game->time2eat * 1000);
		pthread_mutex_unlock(&(get_fork_by_id(tid->game, tid->id - 1)->mutex));
		pthread_mutex_unlock(&(get_fork_by_id(tid->game, tid->id)->mutex));
		tid->eat_count++;
		if (tid->eat_count < tid->game->numPhiEat)
		{
			gettimeofday(&start, NULL);
			printf("%0.0fms %d is sleeping\n", time_diff(&(tid->game->start), &start), tid->id);
			usleep(tid->game->time2sleep * 1000);
		}
	}
	pthread_exit(NULL);
	(void)args;
	return (NULL);
}

t_id	*init_all(int numPhilo, int time2die, int time2eat, int time2sleep, int numPhiEat)
{
	t_game	*game;
	t_id	*res;
	int		i;

	game = malloc(sizeof(t_game));
	game->numPhilo = numPhilo;
	game->time2die = time2die;
	game->time2eat = time2eat;
	game->time2sleep = time2sleep;
	game->numPhiEat = numPhiEat;
	game->fork_lst = malloc(sizeof(t_fork *) * (numPhilo));
	
	res = NULL;
	i = 0;
	while (i < numPhilo)
	{
		game->fork_lst[i] = malloc(sizeof(t_fork));
		game->fork_lst[i]->id = i + 1;
		pthread_mutex_init(&(game->fork_lst[i]->mutex), NULL);
		add_back_tid(&res, new_tid(i + 1, game));
		i++;
	}
	return (res);
}

void	philo(int numPhilo, int time2die, int time2eat, int time2sleep, int numPhiEat)
{
	pthread_t	thread1[numPhilo];
	t_id	*tid;
	tid = init_all(numPhilo, time2die, time2eat, time2sleep, numPhiEat);
	int i = 1;
	gettimeofday(&(tid->game->start), NULL);
	while (i <= numPhilo)
	{
		pthread_create(&(thread1[i - 1]), NULL, thread_func, get_id_by_id(tid, i));
		i++;
	}
	i = 1;
	while (i <= numPhilo)
	{
		pthread_join(thread1[i - 1], NULL);
		i++;
	}
	return ;
}

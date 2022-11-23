/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:06:03 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/23 12:25:06 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_eat(t_id *tid)
{
	pthread_mutex_t	*m1;
	pthread_mutex_t	*m2;

	m1 = &(tid->game->fork_lst[tid->id - 1]->mutex);
	if (tid->id == tid->game->num_philo)
		m2 = &(tid->game->fork_lst[0]->mutex);
	else
		m2 = &(tid->game->fork_lst[tid->id]->mutex);
	pthread_mutex_lock(m1);
	mutex_print(tid, "has taken a fork");
	if (tid->game->num_philo == 1)
	{
		split_sleep(tid, tid->game->time2die);
		pthread_mutex_unlock(m1);
		return ;
	}
	pthread_mutex_lock(m2);
	mutex_print(tid, "has taken a fork");
	mutex_print(tid, "is eating");
	pthread_mutex_lock(&(tid->game->eat_mtx));
	gettimeofday(&(tid->lst_eat), NULL);
	pthread_mutex_unlock(&(tid->game->eat_mtx));
	split_sleep(tid, tid->game->time2eat);
	pthread_mutex_unlock(m1);
	pthread_mutex_unlock(m2);
}

void	*thread_func(void *args)
{
	t_id	*tid;

	tid = (t_id *)args;
	if (tid->id % 2 == 0)
		usleep(tid->game->time2eat / 2 * 1000);
	pthread_mutex_lock(&(tid->eatcount_mtx));
	while (tid->eat_count < tid->game->num_phi_eat)
	{
		pthread_mutex_unlock(&(tid->eatcount_mtx));
		thread_eat(tid);
		pthread_mutex_lock(&(tid->game->philodied_mtx));
		if (tid->game->philo_died == 1)
		{
			pthread_mutex_unlock(&(tid->game->philodied_mtx));
			return (NULL);
		}
		pthread_mutex_unlock(&(tid->game->philodied_mtx));
		philo_incr_eat(tid);
		pthread_mutex_lock(&(tid->eatcount_mtx));
	}
	pthread_mutex_unlock(&(tid->eatcount_mtx));
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
	t_id			*tmp;

	pthread_mutex_lock(&(tid->game->philodied_mtx));
	while (tid->game->philo_died == 0)
	{
		pthread_mutex_unlock(&(tid->game->philodied_mtx));
		i = 0;
		while (++i <= tid->game->num_philo)
		{
			pthread_mutex_lock(&(tid->game->eat_mtx));
			gettimeofday(&time, NULL);
			tmp = get_id_by_id(tid, i);
			if (tid_finish_eat(tmp) == 0
				&& time_diff(&(tmp->lst_eat), &(time)) > tid->game->time2die)
				philo_died(tid);
			pthread_mutex_unlock(&(tid->game->eat_mtx));
			usleep(100);
		}
		if (all_eat(tid))
			return ;
		pthread_mutex_lock(&(tid->game->philodied_mtx));
	}
	pthread_mutex_unlock(&(tid->game->philodied_mtx));
}

void	philo(char **argv, int num_phi_eat)
{
	t_id	*temp;
	t_id	*tid;
	int		i;
	int		nb_philo;

	tid = init_all(argv, num_phi_eat);
	i = 1;
	gettimeofday(&(tid->game->start), NULL);
	nb_philo = ft_atoi(argv[1]);
	temp = tid;
	while (i <= nb_philo)
	{
		pthread_create(&(temp->thread), NULL, thread_func, temp);
		temp = temp->next;
		i++;
	}
	waiting_death(tid);
	waiting_allchild(tid);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:06:03 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/25 17:17:00 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_eat(t_id *tid)
{
	//mutex_print(tid, "enter thread eat");
	pthread_mutex_lock(tid->f1);
	mutex_print(tid, "has taken a fork");
	if (tid->game->num_philo == 1)
	{
		split_sleep(tid, tid->game->time2die);
		pthread_mutex_unlock(tid->f1);
		return ;
	}
	pthread_mutex_lock(tid->f2);
	mutex_print(tid, "has taken a fork");
	mutex_print(tid, "is eating");
	pthread_mutex_lock(&(tid->lsteat_mtx));
	gettimeofday(&(tid->lst_eat), NULL);
	pthread_mutex_unlock(&(tid->lsteat_mtx));
	split_sleep(tid, tid->game->time2eat);
	//mutex_print(tid, "unlock mutex");
	pthread_mutex_unlock(tid->f1);
	pthread_mutex_unlock(tid->f2);
	//mutex_print(tid, "ended thread eat");
}

void	*thread_func(void *args)
{
	t_id	*tid;

	tid = (t_id *)args;
	if (tid->id % 2 == 0)
		usleep((tid->game->time2eat * 1000) / 2);
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
		//mutex_print(tid, "ended thinking");
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
	t_id			*tmp;

	while (1)
	{
		i = 0;
		while (++i <= tid->game->num_philo)
		{
			tmp = get_id_by_id(tid, i);
			if (check_lsteat(tmp) && tid_finish_eat(tmp) == 0)
				return (philo_died(tmp));
		}
		if (all_eat(tid))
			return ;
		usleep(1000);
	}
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

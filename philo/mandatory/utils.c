/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:09:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/28 10:09:19 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_died(t_id *tid)
{
	mutex_print(tid, "died");
	pthread_mutex_lock(&(tid->game->philodied_mtx));
	tid->game->philo_died = 1;
	pthread_mutex_unlock(&(tid->game->philodied_mtx));
	pthread_mutex_unlock(&(tid->lsteat_mtx));
}

void	mutex_print(t_id *tid, char *msg)
{
	struct timeval	time;

	pthread_mutex_lock(&(tid->game->prt_mtx));
	if (tid->game->philo_died == 0)
	{
		gettimeofday(&time, NULL);
		printf("%0.0f ", time_diff(&(tid->game->start), &time));
		printf("%d %s\n", tid->id, msg);
	}
	pthread_mutex_unlock(&(tid->game->prt_mtx));
}

void	split_sleep(t_id *tid, int time)
{
	usleep(time * 1000);
	(void)tid;
}

size_t	ft_strlen(const char *str)
{
	size_t	res;

	res = 0;
	if (str)
	{
		while (*str != '\0')
		{
			res++;
			str++;
		}	
	}
	return (res);
}

int	all_eat(t_id *tid)
{
	int	i;

	i = 0;
	while (tid->game->num_phi_eat != -1 && i < tid->game->num_philo)
	{
		pthread_mutex_lock(&(get_id_by_id(tid, i + 1)->eatcount_mtx));
		if (get_id_by_id(tid, i + 1)->eat_count >= tid->game->num_phi_eat)
		{
			pthread_mutex_unlock(&(get_id_by_id(tid, i + 1)->eatcount_mtx));
			i++;
			continue ;
		}
		pthread_mutex_unlock(&(get_id_by_id(tid, i + 1)->eatcount_mtx));
		break ;
	}
	if (i == tid->game->num_philo)
		return (1);
	return (0);
}

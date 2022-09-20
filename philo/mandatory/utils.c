/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:09:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/20 18:48:18 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_fork	*get_fork_by_id(t_game *game, int id)
{
	if (id < 1)
		return (game->fork_lst[game->num_philo - 1]);
	else if (id > game->num_philo)
		return (game->fork_lst[0]);
	else
		return (game->fork_lst[id - 1]);
}

void	mutex_print(t_id *tid, char *msg)
{
	struct timeval	time;

	pthread_mutex_lock(&(tid->game->prt_mtx));
	if (tid->game->philo_died == 0)
	{
		gettimeofday(&time, NULL);
		printf("%0.0fms ", time_diff(&(tid->game->start), &time));
		printf("%d %s\n", tid->id, msg);
	}
	pthread_mutex_unlock(&(tid->game->prt_mtx));
}

void	split_sleep(t_id *tid, int time)
{
	struct timeval	start;
	struct timeval	temp;

	gettimeofday(&start, NULL);
	while (tid->game->philo_died == 0)
	{
		gettimeofday(&temp, NULL);
		if (time_diff(&start, &temp) >= time)
			break ;
		usleep(200);
	}
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
	while (tid->game->num_phi_eat != -1 && i < tid->game->num_philo
		&& get_id_by_id(tid, i + 1)->eat_count >= tid->game->num_phi_eat)
		i++;
	if (i == tid->game->num_philo)
		return (1);
	return (0);
}

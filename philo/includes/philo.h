/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:14:43 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/25 14:08:29 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_game
{
	int				num_philo;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num_phi_eat;
	t_fork			**fork_lst;
	struct timeval	start;

	int				philo_died;
	pthread_mutex_t	philodied_mtx;
	pthread_mutex_t	prt_mtx;
	pthread_mutex_t	eat_mtx;
}	t_game;

typedef struct s_id
{
	int				id;
	int				eat_count;
	struct s_id		*next;
	t_game			*game;
	pthread_t		thread;
	struct timeval	lst_eat;

	pthread_mutex_t	eatcount_mtx;
	pthread_mutex_t	lsteat_mtx;

	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;
}	t_id;

//utils
void			mutex_print(t_id *tid, char *msg);
size_t			ft_strlen(const char *str);
void			split_sleep(t_id *tid, int time);
int				all_eat(t_id *tid);
void			philo_died(t_id *tid);

//math
int				ft_atoi(const char *str);
float			time_diff(struct timeval *start, struct timeval *end);
long long		ft_atoi_long(const char *str);
int				all_num(char *str);

//philo
void			philo(char **argv, int num_phi_eat);

//tid
t_id			*lst_tid(t_id *tid);
t_id			*new_tid(int id, t_game *game);
t_id			*get_id_by_id(t_id *tid, int id);
void			add_back_tid(t_id **tid, t_id *new);
int				tid_finish_eat(t_id *tmp);

//free
void			free_all(t_id *tid);

//init
t_id			*init_all(char **argv, int num_phi_eat);

//philoeat
void			philo_incr_eat(t_id *tid);
int				check_lsteat(t_id *tid);

//fork
pthread_mutex_t	*get_first_fork(t_id *tid);
pthread_mutex_t	*get_second_fork(t_id *tid);

#endif
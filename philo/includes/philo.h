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
	int id;
	pthread_mutex_t mutex;
}	t_fork;

typedef struct s_game
{
	int	numPhilo;
	int time2die;
	int time2eat;
	int time2sleep;
	int numPhiEat;
	t_fork	**fork_lst;
	struct timeval	start;
}	t_game;

typedef struct s_id
{
	int		id;
	int		eat_count;
	struct s_id	*next;
	t_game	*game;
}	t_id;

void	philo(int numPhilo, int time2die, int time2eat, int time2sleep, int numPhiEat);
int		ft_atoi(const char *str);
void	add_back_tid(t_id **tid, t_id *new);
t_id	*new_tid(int id, t_game *game);
t_id	*lst_tid(t_id *tid);
t_id	*get_id_by_id(t_id *tid, int id);
t_fork	*get_fork_by_id(t_game *game, int id);


#endif
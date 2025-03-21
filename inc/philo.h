/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:34:47 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/19 15:57:56 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define PHILO_MAX 200
# define TRUE 1
# define FALSE 0

# define RES		"\033[0m"
# define RED		"\033[0;31m"
# define GRE		"\033[0;32m"
# define WHI		"\033[0;37m"

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork_mutex;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			ph_id;
	int			max_meals;
	long		meals_counter;
	long		last_meal;
	pthread_t	philo_thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mtx		philo_mtx;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			total_meals;
	long			start_time;
	long			active_philo;
	int				end_time;
	int				threads_ready;
	int				error_flag;
	pthread_t		thread_death;
	t_fork			*forks_arr;
	t_philo			*philo_arr;
	t_mtx			access_mutex;
	t_mtx			print_mutex;	
}				t_data;

typedef enum e_status
{
	THINKING,
	TAKES_LEFT_FORK,
	TAKES_RIGHT_FORK,
	EATING,
	SLEEPING,
	DIED,
}				t_status;

typedef enum e_flag
{
	INIT,
	CREATE,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH,
	DESTROY,
}				t_flag;

void	handle_thread(pthread_t *thread_info, void *(*f)(void *) \
		, void *t_data, t_flag flag);
void	handle_mutex(t_mtx *mtx, t_flag flag);
void	waiting_thread(t_data *data);
void	thread_active(t_mtx *mutex, long *value);
void	*death_check(void *ph_data);
void	*single_philo(void *ph);
void	data_init(t_data *data);
void	convert_input(t_data *data, char **argv);
void	set_value(t_mtx *mutex, int *value, int flag);
void	set_long(t_mtx *mutex, long *value, long flag);
int		get_bool(t_mtx *mutex, int *flag);
long	get_long(t_mtx *mutex, long *value);
void	simulation_start(t_data *data);
void	print_status(t_status status, t_philo *philo);
long	gettime(void);
void	ft_usleep(long sleep_time, t_data *data);
void	*ft_malloc(size_t size, t_data *data);
void	free_things(t_data *data);
#endif
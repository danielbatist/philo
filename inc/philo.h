/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:34:47 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/24 20:19:20 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../printf/ft_printf.h"
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				preset_meals;
	int				died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fork_mutex;
	int				*forks_free;	
	
}				t_data;


typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	int				meals_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
	struct timeval	last_meal_time;
	struct s_philo	*next;
}				t_philo;

t_philo	*init_philo(int num_philo, pthread_mutex_t *forks, t_data *data);
t_philo	*creat_philo(int id);
int		check_philo_died(t_philo *philo);
long	get_time(void);
void	update_last_meal_time(t_philo *philo);
void	take_forks_even(t_philo *philo);
void	take_forks_odd(t_philo *philo);
void	release_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	print_message(t_philo *philo, char *str);
#endif
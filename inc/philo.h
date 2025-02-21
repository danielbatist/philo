/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:34:47 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/21 18:53:38 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../printf/ft_printf.h"
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data
{
	int	num_philo;
	int	preset_meals;
	int	died;
	pthread_mutex_t	print_mutex;
}				t_data;


typedef struct s_philo
{
	int				id;
	int				meals_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
	struct s_philo	*next;
}				t_philo;

t_philo	*init_philo(int num_philo, pthread_mutex_t *forks, t_data *data);
t_philo	*creat_philo(int id);


#endif
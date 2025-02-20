/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:34:47 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/20 20:35:36 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../printf/ft_printf.h"
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	struct s_philo	*next;
}				t_philo;

t_philo	*init_philo(int num_philo);
t_philo	*creat_philo(int id);


#endif
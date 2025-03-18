/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:22:35 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/17 21:11:37 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value(t_mtx *mutex, int *value, int flag)
{
	handle_mutex(mutex, LOCK);
	*value = flag;
	handle_mutex(mutex, UNLOCK);
}

void	set_long(t_mtx *mutex, long *value, long flag)
{
	handle_mutex(mutex, LOCK);
	*value = flag;
	handle_mutex(mutex, UNLOCK);
}

int	get_bool(t_mtx *mutex, int *flag)
{
	int	tmp;

	handle_mutex(mutex, LOCK);
	tmp = *flag;
	handle_mutex(mutex, UNLOCK);
	return (tmp);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	tmp;

	handle_mutex(mutex, LOCK);
	tmp = *value;
	handle_mutex(mutex, UNLOCK);
	return (tmp);
}

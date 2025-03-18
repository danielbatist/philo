/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:08:40 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/17 23:02:32 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting_thread(t_data *data)
{
	while (1)
	{
		if (get_bool(&data->access_mutex, &data->threads_ready) == TRUE)
			break ;
	}
}

void	thread_active(t_mtx *mutex, long *value)
{
	handle_mutex(mutex, LOCK);
	(*value)++;
	handle_mutex(mutex, UNLOCK);
}

static int	philo_die(t_philo *philo)
{
	long	elapsed_time;

	if (get_bool(&philo->philo_mtx, &philo->max_meals) == TRUE)
		return (FALSE);
	elapsed_time = gettime() - get_long(&philo->philo_mtx, &philo->last_meal);
	if (elapsed_time > philo->data->time_to_die)
		return (TRUE);
	return (FALSE);
}

static int	all_ph_active(t_mtx *mutex, long *philo_active, long ph_total)
{
	int	flag;

	flag = FALSE;
	handle_mutex(mutex, LOCK);
	if (*philo_active == ph_total)
		flag = TRUE;
	handle_mutex(mutex, UNLOCK);
	return (flag);
}

void	*death_check(void *ph_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)ph_data;
	while (1)
	{
		if (all_ph_active(&data->access_mutex, &data->active_philo \
			, data->num_philo))
			break ;
	}
	while (get_bool(&data->access_mutex, &data->end_time) == FALSE)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (philo_die(data->philo_arr + i) == TRUE)
			{
				print_status(DIED, data->philo_arr + i);
				set_value(&data->access_mutex, &data->end_time, TRUE);
			}
			i++;
		}
	}
	return (NULL);
}

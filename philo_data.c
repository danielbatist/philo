/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:31:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/17 21:08:50 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	waiting_thread(philo->data);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime());
	thread_active(&philo->data->access_mutex, &philo->data->active_philo);
	print_status(TAKES_LEFT_FORK, philo);
	while (get_bool(&philo->data->access_mutex \
		, &philo->data->end_time) == FALSE)
		ft_usleep(200, philo->data);
	return (NULL);
}

static void	take_forks(t_philo *philo, t_fork *forks_arr, int philo_index)
{
	int	philo_total;

	philo_total = philo->data->num_philo;
	if (philo->ph_id % 2 == 0)
	{
		philo->left_fork = &forks_arr[philo_index];
		philo->right_fork = &forks_arr[(philo_index + 1) % philo_total];
	}
	else
	{
		philo->right_fork = &forks_arr[(philo_index + 1) % philo_total];
		philo->left_fork = &forks_arr[philo_index];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->num_philo)
	{
		philo = data->philo_arr + i;
		philo->ph_id = i + 1;
		philo->max_meals = 0;
		philo->meals_counter = 0;
		handle_mutex(&philo->philo_mtx, INIT);
		philo->data = data;
		take_forks(philo, data->forks_arr, i);
		i++;
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->end_time = 0;
	data->threads_ready = 0;
	data->active_philo = 0;
	data->philo_arr = ft_malloc(data->num_philo * sizeof(t_philo), data);
	if (!data->philo_arr)
		return ;
	data->forks_arr = ft_malloc(data->num_philo * sizeof(t_fork), data);
	if (!data->forks_arr)
	{
		free(data->philo_arr);
		return ;
	}
	handle_mutex(&data->access_mutex, INIT);
	handle_mutex(&data->print_mutex, INIT);
	while (i < data->num_philo)
	{
		handle_mutex(&data->forks_arr[i].fork_mutex, INIT);
		data->forks_arr[i].fork_id = i;
		i++;
	}
	philo_init(data);
}

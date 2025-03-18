/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:15:38 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/18 09:53:13 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo, int pre_sim)
{
	long	eating_time;
	long	sleeping_time;
	long	thinking_time;

	if (pre_sim == FALSE)
		print_status(THINKING, philo);
	if (philo->data->num_philo % 2 == 0)
		return ;
	eating_time = philo->data->time_to_eat;
	sleeping_time = philo->data->time_to_sleep;
	thinking_time = (eating_time * 2) - sleeping_time;
	if (thinking_time < 0)
		thinking_time = 0;
	ft_usleep(thinking_time * 0.3, philo->data);
}

static void	synch_dinner(t_philo *philo)
{
	if (philo->ph_id % 2 == 0)
		ft_usleep(30, philo->data);
	else
		thinking(philo, TRUE);
}

static void	eating(t_philo *philo)
{
	handle_mutex(&philo->left_fork->fork_mutex, LOCK);
	print_status(TAKES_LEFT_FORK, philo);
	handle_mutex(&philo->right_fork->fork_mutex, LOCK);
	print_status(TAKES_RIGHT_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime());
	philo->meals_counter++;
	print_status(EATING, philo);
	ft_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->total_meals > 0 && \
		philo->meals_counter == philo->data->total_meals)
		set_value(&philo->philo_mtx, &philo->max_meals, TRUE);
	handle_mutex(&philo->left_fork->fork_mutex, UNLOCK);
	handle_mutex(&philo->right_fork->fork_mutex, UNLOCK);
}

static void	*philo_dinner(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	waiting_thread(philo->data);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime());
	thread_active(&philo->data->access_mutex, &philo->data->active_philo);
	synch_dinner(philo);
	while (!get_bool(&philo->data->access_mutex, &philo->data->end_time))
	{
		if (get_bool(&philo->philo_mtx, &philo->max_meals) == TRUE)
			break ;
		eating(philo);
		print_status(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, FALSE);
	}
	return (NULL);
}

void	simulation_start(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_philo == 1)
		handle_thread(&data->philo_arr[0].philo_thread \
		, single_philo, &data->philo_arr[0], CREATE);
	else
	{
		while (i < data->num_philo)
		{
			handle_thread(&data->philo_arr[i].philo_thread \
			, philo_dinner, &data->philo_arr[i], CREATE);
			i++;
		}
	}
	handle_thread(&data->thread_death, death_check, data, CREATE);
	data->start_time = gettime();
	set_value(&data->access_mutex, &data->threads_ready, TRUE);
	i = 0;
	while (i < data->num_philo)
		handle_thread(&data->philo_arr[i++].philo_thread, NULL, NULL, JOIN);
	set_value(&data->access_mutex, &data->end_time, TRUE);
	handle_thread(&data->thread_death, NULL, NULL, JOIN);
}

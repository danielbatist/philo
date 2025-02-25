/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:17:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/24 21:45:43 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex);

	while ((philo->data->forks_free[philo->id - 1] == 1 ) || (philo->data->forks_free[philo->id % philo->data->num_philo] == 1))
	{
		pthread_mutex_unlock(&philo->data->fork_mutex);
		usleep(1000);
		pthread_mutex_lock(&philo->data->fork_mutex);
	}
	philo->data->forks_free[philo->id - 1] = 1;
	philo->data->forks_free[philo->id % philo->data->num_philo] = 1;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_unlock(&philo->data->fork_mutex);
	print_message(philo, "has taken left fork");
	print_message(philo, "has taken right fork");
	usleep(1000);
}

void	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex);
	while ((philo->data->forks_free[philo->id % philo->data->num_philo] == 1) || (philo->data->forks_free[philo->id - 1] == 1 ))
	{
		pthread_mutex_unlock(&philo->data->fork_mutex);
		usleep(1000);
		pthread_mutex_lock(&philo->data->fork_mutex);
	}
	philo->data->forks_free[philo->id - 1] = 1;
	philo->data->forks_free[philo->id % philo->data->num_philo] = 1;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_unlock(&philo->data->fork_mutex);
	print_message(philo, "has taken right fork");
	print_message(philo, "has taken left fork");
	usleep(1000);
}

void	eating(t_philo *philo)
{
	if (gettimeofday(&philo->last_meal_time, NULL) == -1)
	{
		ft_printf("Error getting time\n");
		return ;
	}
	update_last_meal_time(philo);
	usleep(philo->data->time_to_eat * 1000);
	print_message(philo, "is eating");
	philo->meals_eat++;
	

}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->fork_mutex);
	philo->data->forks_free[philo->id - 1] = 0;
	philo->data->forks_free[philo->id % philo->data->num_philo] = 0;
	pthread_mutex_unlock(&philo->data->fork_mutex);
	print_message(philo, "has released forks");
	usleep(1000);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

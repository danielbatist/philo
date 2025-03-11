/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:15 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/10 20:06:47 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_status status, t_philo *philo)
{
	long	elapsed_time;
	int		end_time;

	elapsed_time = gettime() - philo->data->start_time;
	if (get_bool(&philo->philo_mtx, &philo->max_meals))
		return ;
	else
	{
		handle_mutex(&philo->data->print_mutex, LOCK);
		end_time = get_bool(&philo->data->access_mutex, &philo->data->end_time);
		if (status == TAKES_LEFT_FORK && !end_time)
			printf(WHITE"%-6ld"RESET" %d has taken a left fork\n", elapsed_time, philo->philo_id);
		else if (status == TAKES_RIGHT_FORK && !end_time)
			printf(WHITE"%-6ld"RESET" %d has taken a right fork\n", elapsed_time, philo->philo_id);
		else if (status == EATING && !end_time)
			printf(GREEN"%-6ld"RESET" %d is eating\n", elapsed_time, philo->philo_id);
		else if (status == SLEEPING && !end_time)
			printf(WHITE"%-6ld"RESET" %d is sleeping\n", elapsed_time, philo->philo_id);
		else if (status == THINKING && !end_time)
			printf(WHITE"%-6ld"RESET" %d is thinking\n", elapsed_time, philo->philo_id);
		else if (status == DIED && !end_time)
			printf(RED"%-6ld"RESET" %d is died\n", elapsed_time, philo->philo_id);
	}
	handle_mutex(&philo->data->print_mutex, UNLOCK);
}

long	gettime(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
	{
		ft_printf("Error: gettimeofday failure.\n");
		return (1);
	}
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	ft_usleep(long sleep_time, t_data *data)
{
	long	start_time;
	long	elapsed_time;
	long	rest_time;

	start_time = gettime();
	while (gettime() - start_time < sleep_time)
	{
		if (get_bool(&data->access_mutex, &data->end_time))
			break ;
		elapsed_time = gettime() - start_time;
		rest_time = sleep_time - elapsed_time;
		if (rest_time > 10)
			usleep((rest_time * 1000) / 2);
		else
			while (gettime() - start_time < sleep_time)
				;
	}
}

void	free_things(t_data *data)
{
	t_philo *philo;
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo = data->philo_arr + i;
		handle_mutex(&philo->philo_mtx, DESTROY);
		i++;
	}
	handle_mutex(&data->print_mutex, DESTROY);
	handle_mutex(&data->access_mutex, DESTROY);
	free(data->forks_arr);
	free(data->philo_arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:03 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/20 20:49:34 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	ft_printf("Philosopher %d is thinking\n", philo->id);
	usleep(1000);
	ft_printf("Philosopher %d is eating\n", philo->id);
	usleep(1000);
	ft_printf("Philosopher %d is sleeping\n", philo->id);
	usleep(1000);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		num_philo;
	t_philo	*philo;
	t_philo	*current;
	t_philo	*tmp;

	if (argc != 2)
	{
		ft_printf("Invalid input\n");
		return (1);
	}
	num_philo = ft_atoi(argv[1]);
	if (!(philo = init_philo(num_philo)))
		return (1);
	current = NULL;
	while (current != philo)
	{
		if (current == NULL)
			current = philo;
		if (pthread_create(&current->thread, NULL, &routine, current) != 0)
		{
			perror("Thread failure!!!");
			return (1);
		}
		ft_printf("Thread for philosopher %d createad\n", current->id);
		current = current->next;
	}
	current = NULL;
	while (current != philo)
	{
		if (current == NULL)
			current = philo;
		if (pthread_join(current->thread, NULL) != 0)
			return (1);
		ft_printf("Thread for philosopher %d finished\n", current->id);
		current = current->next;
	}
	current = NULL;
	while (current != philo)
	{
		if (current == NULL)
			current = philo;
		tmp = current;
		current = current->next;
		free(tmp);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:03 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/24 21:25:17 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->died == 1 || check_philo_died(philo) == 1 || philo->meals_eat == philo->data->preset_meals) 
			break ;
		//pensar
		print_message(philo, "is thinking");
		//pegar garfo
		if (philo->id % 2 == 0)
			take_forks_even(philo);
		else
			take_forks_odd(philo);
		//comendo
		eating(philo);
		//libera os garfos
		release_forks(philo);
		//dormindo
		sleeping(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	int				num_philo;
	t_philo			*philo;
	t_philo			*current;
	t_philo			*tmp;
	pthread_mutex_t	*forks;
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		ft_printf("Invalid input\n");
		ft_printf("Usage: <num_philo> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	num_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.preset_meals = -1;
	if (argc == 6)
		data.preset_meals = ft_atoi(argv[5]);
	data.num_philo = num_philo;
	data.died = 0;
	if (num_philo <= 0 || data.time_to_die <= 0 || data.time_to_eat <= 0 || data.time_to_sleep <= 0)
	{
		ft_printf("Invalid input\n");
		ft_printf("Try again with a valid number \n");
		return (1);
	}
	pthread_mutex_init(&data.print_mutex, NULL);
	pthread_mutex_init(&data.fork_mutex, NULL);
	if (!(data.forks_free = malloc(num_philo * sizeof(int))))
		return (1);
	i = 0;
	while (i < num_philo)
	{
		data.forks_free[i] = 0;
		i++;
	}
	if (!(forks = malloc(num_philo * sizeof(pthread_mutex_t))))
		return (1);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_printf("mutex initialization failed\n");
			return (1);
		}
		i++;
	}
	if (!(philo = init_philo(num_philo, forks, &data)))
		return (1);
	current = NULL;
	while (current != philo)
	{
		if (current == NULL)
			current = philo;
		if (gettimeofday(&current->last_meal_time, NULL) == -1)
		{
			ft_printf("Error getting time\n");
			return (1);
		}
		if (pthread_create(&current->thread, NULL, &routine, current) != 0)
		{
			perror("Thread failure!!!");
			return (1);
		}
		current = current->next;
	}
	current = NULL;
	while (current != philo)
	{
		if (current == NULL)
			current = philo;
		if (pthread_join(current->thread, NULL) != 0)
			return (1);
		current = current->next;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.fork_mutex);
	free(forks);
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
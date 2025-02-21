/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:03 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/21 19:32:00 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{	//verifica se alguem morreu ou comeu o suficiente.
		if (philo->data->died || ( philo->meals_eat > 2))
			break;

		//pensar
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf("Philosopher %d is thinking\n", philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		sleep(2);
		//pegar garfo
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->data->print_mutex);
			ft_printf("Philosopher %d has taken left fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			sleep(2);
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->data->print_mutex);
			ft_printf("Philosopher %d has taken right fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			sleep(2);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->data->print_mutex);
			ft_printf("Philosopher %d has taken right fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			sleep(2);
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->data->print_mutex);
			ft_printf("Philosopher %d has taken left fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			sleep(2);
		}
		//comendo
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf("Philosopher %d is eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		sleep(2);
		philo->meals_eat++;
		//libera os garfos
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf("Philosopher %d has released forks\n", philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		sleep(2);
		//dormindo
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf("Philosopher %d is sleeping\n", philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		sleep(2);
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

	if (argc != 2)
	{
		ft_printf("Invalid input\n");
		return (1);
	}
	num_philo = ft_atoi(argv[1]);
	data.num_philo = num_philo;
	data.preset_meals = 2;
	data.died = 0;
	pthread_mutex_init(&data.print_mutex, NULL);
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
		if (pthread_create(&current->thread, NULL, &routine, current) != 0)
		{
			perror("Thread failure!!!");
			return (1);
		}
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf("Thread for philosopher %d createad\n", current->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		sleep(2);
		current = current->next;
	}
	current = NULL;
	while (current != philo)
	{
		if (current == NULL)
			current = philo;
		if (pthread_join(current->thread, NULL) != 0)
			return (1);
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf("Thread for philosopher %d finished\n", current->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		sleep(2);
		current = current->next;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
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
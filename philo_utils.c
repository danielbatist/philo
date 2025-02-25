/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:15 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/24 21:38:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	if (philo->data->died == 1)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	ft_printf("Philosopher %d %s\n", philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

t_philo	*creat_philo(int id)
{
	t_philo	*philo;

	if (!(philo = malloc(sizeof(t_philo))))
		return (NULL);
	philo->id = id;
	philo->next = NULL;
	return (philo);
}

t_philo	*init_philo(int num_philo, pthread_mutex_t *forks, t_data *data)
{
	int	i;
	t_philo	*head;
	t_philo	*current;
	t_philo	*tmp;
	t_philo	*philo;

	i = 0;
	head = NULL;
	current = NULL;
	while (i < num_philo)
	{
		philo = creat_philo(i + 1);
		if (!philo)
		{
			while (head)
			{
				tmp = head;
				head = head->next;
				free(tmp);
			}
			return (NULL);
		}

		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % num_philo];
		philo->meals_eat = 0;
		philo->data = data;
		if (!head)
			head = philo;
		else
			current->next = philo;
		i++;
		current = philo;
	}
	current->next = head;
	return (head);
}
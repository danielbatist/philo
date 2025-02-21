/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:15 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/21 19:55:30 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
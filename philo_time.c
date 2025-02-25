/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:44:38 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/24 20:23:29 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//verificar se o filosofo morreu
int    check_philo_died(t_philo *philo)
{
    struct timeval current_time;
    long   time_since_last_meal;

    if (philo->data->died == 1)
        return (1);
    if (gettimeofday(&current_time, NULL) == -1)
    {
        ft_printf("Error getting time\n");
        return (-1);
    }
    time_since_last_meal = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) 
		- (philo->last_meal_time.tv_sec * 1000 + philo->last_meal_time.tv_usec / 1000);
	if (time_since_last_meal > philo->data->time_to_die)
	{
		print_message(philo, "died");
		philo->data->died = 1;
		return (1);
	}
	return (0);
}

// função para obter o tempo atual em milissegundos
long   get_time(void)
{
    struct timeval current_time;

    if (gettimeofday(&current_time, NULL) == -1)
    {
        ft_printf("Error getting time\n");
        return (-1);
    }
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

// atualiza o tempo da ultima refeição
void   update_last_meal_time(t_philo *philo)
{
    struct timeval current_time;

    if (gettimeofday(&current_time, NULL) == -1)
    {
        ft_printf("Error getting time\n");
        return ;
    }
    philo->last_meal_time = current_time;
}

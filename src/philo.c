/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:03 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/19 17:17:09 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		data.error_flag = 0;
		convert_input(&data, argv);
		if (!data.error_flag)
		{
			data_init(&data);
			simulation_start(&data);
			free_things(&data);
		}
		else
			return (1);
	}
	else
	{
		printf("Invalid input\n \
				  Usage: <num_philo> <time_to_die> <time_to_eat> <time_to_sleep>[number_of_times_each_philosopher_must_eat]\n \
				  For example: ./philo 5 800 200 200 7\n");
		return (1);
	}
	return (0);
}

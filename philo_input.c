/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:54 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/11 19:41:38 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static long	ft_atol(const char *num)
{
	long	res;

	res = 0;
	while ((*num == '+' || *num == 32 || (*num >= 9 && *num <= 13)))
		num++;
	if (*num == '-')
		return (0);
	if (*num < '0' || *num > '9')
	{
		ft_printf("Input error: Digit value only\n");
		return (0);
	}
	while (*num >= '0' && *num <= '9')
	{
		res = res * 10 + *num - '0';
		num++;
	}
	return (res);
}

static long	check_num_valid(t_data *data, char *argv)
{
	long	num;

	num = ft_atol(argv);
	if (num > INT_MAX)
	{
		ft_printf("Input error: the value exceed 2147483647\n");
		data->error_flag = 1;
	}
	if (num < 1)
	{
		ft_printf("Input error: Positive number only\n");
		data->error_flag = 1;
	}
	return (num);
}

void	convert_input(t_data *data, char **argv)
{
	data->num_philo = check_num_valid(data, argv[1]);
	if (data->num_philo > INT_MAX || data->num_philo < 1)
	{
		ft_printf("Input error: total number of philos must be 1 - 200\n");
		data->error_flag = 1;
	}
	data->time_to_die = check_num_valid(data, argv[2]);
	data->time_to_eat = check_num_valid(data, argv[3]);
	data->time_to_sleep = check_num_valid(data, argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
	{
		ft_printf("Input error: time must be at least 60ms\n");
		data->error_flag = 1;
	}
	if (argv[5])
		data->total_meals = check_num_valid(data, argv[5]);
	else
		data->total_meals = -1;
}
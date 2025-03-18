/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:54 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/17 21:53:10 by dbatista         ###   ########.fr       */
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
		return (1);
	while (*num >= '0' && *num <= '9')
	{
		res = res * 10 + *num - '0';
		num++;
	}
	return (res);
}

static long	check_is_num(t_data *data, char *args)
{
	int		i;
	long	num;

	i = 0;
	while (args[i])
	{
		if (args[i] < '0' || args[i] > '9')
		{
			data->error_flag = 1;
			return (-1);
		}
		i++;
	}
	num = ft_atol(args);
	if (num > INT_MAX)
	{
		data->error_flag = 1;
		return (-1);
	}
	return (num);
}

void	convert_input(t_data *data, char **argv)
{
	data->num_philo = check_is_num(data, argv[1]);
	data->time_to_die = check_is_num(data, argv[2]);
	data->time_to_eat = check_is_num(data, argv[3]);
	data->time_to_sleep = check_is_num(data, argv[4]);
	if (argv[5])
		data->total_meals = check_is_num(data, argv[5]);
	else
		data->total_meals = -1;
	if (!data->error_flag)
	{
		if (data->num_philo > 200)
			data->error_flag = 1;
		if (data->time_to_die < 60 || data->time_to_eat < 60 \
			|| data->time_to_sleep < 60)
			data->error_flag = 1;
	}
	if (data->error_flag)
	{
		printf("Input error: invalid arguments, try again.\n");
		printf ("Ex: <./philo 5 800 200 200> or <./philo 5 800 200 200 7>\n ");
	}
}

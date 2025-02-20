/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:56 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/20 18:33:15 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int	i;

	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	int	i;
	int	arg = ft_atoi(argv[1]);
	pthread_t	th[arg];

	if (argc > 1)
	{
		i = 0;
		pthread_mutex_init(&mutex, NULL);
		while (i < arg)
		{
			if (pthread_create(th + i, NULL, &routine, NULL) != 0)
			{
				perror("thread error!");
				return (1);
			}
			ft_printf("Thread %d has started\n", i);
			sleep(1);
			i++;
		}
		i = 0;
		while (i < arg)
		{
			if (pthread_join(th[i] , NULL) != 0)
				return (1);
			ft_printf("Thread %d finish\n", i);
			sleep(1);
			i++;
		}
		pthread_mutex_destroy(&mutex);
		ft_printf("Number of mails: %d\n", mails);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:56 by dbatista          #+#    #+#             */
/*   Updated: 2025/02/18 21:04:41 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
    ft_printf("Minha primeira thread está sendo criada.\n");
	sleep(3);
	ft_printf("Deu tudo certo.");
	return (NULL);
}

int		main(void)
{
    pthread_t	t1;
	pthread_t	t2;
    pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
    return (0);
}
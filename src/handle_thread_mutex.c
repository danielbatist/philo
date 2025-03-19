/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread_mutex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:46:11 by dbatista          #+#    #+#             */
/*   Updated: 2025/03/19 15:58:53 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	thread_error(int status, t_flag flag)
{
	if (status != 0 && (flag == CREATE || flag == JOIN))
	{
		printf("Thread error\n");
		return ;
	}
}

static void	mutex_error(int status, t_flag flag)
{
	if (status != 0 && (flag == INIT || flag == LOCK || \
		flag == UNLOCK || flag == DESTROY))
	{
		printf("Mutex error\n");
		return ;
	}
}

void	handle_thread(pthread_t *thread_info, void *(*f)(void *) \
		, void *t_data, t_flag flag)
{
	if (flag == CREATE)
		thread_error(pthread_create(thread_info, NULL, f, t_data), flag);
	else if (flag == JOIN)
		thread_error(pthread_join(*thread_info, NULL), flag);
	else
	{
		printf("Flag options: CREATE and JOIN");
		return ;
	}
}

void	handle_mutex(t_mtx *mtx, t_flag flag)
{
	if (flag == INIT)
		mutex_error(pthread_mutex_init(mtx, NULL), flag);
	else if (flag == LOCK)
		mutex_error(pthread_mutex_lock(mtx), flag);
	else if (flag == UNLOCK)
		mutex_error(pthread_mutex_unlock(mtx), flag);
	else if (flag == DESTROY)
		mutex_error(pthread_mutex_destroy(mtx), flag);
	else
	{
		printf("Flags option: LOCK, UNLOCK, INIT, DESTROY");
		return ;
	}
}

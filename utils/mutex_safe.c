/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:32:11 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:07:57 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Mutex handler for LOCK/UNLOCK/INIT/DESTROY operations. */
void	safe_mutex_handler(t_mutex *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handler_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handler_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handler_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handler_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid opcode for mutex handler.");
}

/* Handle mutex-related errors for operations. */
void	handler_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("Invalid mutex for lock/unlock.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("Invalid attributes for mutex init.");
	else if (EDEADLK == status && opcode == LOCK)
		error_exit("Deadlock detected while locking mutex.");
	else if (status == EDEADLK)
		error_exit("Deadlock detected while unlocking mutex.");
	else if (status == EBUSY)
		error_exit("Mutex locked; cannot destroy.");
	else if (status == ENOMEM)
		error_exit("Insufficient memory for mutex.");
}

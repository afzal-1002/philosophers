/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:31:08 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:07:44 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Thread wrappers and error handling for create/join/detach. */
void	handler_thread_error(int status, t_opcode opcode);

void	safe_thread_handler(pthread_t *thread, void *(*start_routine)(void *),
			void *data, t_opcode opcode);

void	safe_thread_handler(pthread_t *thread, void *(*start_routine)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handler_thread_error(pthread_create(thread, NULL, start_routine, data),
			opcode);
	else if (JOIN == opcode)
		handler_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handler_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Invalid opcode for thread handler.");
}

void	handler_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources available to create another thread.");
	else if (status == EPERM)
		error_exit("Insufficient permission to set thread scheduling.");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("Invalid attributes specified for thread creation.");
	else if (status == ESRCH)
		error_exit("No thread found corresponding to the given id.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("Invalid thread specified for join/detach operation.");
	else if (status == EDEADLK)
		error_exit("Deadlock detected or thread attempted to join itself.");
	else if (status == EINVAL)
		error_exit("Thread is not a joinable thread.");
}

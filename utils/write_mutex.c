/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal <mafzal@student.42warsaw.pl>         +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:30:07 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:50:00 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status_message(t_philo_status status, t_philo *philo,
		long elasped_time)
{
	if (TAKEN_LEFT_FORK == status && !simulation_end(philo->table))
		printf("%-6ld %d has taken a fork\n", elasped_time, philo->ph_id);
	else if (TAKEN_RIGHT_FORK == status && !simulation_end(philo->table))
		printf("%-6ld %d has taken a fork\n", elasped_time, philo->ph_id);
	else if (EATING == status && !simulation_end(philo->table))
		printf("%-6ld %d is eating\n", elasped_time, philo->ph_id);
	else if (SLEEPING == status && !simulation_end(philo->table))
		printf("%-6ld %d is sleeping\n", elasped_time, philo->ph_id);
	else if (THINKING == status && !simulation_end(philo->table))
		printf("%-6ld %d is thinking\n", elasped_time, philo->ph_id);
	else if (DEAD == status)
		printf("%-6ld %d has died\n", elasped_time, philo->ph_id);
}

void	write_mutex(t_philo_status status, t_philo *philo)
{
	long	elasped_time;

	if (philo == NULL)
	{
		error_exit("Philo pointer is NULL in write_mutex function.");
		return ;
	}
	elasped_time = get_time_in_ms(MILLISECOND)
		- philo->table->simulation_start_time;
	safe_mutex_handler(&philo->table->write_mutex, LOCK);
	print_status_message(status, philo, elasped_time);
	safe_mutex_handler(&philo->table->write_mutex, UNLOCK);
}

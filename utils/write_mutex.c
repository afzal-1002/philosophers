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

static void	debug_print(t_philo_status status, t_philo *philo, long t)
{
	if (status == TAKEN_FIRST_FORK && !simulation_end(philo->table))
		printf("%-6ld %d has taken the 1st fork\n%d [ ] %d\n", t, philo->ph_id,
			philo->ph_id, philo->first_fork->fork_id);
	else if (status == TAKEN_SECOND_FORK && !simulation_end(philo->table))
		printf("%-6ld %d has taken the 2nd fork\n%d [ ] %d\n", t, philo->ph_id,
			philo->ph_id, philo->second_fork->fork_id);
	else if (status == EATING && !simulation_end(philo->table))
		printf("%-6ld %d is eating\n%d [ %ld ]\n", t, philo->ph_id,
			philo->ph_id, philo->meals_counter);
	else if (status == SLEEPING && !simulation_end(philo->table))
		printf("%-6ld %d is sleeping\n", t, philo->ph_id);
	else if (status == THINKING && !simulation_end(philo->table))
		printf("%-6ld %d is thinking\n", t, philo->ph_id);
	else if (status == DEAD && !simulation_end(philo->table))
		printf("%-6ld %d has died\n", t, philo->ph_id);
}

static void	print_status_message(t_philo_status status, t_philo *philo,
		long elasped_time)
{
	if ((TAKEN_FIRST_FORK == status || TAKEN_SECOND_FORK == status)
		&& !simulation_end(philo->table))
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

void	write_status_debug(t_philo_status status, t_philo *philo,
		long elasped_time)
{
	debug_print(status, philo, elasped_time);
}

void	write_mutex(t_philo_status status, t_philo *philo, bool debug)
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
	if (debug)
	{
		write_status_debug(status, philo, elasped_time);
		safe_mutex_handler(&philo->table->write_mutex, UNLOCK);
		return ;
	}
	print_status_message(status, philo, elasped_time);
	safe_mutex_handler(&philo->table->write_mutex, UNLOCK);
}

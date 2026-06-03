/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:30:53 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/03 18:04:16 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *message);
long	get_time_in_ms(t_time_code time_code);
void	precision_usleep(long duration_in_ms, t_table *table);
long	get_long_value(t_mutex *mutex, long *var);

void	error_exit(const char *message)
{
	printf("%s \n", message);
	exit(EXIT_FAILURE);
}

/* Return current time in seconds, milliseconds, or microseconds. */
long	get_time_in_ms(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		error_exit("Failed to get current time.");
	}
	if (time_code == SECOND)
		return (tv.tv_sec + tv.tv_usec / 1000000);
	else if (time_code == MILLISECOND)
		return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else
		error_exit("Invalid time code provided to get_time_in_ms function.");
	return (1337);
}

/*
 * Sleep with periodic checks so simulation can stop promptly.
 * The function wakes up in small increments to allow the simulation to
 * end early when required.
 */
void	precision_usleep(long duration_in_ms, t_table *table)
{
	long	start_time;

	start_time = get_time_in_ms(MILLISECOND);
	while (get_time_in_ms(MILLISECOND) - start_time < duration_in_ms)
	{
		if (simulation_end(table))
			break ;
		usleep(500);
	}
}

long	get_long_value(t_mutex *mutex, long *var)
{
	long	value;

	safe_mutex_handler(mutex, LOCK);
	value = *var;
	safe_mutex_handler(mutex, UNLOCK);
	return (value);
}

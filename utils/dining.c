/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:33:19 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:47:08 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Core dining simulation flow:
 * - Create philosopher threads.
 * - Create monitor thread.
 */

/* Philosopher routine and simulation coordinator. */
void		*dinner_simulation(void *data);
void		dinner_start(t_table *table);

static void	create_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		safe_thread_handler(&table->philos[i].thread_id, dinner_simulation,
			&table->philos[i], CREATE);
		i++;
	}
}

static void	start_monitor_and_join(t_table *table)
{
	int	i;

	safe_thread_handler(&table->monitor, monitor_dinner, table, CREATE);
	table->simulation_start_time = get_time_in_ms(MILLISECOND);
	set_bool_value(&table->table_mutex, &table->all_thread_ready, true);
	i = 0;
	while (i < table->num_philos)
	{
		safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool_value(&table->table_mutex, &table->simulation_should_end, true);
	safe_thread_handler(&table->monitor, NULL, NULL, JOIN);
}

void	dinner_start(t_table *table)
{
	if (table->num_philos == 0)
	{
		error_exit("At least one philosopher required.");
		return ;
	}
	else if (table->num_philos == 1)
	{
		table->simulation_start_time = get_time_in_ms(MILLISECOND);
		set_long_value(&table->table_mutex, &table->philos[0].last_meal_time,
			table->simulation_start_time);
		write_mutex(TAKEN_FIRST_FORK, &table->philos[0]);
		usleep(table->time_to_die * 1000);
		write_mutex(DEAD, &table->philos[0]);
		return ;
	}
	else
	{
		create_philosophers(table);
	}
	start_monitor_and_join(table);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_thread_ready(philo->table);
	set_long_value(&philo->table->table_mutex, &philo->last_meal_time,
		get_time_in_ms(MILLISECOND));
	increment_long(&philo->table->table_mutex,
		&philo->table->thread_running_count);
	while (!simulation_end(philo->table))
	{
		if (get_bool_value(&philo->philo_mutex, &philo->full))
			break ;
		eating(philo);
		write_mutex(SLEEPING, philo);
		precision_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

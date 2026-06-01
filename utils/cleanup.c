/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:27:03 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:18:31 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Free allocated resources and destroy all mutexes. */
void	cleanup(t_table *table)
{
	int	i;

	if (table == NULL)
		return ;
	destroy_forks(table);
	destroy_philos(table);
	safe_mutex_handler(&table->table_mutex, DESTROY);
	safe_mutex_handler(&table->write_mutex, DESTROY);
}

static void	destroy_forks(t_table *table)
{
	int	i;

	if (table->forks == NULL)
		return ;
	i = 0;
	while (i < table->num_philos)
	{
		safe_mutex_handler(&table->forks[i].fork, DESTROY);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
}

static void	destroy_philos(t_table *table)
{
	int	i;

	if (table->philos == NULL)
		return ;
	i = 0;
	while (i < table->num_philos)
	{
		safe_mutex_handler(&table->philos[i].philo_mutex, DESTROY);
		i++;
	}
	free(table->philos);
	table->philos = NULL;
}

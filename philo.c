/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:28:28 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:17:47 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Entry point: parse input, initialize data, run simulation, cleanup. */
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(argv, &table);
		data_init(&table);
		dinner_start(&table);
		cleanup(&table);
	}
	else
	{
		error_exit("Invalid number of arguments.");
		return (1);
	}
	return (0);
}

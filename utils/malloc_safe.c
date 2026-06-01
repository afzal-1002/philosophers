/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:32:27 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 16:32:27 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Allocate memory or exit on failure/invalid size. */
void	*safe_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		error_exit("Invalid allocation size.");
	ptr = malloc(size);
	if (ptr == NULL)
		error_exit("Memory allocation failed.");
	return (ptr);
}

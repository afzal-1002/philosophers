/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:33:57 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 19:33:58 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Return 1 when c is ASCII whitespace; otherwise return 0. */
int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

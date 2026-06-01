/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:27:39 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:05:49 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	fork_and_report(const char *label, int wait_seconds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork Failed\n");
		return (1);
	}
	if (pid == 0)
		printf("Child%s: %d\n", label, getpid());
	else
	{
		sleep(wait_seconds);
		printf("Parent%s: %d\n", label, getpid());
	}
	return (0);
}

int	main(void)
{
	if (fork_and_report("", 5) != 0)
		return (1);
	if (fork_and_report(" 2", 5) != 0)
		return (1);
	return (0);
}

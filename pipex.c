/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:08:09 by habouda           #+#    #+#             */
/*   Updated: 2024/09/16 16:40:09 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	child_process(int fd[2], char *argv[])
{
	int	file;
	
	file = open(argv[1], O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
}
int	main(int argc, char *argv[])
{
	int	fd[2];
	pid_t pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
			exit(-1);
		waitpid(0, NULL, 0);
	}
}

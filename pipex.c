/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:08:09 by habouda           #+#    #+#             */
/*   Updated: 2024/09/17 17:05:45 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	execute(char *envp[], char *argv)
{
	char	**cmd;
	char	*path;

	path = ft_strjoin("/usr/bin/", argv);
	cmd = ft_split(argv, ' ');
	execve(path, cmd, envp);
}
void	child_process(int fd[2], char *argv[], char **envp)
{
	int	file;
	
	file = open(argv[1], O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	execute(envp, argv[2]);
}

void	parent_process(int fd[2], char *argv[], char **envp)
{
	int	file;

	file = open(argv[4], O_RDONLY);
	dup2(file , STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execute(envp, argv[3]);
}
int	main(int argc, char *argv[], char *envp[])
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
		if (pid == 0)
			child_process(fd, argv, envp);
		waitpid(0, NULL, 0);
		parent_process(fd, argv, envp);
	}
}

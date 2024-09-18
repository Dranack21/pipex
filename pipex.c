/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:08:09 by habouda           #+#    #+#             */
/*   Updated: 2024/09/18 17:30:05 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	execute(char *envp[], char *argv)
{
	char	**cmd;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	cmd = ft_split(argv, ' ');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd[0]);
		if (access(full_path, X_OK) == 0)
			return (execve(full_path, cmd, envp), 1);
		i++;
		free(full_path);
	}
	return (write(2, "command not found", 18), -1);
}

void	child_process(int fd[2], char *argv[], char **envp)
{
	int	file;

	file = open(argv[1], O_RDONLY);
	if (file < 0)
	{
		perror("cannot open file");
		exit(-1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	if (execute(envp, argv[2]) < 0)
		exit(-1);
}

void	parent_process(int fd[2], char *argv[], char **envp)
{
	int	file;

	file = open(argv[4], O_WRONLY);
	if (file < 0)
	{
		perror("cannot open file");
		exit(-1);
	}
	dup2(file, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	if (execute(envp, argv[3]) < 0)
		exit(-1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

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

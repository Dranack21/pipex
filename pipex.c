/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:08:09 by habouda           #+#    #+#             */
/*   Updated: 2024/09/27 01:29:20 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path(char *envp[])
{
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	return (i);
}

int	execute(char *envp[], char *argv)
{
	char	**cmd;
	char	**paths;
	char	*temp;
	char	*full_path;
	int		i;

	paths = ft_split(envp[get_path(envp)] + 5, ':');
	cmd = ft_split(argv, ' ');
	i = 0;
	while (paths[i++])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, cmd, envp);
			ft_free_array(paths);
			return (ft_free_array(cmd), 1);
		}
		free(full_path);
	}
	ft_free_array(cmd);
	ft_free_array(paths);
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
	close(fd[1]);
	close(file);
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
	close(fd[0]);
	close(file);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:41:36 by habouda           #+#    #+#             */
/*   Updated: 2024/10/10 15:12:08 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_cmd_path(char **paths, char *cmd)
{
	char	*temp;
	char	*full_p;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_p = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_p, X_OK) == 0)
			return (full_p);
		free(full_p);
		i++;
	}
	return (NULL);
}

int	execute(char *envp[], char *argv)
{
	char	**cmd;
	char	**paths;
	char	*full_p;

	cmd = ft_split(argv, ' ');
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	paths = ft_split(envp[get_path(envp)] + 5, ':');
	full_p = find_cmd_path(paths, cmd[0]);
	if (full_p)
	{
		execve(full_p, cmd, envp);
		free(full_p);
		return (ft_free_array(paths), ft_free_array(cmd), -1);
	}
	ft_free_array(cmd);
	ft_free_array(paths);
	return (write(2, "command not found\n", 18), -1);
}

void	child_process(int fd[2], char *argv[], char **envp)
{
	int	file;

	file = open(argv[1], O_RDONLY);
	if (file < 0)
	{
		perror("cannot open file");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file);
	if (execute(envp, argv[2]) < 0)
		exit(0);
}

void	parent_process(int fd[2], char *argv[], char **envp)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
	{
		perror("cannot open file");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(file);
	if (execute(envp, argv[3]) < 0)
		exit(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(1);
		create_pipe_and_fork(fd, argv, envp);
		exit(0);
	}
	return (write(2, "Use 5 arguments", 16), -1);
}

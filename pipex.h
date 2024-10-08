/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:08:12 by habouda           #+#    #+#             */
/*   Updated: 2024/10/09 20:45:06 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

void	child_process(int fd[2], char *argv[], char **envp);
void	parent_process(int fd[2], char *argv[], char **envp);
char	*find_cmd_path(char **paths, char *cmd);
void	create_pipe_and_fork(int fd[2], char *argv[], char **envp);
int		execute(char *envp[], char *argv);
int		get_path(char *envp[]);

#endif
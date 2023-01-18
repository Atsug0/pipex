/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsug0 <atsug0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:18:45 by atsug0            #+#    #+#             */
/*   Updated: 2023/01/18 02:22:48 by atsug0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void close_pipe(t_pipex pipex) 
{
    close(pipex.pipe[0]);
    close(pipex.pipe[1]);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void redirection_in(t_pipex pipex, char **envp) 
{
    close(pipex.pipe[0]);
    if (dup2(pipex.pipe[1], 1) < 0)
        msg_error("dup2");
    if (dup2(pipex.fdin, 0) < 0)
        msg_error("dup2");
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_first[0]);
    execve(pipex.cmd, pipex.cmd_first, envp);
    exit(127);
}

static void redirection_out(t_pipex pipex, char **envp) 
{
    if (dup2(pipex.pipe[0], 0) < 0)
        msg_error("dup2");
    if (dup2(pipex.fdout, 1) < 0)
        msg_error("dup2");
    close_pipe(pipex);
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_second[0]);
    execve(pipex.cmd, pipex.cmd_second, envp);
    exit(127);
}


void exec_pipe(t_pipex pipex, char **envp)
{
    pid_t pid1;
    pid_t pid2;

    if (pipe(pipex.pipe) < 0)
        msg_error("Pipe");
    pid1 = fork();
    if (pid1 == 0)
        redirection_in(pipex, envp);
    pid2 = fork();
    if (pid2 == 0)
        redirection_out(pipex, envp);
    close_pipe(pipex);
    waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
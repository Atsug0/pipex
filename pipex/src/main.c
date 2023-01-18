/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsug0 <atsug0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:20:11 by atsug0            #+#    #+#             */
/*   Updated: 2023/01/18 02:22:28 by atsug0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}


int main(int argc, char *argv[], char *envp[]) 
{
    t_pipex pipex;

    if (argc != 5)
        return (msg("Pas assez d'argument"));
    pipex.fdin = open(argv[1], O_RDONLY);
    pipex.fdout = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if (pipex.fdin < 0 ) 
        msg_error("Infile");
    if (pipex.fdout < 0)
        msg_error("Outfile");
    pipex.cmd_first = ft_split(argv[2], ' ');
    pipex.cmd_second = ft_split(argv[3], ' ');
    if (!pipex.cmd_first || !pipex.cmd_second)
    {
        close(pipex.fdin);
        close(pipex.fdout);
        msg_error("split");
    }
    pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
    exec_pipe(pipex, envp);
    ft_bigfree(pipex.cmd_first);
    ft_bigfree(pipex.cmd_second);
    close(pipex.fdin);
    close(pipex.fdout);
    return(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsug0 <atsug0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:16:47 by atsug0            #+#    #+#             */
/*   Updated: 2023/01/18 01:47:57 by atsug0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

typedef struct s_pipex
{
    int fdin;
    int fdout;
    int pipe[2];
    char **cmd_first;
    char **cmd_second;
    char *paths;
    char *cmd;
    char **cmd_paths;
    
}t_pipex;

char	**ft_bigfree(char **tab);
char	**ft_split(char *str, char charset);
void    exec_pipe(t_pipex pipex, char **envp);
int	    msg(char *err);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void	msg_error(char *err);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_s(char *str);



#endif
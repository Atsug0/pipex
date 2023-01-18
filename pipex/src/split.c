/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsug0 <atsug0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:13:54 by atsug0            #+#    #+#             */
/*   Updated: 2023/01/18 01:08:09 by atsug0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_bigfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	ft_len_w(char *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != charset)
		i++;
	return (i);
}

static int	ft_nbr_w(char *str, char charset)
{
	int	count;
	int	i;

	count = 0;
	while (*str)
	{
		while (*str && *str == charset)
			str++;
		i = ft_len_w(str, charset);
		str += i;
		if (i)
			count++;
	}
	return (count);
}

static char	*ft_copy(char *src, int n)
{
	char	*res;

	res = malloc((n + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[n] = '\0';
	while (n--)
		res[n] = src[n];
	return (res);
}

char	**ft_split(char *str, char charset)
{
	int		size;
	int		i;
	int		n;
	char	**tab;

	size = ft_nbr_w(str, charset);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*str && *str == charset)
			str++;
		n = ft_len_w(str, charset);
		tab[i] = ft_copy(str, n);
		if (!tab[i])
			return (ft_bigfree(tab));
		str += n;
	}
	tab[size] = 0;
	return (tab);
}


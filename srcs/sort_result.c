/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:37:57 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/20 19:02:25 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char		*path(char *dir, char *str)
{
	char	*result;

	if (dir == NULL)
		return (str);
	if (!(result = malloc(sizeof(char) *
						(ft_strlen(dir) + ft_strlen(str) + 3))))
		return (NULL);
	ft_strcpy(result, dir);
	if (str[0] != '/' && dir[ft_strlen(dir) - 1] != '/')
		ft_strcat(result, "/");
	ft_strcat(result, str);
	return (result);
}

t_data		*ft_stat(char *rep, char *str, t_data *ls)
{
	char	*way;

	way = path(rep, str);
	stat(way, &(ls->s));
	lstat(way, &(ls->s));
	free(way);
	return (ls);
}

char		**sortime(char **tab, t_data *ls, int size, char *rep)
{
	int		i;
	char	*tmp;
	int		timod;

	i = 0;
	timod = 0;
	tab = ft_sort_tab(tab, size);
	ls = ft_stat(rep, tab[i], ls);
	while (i < size)
	{
		timod = ls->s.st_mtime;
		ls = ft_stat(rep, tab[i + 1], ls);
		if (timod < ls->s.st_mtime || ((timod == ls->s.st_mtime)
			&& ft_strcmp(tab[i], tab[i + 1])))
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			ls = ft_stat(rep, tab[i], ls);
		}
		else
			i++;
	}
	return (tab);
}

char		**revtime(char **tab, t_data *ls, int size, char *rep)
{
	int		i;
	char	*tmp;
	int		timod;

	i = 0;
	timod = 0;
	tab = ft_rev_tab(tab, size);
	ls = ft_stat(rep, tab[i], ls);
	while (i < size)
	{
		timod = ls->s.st_mtime;
		ls = ft_stat(rep, tab[i + 1], ls);
		if (timod > ls->s.st_mtime || ((timod == ls->s.st_mtime)
			&& ft_strcmp(tab[i], tab[i + 1])))
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			ls = ft_stat(rep, tab[i], ls);
		}
		else
			i++;
	}
	return (tab);
}

char		**organize(char **tab, t_data *ls, int i, char *rep)
{
	if (ft_strchr(ls->args, 't'))
	{
		if (ft_strchr(ls->args, 'r'))
			tab = revtime(tab, ls, i, rep);
		else
			tab = sortime(tab, ls, i, rep);
	}
	else
	{
		if (ft_strchr(ls->args, 'r'))
			tab = ft_rev_tab(tab, i);
		else
			tab = ft_sort_tab(tab, i);
	}
	return (tab);
}

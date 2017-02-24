/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:37:57 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/21 02:54:57 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char		*path(char *dir, char *str)
{
	char	*result;

	if (dir == NULL)
		return (str);
	if (str[ft_strlen(str) - 1] != '/')
		result = ft_strjoin(dir, "/");
	else
		result = ft_strdup(dir);
	result = ft_strjoin(result, str);
	return (result);
}

char		**sortime(char **tab, t_data *ls, int size, char *rep)
{
	int		i;
	char	*tmp;
	int		timod;

	i = 0;
	timod = 0;
	tab = ft_sort_tab(tab, size);
	stat(path(rep, tab[i]), &(ls->s));
	while (i < size)
	{
		timod = ls->s.st_mtime;
		stat(path(rep, tab[i + 1]), &(ls->s));
		if (timod < ls->s.st_mtime)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			stat(path(rep, tab[i]), &(ls->s));
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
	stat(path(rep, tab[i]), &(ls->s));
	while (i < size)
	{
		timod = ls->s.st_mtime;
		stat(path(rep, tab[i + 1]), &(ls->s));
		if (timod > ls->s.st_mtime)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			stat(path(rep, tab[i]), &(ls->s));
		}
		else
			i++;
	}
	return (tab);
}

char	**organize(char **tab, t_data *ls, int i, char *rep)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:37:57 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/08 16:06:05 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char		**sortime(char **tab, t_data *ls, int size)
{
	int		i;
	char	*tmp;
	int		timod;

	i = 0;
	timod = 0;
	tab = ft_sort_tab(tab, size);
	stat(tab[i], &(ls->s));
	while (i < size)
	{
		timod = ls->s.st_mtime;
		stat(tab[i + 1], &(ls->s));
		if (timod < ls->s.st_mtime)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			stat(tab[i], &(ls->s));
		}
		else
			i++;
	}
	return (tab);
}

char		**revtime(char **tab, t_data *ls, int size)
{
	int		i;
	char	*tmp;
	int		timod;

	i = 0;
	timod = 0;
	tab = ft_rev_tab(tab, size);
	stat(tab[i], &(ls->s));
	while (i < size)
	{
		timod = ls->s.st_mtime;
		stat(tab[i + 1], &(ls->s));
		if (timod > ls->s.st_mtime)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
			stat(tab[i], &(ls->s));
		}
		else
			i++;
	}
	return (tab);
}

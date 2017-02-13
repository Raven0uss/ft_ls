/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:35:27 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/08 18:45:19 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void				aff_ls(t_data *ls, char **tab, int i)
{
	if (ft_strchr(ls->args, 't'))
	{
		if (ft_strchr(ls->args, 'r'))
			tab = revtime(tab, ls, i - 1);
		else
			tab = sortime(tab, ls, i - 1);
	}
	else
	{
		if (ft_strchr(ls->args, 'r'))
			tab = ft_rev_tab(tab, i - 1);
		else
			tab = ft_sort_tab(tab, i - 1);
	}
	if (ft_strchr(ls->args, 'l'))
		aff_ls_list(tab, ls);
	else
		ft_aff_tab(tab, "\n");
}

static void			ft_opt(t_data *ls, char **tab)
{
	int				i;

	i = 0;
	if (!(ls->reps[0]) && !(ft_strchr(ls->args, 'R')))
	{
		if (!(tab = malloc(sizeof(char *) * 1024)))
			return ;
		if (!(ls->dir = opendir(".")))
			perror("ft_ls: ");
		while ((ls->ent = readdir(ls->dir)))
			if (ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a'))
				tab[i++] = ft_strdup(ls->ent->d_name);
		aff_ls(ls, tab, i);
		closedir(ls->dir);
		free(tab);
	}
	else
		ft_optreps(ls, tab);
}

void				ft_ls(t_data *ls)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**tab;
	int				i;

	i = 0;
	tab = NULL;
	if (ls == NULL)
	{
		if (!(tab = malloc(sizeof(char *) * 1024)))//Allocation non precise
			return ;
		if (!(dir = opendir(".")))
			perror("ft_ls: ");
		while ((ent = readdir(dir)))
			if (ent->d_name[0] != '.')
				tab[i++] = ft_strdup(ent->d_name);
		ft_aff_tab(ft_sort_tab(tab, i - 1), "\n");
		closedir(dir);
		free(tab);
		return ;
	}
	else
		ft_opt(ls, tab);
	ft_strdel(&(ls->args));
	free(ls->reps);
}
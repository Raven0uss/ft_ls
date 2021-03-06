/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:35:27 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/13 19:07:59 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void				aff_ls(t_data *ls, char **tab, unsigned int i, char *rep)
{
	if (ft_strchr(ls->args, 't'))
	{
		if (ft_strchr(ls->args, 'r'))
			tab = revtime(tab, ls, i - 1, rep);
		else
			tab = sortime(tab, ls, i - 1, rep);
	}
	else
	{
		if (ft_strchr(ls->args, 'r'))
			tab = ft_rev_tab(tab, i - 1);
		else
			tab = ft_sort_tab(tab, i - 1);
	}
	if (ft_strchr(ls->args, 'l'))
		aff_ls_list(tab, ls, rep);
	else
		ft_aff_tab(tab, "\n");
}

static void			ft_opt(t_data *ls, char **tab, unsigned int i)
{
	if (!(ls->reps[0]) && !(ft_strchr(ls->args, 'R')))
	{
		if (!(tab = malloc(sizeof(char *) * 42424)))
			return ;
		if (!(ls->dir = opendir(".")))
			perror("ft_ls: ");
		while ((ls->ent = readdir(ls->dir)))
			if (ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a'))
				tab[i++] = ft_strdup(ls->ent->d_name);
		if (i != 0)
			aff_ls(ls, tab, i, "./");
		closedir(ls->dir);
		free(tab);
	}
	else
	{
		if (!(ls->reps[0]))
		{
			ls->reps[0] = ft_strdup(".");
			ls->reps[1] = 0;
		}
		ft_optreps(ls, tab, 0);
	}
}

void				ft_ls(t_data *ls, unsigned int i)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**tab;

	tab = NULL;
	if (ls == NULL)
	{
		if (!(tab = malloc(sizeof(char *) * 42424)))
			return ;
		if (!(dir = opendir(".")))
			perror("ft_ls: ");
		while ((ent = readdir(dir)))
			if (ent->d_name[0] != '.')
				tab[i++] = ft_strdup(ent->d_name);
		if (i != 0)
			ft_aff_tab(ft_sort_tab(tab, i - 1), "\n");
		closedir(dir);
		free(tab);
		return ;
	}
	else
		ft_opt(ls, tab, 0);
	ft_strdel(&(ls->args));
	free(ls->reps);
}

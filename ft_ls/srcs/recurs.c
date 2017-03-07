/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:36:43 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/07 12:48:34 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**encrust_rec(t_data *ls, int pos)
{
	unsigned int		size;
	unsigned int		i;
	unsigned int		max;
	unsigned int		count;

	size = ft_sizetab(ls->recs) - 1;
	max = ft_sizetab(ls->reps);
	count = max;
	i = 0;
	ls->reps[max + size] = 0;
	while (pos != max)
	{
		ls->reps[max + size] = ft_strdup(ls->reps[--count]);
		max--;
	}
	while (ls->recs[i])
	{
		ls->reps[pos++] = ft_strdup(ls->recs[i]);
		free(ls->recs[i]);
		ls->recs[i++] = 0;
	}
	return (ls->reps);
}

char	**add_repository(char *to_add, char *dir, t_data *ls)
{
	int		i;

	i = 0;
	while (ls->recs[i])
		i++;
	ls->recs[i++] = ft_strdup(path(dir, to_add));
	ls->recs[i] = 0;
	//ls->recs = organize(ls->recs, ls, i - 1, NULL);
	return (ls->recs);
}

static char	**add_to_reps(t_data *ls, int pos)
{
	int		i;

	i = 0;
	if (!ls->reps[pos])
	{
		while (ls->recs[i])
		{
			ls->reps[pos++] = ft_strdup(ls->recs[i]);
			free(ls->recs[i]);
			ls->recs[i++] = 0;
		}
		ls->reps[pos] = 0;
	}
	else
		ls->reps = encrust_rec(ls, pos);
	return (ls->reps);
}

static char 	**ft_aff_tab_rec(char **tab, char *sep, char *rep, t_data *ls)
{
	int			i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		stat(path(rep, tab[i]), &(ls->s));
		if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode)
			&& (ft_strcmp(".", tab[i]) && ft_strcmp("..", tab[i])))
			ls->recs = add_repository(tab[i], rep, ls);
		i++;
		if (tab[i])
			ft_putstr(sep);
	}
	ft_putchar('\n');
	return (ls->recs);
}

static char		**aff_ls_rec(t_data *ls, char **tab, int i, char *rep)
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
		ls->recs = aff_ls_list_rec(tab, ls, rep);
	else
		ls->recs = ft_aff_tab_rec(tab, "  ", rep, ls);
	return (ls->recs);
}

static		char	**loop_optreps(t_data *ls, char **tab, char *repo)
{
	unsigned int		i;

	i = 0;
	ls->recs[0] = NULL;
	if (!(ls->dir = opendir(repo)))
		perror(repo);
	else
	{
		while ((ls->ent = readdir(ls->dir)))
			if (ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a'))
				tab[i++] = ft_strdup(ls->ent->d_name);
		tab[i] = 0;
		ls->recs = aff_ls_rec(ls, tab, i, repo);
		closedir(ls->dir);
	}
	return (ls->recs);
}

static void	ft_recurs(t_data *ls)
{
	int		i;

	i = 0;
	while (ls->recs[i])
	{
		i++;
	}
}


void		ft_optreps(t_data *ls, char **tab, int j)
{
	if (ls->reps[j])
	{
		if (!(tab = malloc(sizeof(char *) * 1024)))
			return ;
		ls->recs = loop_optreps(ls, tab, ls->reps[j]);
		free(tab);
		if (ls->recs[0] != NULL)
			; // Recursive has to work
			//ft_recurs(ls);
			//ls->reps = add_to_reps(ls, j + 1);
		if (ls->reps[++j])
		{
			ft_putchar('\n');
			ft_putstr(ls->reps[j]);
			ft_putendl(":");
		}
		ft_optreps(ls, tab, j);
	}
}

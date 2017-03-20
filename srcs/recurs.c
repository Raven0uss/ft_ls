/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:36:43 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/20 19:55:42 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char			**encrust_rec(t_data *ls, unsigned int pos)
{
	unsigned int	size;
	unsigned int	i;
	unsigned int	max;
	unsigned int	count;

	size = ft_sizetab(ls->recs) - 1;
	max = ft_sizetab(ls->reps);
	count = max;
	i = 0;
	ls->reps[max + size + 1] = 0;
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

static char			**add_to_reps(t_data *ls, unsigned int pos)
{
	unsigned int	i;

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

static	char		**loop_optreps(t_data *ls, char **tab, char *repo)
{
	unsigned int	i;

	i = 0;
	ls->recs[0] = NULL;
	if (!(ls->dir = opendir(repo)))
		perror(ft_strjoin("ft_ls: ", repo));
	else
	{
		while ((ls->ent = readdir(ls->dir)))
			if (ls->ent->d_name[0] &&
				(ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a')))
				tab[i++] = ft_strdup(ls->ent->d_name);
		tab[i] = 0;
		if (i != 0)
			ls->recs = aff_ls_rec(ls, tab, i, repo);
		closedir(ls->dir);
	}
	return (ls->recs);
}

static char			**remove_first(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i + 1])
			tab[i] = ft_strdup(tab[i + 1]);
		else
		{
			tab[i] = 0;
			return (tab);
		}
		i++;
	}
	return (tab);
}

void				ft_optreps(t_data *ls, char **tab, unsigned int j)
{
	if (ls->reps[j])
	{
		if (!(tab = malloc(sizeof(char *) * 42424)))
			return ;
		ls->recs = loop_optreps(ls, tab, ls->reps[j]);
		if (ls->recs[0] != NULL)
			ls->reps = add_to_reps(ls, j + 1);
		free(tab);
		if (ls->reps[j + 1])
		{
			ft_putchar('\n');
			ft_putstr(ls->reps[j + 1]);
			ft_putendl(":");
		}
		ls->reps = remove_first(ls->reps);
		ft_optreps(ls, tab, j);
	}
}

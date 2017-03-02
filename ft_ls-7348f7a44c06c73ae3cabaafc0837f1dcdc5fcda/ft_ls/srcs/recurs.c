/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:36:43 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/02 21:50:54 by sbelazou         ###   ########.fr       */
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

static char	**add_repository(char *to_add, char *dir, t_data *ls)
{
	int		i;

	i = 0;
	while (ls->recs[i])
		i++;
	ls->recs[i++] = ft_strdup(path(dir, to_add));
	ls->recs[i] = 0;
	ls->recs = organize(ls->recs, ls, i - 1, NULL);
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

static char	**loop_optreps(t_data *ls, char **tab, char *repo)
{
	int		i;

	i = 0;
	ls->recs[0] = NULL;
	if (!(ls->dir = opendir(repo)))
		perror(repo);
	else
	{
		while ((ls->ent = readdir(ls->dir)))
			if (ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a'))
			{
				tab[i] = ft_strdup(ls->ent->d_name);
				stat(path(repo, tab[i]), &(ls->s));
				if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode)
					&& (ft_strcmp(".", tab[i]) && ft_strcmp("..", tab[i])))
					ls->recs = add_repository(tab[i], repo, ls);
				i++;
			}
		tab[i] = 0;
		aff_ls(ls, tab, i, repo);
		closedir(ls->dir);
	}
	return (ls->recs);
}
/*
void		ft_optreps(t_data *ls, char **tab)
{
	int		i;
	int		j;
	char	**rec;

	j = 0;
	if (!ls->reps[0] && ft_strchr(ls->args, 'R'))
	{
		ls->reps[0] = ft_strdup(".");
		ls->reps[1] = 0;
	}
	while (ls->reps[j])
	{
		if (!(tab = malloc(sizeof(char *) * 10240)))// Allocation non precise
			return ;
		rec = loop_optreps(ls, tab, rec, ls->reps[j]);
		free(tab);
		if (rec[0] != NULL)
			ls->reps = add_to_reps(rec, ls, j + 1);
		if (ls->reps[++j])
		{
			ft_putchar('\n');
			ft_putstr(ls->reps[j]);
			ft_putendl(":");
		}
	}
	}*/


void		ft_optreps(t_data *ls, char **tab, int j)
{
	if (ls->reps[j])
	{
		if (!(tab = malloc(sizeof(char *) * 1024)))
			return ;
		ls->recs = loop_optreps(ls, tab, ls->reps[j]);
		free(tab);
		if (ls->recs[0] != NULL)
			ls->reps = add_to_reps(ls, j + 1);
		if (ls->reps[++j])
		{
			ft_putchar('\n');
			ft_putstr(ls->reps[j]);
			ft_putendl(":");
		}
		ft_optreps(ls, tab, j);
	}
}

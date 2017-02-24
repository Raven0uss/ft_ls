/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:36:43 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/21 04:53:21 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**encrust_rec(char **rec, t_data *ls, int pos)
{
	unsigned int		size;
	unsigned int		i;
	unsigned int		max;
	unsigned int		count;

	size = ft_sizetab(rec) - 1;
	max = ft_sizetab(ls->reps);
	count = max;
	i = 0;
	ls->reps[max + size] = 0;
	while (pos != max)
	{
		ls->reps[max + size] = ft_strdup(ls->reps[--count]);
		max--;
	}
	while (rec[i])
	{
		ls->reps[pos++] = ft_strdup(rec[i]);
		free(rec[i++]);
	}
	free(rec);
	return (ls->reps);
}

static char	**add_repository(char *to_add, char **rec, char *dir, t_data *ls)
{
	int		i;

	i = 0;
	while (rec[i])
		i++;
	rec[i++] = ft_strdup(path(dir, to_add));
	rec[i] = 0;
	rec = organize(rec, ls, i - 1, NULL);
	return (rec);
}

static char	**add_to_reps(char **rec, t_data *ls, int pos)
{
	int		i;

	i = 0;
	if (!ls->reps[pos])
	{
		while (rec[i])
		{
			ls->reps[pos++] = ft_strdup(rec[i]);
			free(rec[i++]);
		}
		free(rec);
		ls->reps[pos] = 0;
	}
	else
		ls->reps = encrust_rec(rec, ls, pos);
	return (ls->reps);
}

static char	**loop_optreps(t_data *ls, char **tab, char **rec, char *repo)
{
	int		i;

	i = 0;
	if (!(rec = malloc(sizeof(char *) * 1024)))
		return (NULL);
	rec[0] = NULL;
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
					rec = add_repository(tab[i], rec, repo, ls);
				i++;
			}
		tab[i] = 0;
		aff_ls(ls, tab, i, repo);
		closedir(ls->dir);
	}
	return (rec);
}

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
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:36:43 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/21 01:27:06 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**encrust_rec(char **rec, t_data *ls, int pos)
{
	int		size;
	int		i;
	int		max;

	size = ft_sizetab(rec);
	max = ft_sizetab(ls->reps);
	i = 0;
	while (pos != max)
	{
		ls->reps[max + i] = ft_strdup(ls->reps[pos]);
		if (rec[i])
		{
			ls->reps[pos] = ft_strdup(rec[i]);
			free(rec[i]);
		}
		i++;
		pos++;
	}
	free(rec);
	ls->reps[max + i] = 0;
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
	//ft_aff_tab(rec ," = ");
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

void		ft_optreps(t_data *ls, char **tab)
{
	int		i;
	int		j;
	char	**rec;

	i = 0;
	j = 0;
	if (!ls->reps[0] && ft_strchr(ls->args, 'R'))
	{
		ls->reps[0] = ft_strdup(".");
		ls->reps[1] = 0;
	}
	while (ls->reps[j])
	{
		i = 0;
		if (!(rec = malloc(sizeof(char *) * 1024)))
			return ;
		rec[0] = NULL;
		if (!(tab = malloc(sizeof(char *) * 1024))) // Allocation non precise
			return ;
		if (!(ls->dir = opendir(ls->reps[j])))
			perror(ls->reps[j]);
		else
		{
			while ((ls->ent = readdir(ls->dir)))
				if (ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a'))
				{
					tab[i] = ft_strdup(ls->ent->d_name);
					stat(path(ls->reps[j], tab[i]), &(ls->s));
					if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode))
						rec = add_repository(tab[i], rec, ls->reps[j], ls);
					i++;
				}
			tab[i] = 0;
			aff_ls(ls, tab, i, ls->reps[j]);
			closedir(ls->dir);
		}
		free(tab);
		j++;
		if (rec[0] != NULL)
		{
			ls->reps = add_to_reps(rec, ls, j);
		}
		if (ls->reps[j])
		{
			ft_putchar('\n');
			ft_putstr(ls->reps[j]);
			ft_putendl(":");
		}
	}
}

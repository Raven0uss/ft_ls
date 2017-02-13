/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:36:43 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/08 18:58:02 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**add_repository(char *to_add, int pos, char **reps, char *cur)
{
	int		i;

	i = 0;
	return (reps);
}

void		ft_optreps(t_data *ls, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ls->reps[j])
	{
		if (!(tab = malloc(sizeof(char *) * 1024)))
			return ;
		if (!(ls->dir = opendir(ls->reps[j])))
			perror(ls->reps[j]);
		while ((ls->ent = readdir(ls->dir)))
			if (ls->ent->d_name[0] != '.' || ft_strchr(ls->args, 'a'))
			{
				tab[i] = ft_strdup(ls->ent->d_name);
				stat(tab[i], &(ls->s));
				if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode))
					ls->reps = add_repository(tab[i], j, ls->reps, ls->reps[j]);
				i++;
			}
		aff_ls(ls, tab, i);
		closedir(ls->dir);
		free(tab);
		j++;
	}
}

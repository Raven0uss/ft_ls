/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:42:28 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/13 18:35:11 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char				**add_repository(char *to_add, char *dir, t_data *ls)
{
	unsigned int	i;

	i = 0;
	while (ls->recs[i])
		i++;
	ls->recs[i++] = ft_strdup(path(dir, to_add));
	ls->recs[i] = 0;
	return (ls->recs);
}

static char			**ft_disprtab(char **tab, char *sep, char *rep, t_data *ls)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		ls = ft_stat(rep, tab[i], ls);
		if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode)
			&& ((ft_strcmp(".", tab[i]) && ft_strcmp("..", tab[i]))))
			ls->recs = add_repository(tab[i], rep, ls);
		i++;
		if (tab[i])
			ft_putstr(sep);
	}
	ft_putchar('\n');
	return (ls->recs);
}

char				**aff_ls_rec(t_data *ls, char **tab, int i, char *rep)
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
		ls->recs = ft_disprtab(tab, "\n", rep, ls);
	return (ls->recs);
}

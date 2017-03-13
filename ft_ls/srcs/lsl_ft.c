/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsl_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:42:42 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/13 18:38:41 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char				**aff_ls_list_rec(char **tab, t_data *ls, char *rep)
{
	int				i;

	i = 0;
	ls = get_ttx(tab, rep, ls);
	ft_putstr("total ");
	ft_putnbr(ls->ttx->ttl);
	ft_putchar('\n');
	while (tab[i])
	{
		ls = ft_stat(rep, tab[i], ls);
		aff_stat(ls);
		if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode)
			&& (ft_strcmp(".", tab[i]) && ft_strcmp("..", tab[i])))
			ls->recs = add_repository(tab[i], rep, ls);
		ft_putendl(tab[i++]);
	}
	free(ls->ttx);
	return (ls->recs);
}

void				aff_ls_list(char **tab, t_data *ls, char *rep)
{
	int				i;

	i = 0;
	ls = get_ttx(tab, rep, ls);
	ft_putstr("total ");
	ft_putnbr(ls->ttx->ttl);
	ft_putchar('\n');
	while (tab[i])
	{
		ls = ft_stat(rep, tab[i], ls);
		aff_stat(ls);
		ft_putendl(tab[i++]);
	}
	free(ls->ttx);
}

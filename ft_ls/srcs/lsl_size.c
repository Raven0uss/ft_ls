/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:19:26 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/13 19:18:30 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static t_lsize		*init_size(t_lsize *ttx)
{
	if (!(ttx = malloc(sizeof(t_lsize))))
		return (NULL);
	ttx->ttl = 0;
	ttx->sze = 0;
	ttx->grp = 0;
	ttx->usr = 0;
	ttx->lnk = 0;
	ttx->low = 0;
	ttx->upr = 0;
	return (ttx);
}

static t_lsize		*padding(t_lsize *ttx, struct stat s)
{
	ttx->sze = ((int)ft_intlen(s.st_size) > (int)ttx->sze ?
				(int)ft_intlen(s.st_size) : ttx->sze);
	ttx->lnk = ((int)ft_intlen(s.st_nlink) > (int)ttx->lnk ?
				(int)ft_intlen(s.st_nlink) : ttx->lnk);
	ttx->upr = ((int)ft_intlen(UP(s.st_rdev)) > (int)ttx->upr ?
				(int)ft_intlen(UP(s.st_rdev)) : ttx->upr);
	ttx->low = ((int)ft_intlen(LOW(s.st_rdev)) > (int)ttx->low ?
				(int)ft_intlen(LOW(s.st_rdev)) : ttx->low);
	ttx->ttl += s.st_blocks;
	return (ttx);
}

static t_lsize		*calc_total(char **tab, char *rep, t_data *ls)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		ls = ft_stat(rep, tab[i++], ls);
		ls->ttx = padding(ls->ttx, ls->s);
	}
	return (ls->ttx);
}

t_data				*get_ttx(char **tab, char *rep, t_data *ls)
{
	ls->ttx = init_size(ls->ttx);
	ls->ttx = calc_total(tab, rep, ls);
	return (ls);
}

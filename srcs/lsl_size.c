/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:19:26 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/22 16:35:44 by sbelazou         ###   ########.fr       */
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
	ttx->sbd = 0;
	ttx->dvc = 0;
	return (ttx);
}

static t_lsize		*padding(t_lsize *ttx, struct stat s)
{
	ttx->sze = ((int)ft_intlen(s.st_size) > (int)ttx->sze ?
				(int)ft_intlen(s.st_size) : (int)ttx->sze);
	ttx->lnk = ((int)ft_intlen(s.st_nlink) > (int)ttx->lnk ?
				(int)ft_intlen(s.st_nlink) : (int)ttx->lnk);
	ttx->dvc = ((int)ft_intlen(DEVICE(s.st_rdev)) > (int)ttx->dvc ?
				(int)ft_intlen(DEVICE(s.st_rdev)) : (int)ttx->dvc);
	ttx->sbd = ((int)ft_intlen(SUBDEV(s.st_rdev)) > (int)ttx->sbd ?
				(int)ft_intlen(SUBDEV(s.st_rdev)) : (int)ttx->sbd);
	if (getpwuid(s.st_uid))
		ttx->usr = ((int)ft_strlen(getpwuid(s.st_uid)->pw_name))
			> (int)ttx->usr ?
			((int)ft_strlen(getpwuid(s.st_uid)->pw_name)) : (int)ttx->usr;
	else
		ttx->usr = 1;
	if (getgrgid(s.st_gid))
		ttx->grp = ((int)ft_strlen(getgrgid(s.st_gid)->gr_name))
			> (int)ttx->grp ?
			((int)ft_strlen(getgrgid(s.st_gid)->gr_name)) : (int)ttx->grp;
	else
		ttx->grp = 1;
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

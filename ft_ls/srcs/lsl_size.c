/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:19:26 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/12 15:28:32 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static t_lsize	*init_size(t_lsize *ttx)
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

static t_lsize	*fill_size(t_lsize *ttx, struct stat s)
{
  ttx->sze = ((int)ft_intlen(s.st_size) > ttx->sze ?
	      (int)ft_intlen(s.st_size) : ttx->sze);
  ttx->lnk = ((int)ft_intlen(s.st_nlink) > ttx->lnk ?
	      (int)ft_intlen(s.st_st_nlink) : ttx->lnk);
  return (ttx);
}

static int	calc_total(char **tab, char *rep, t_lsize ttx, t_data *ls)
{
  unsigned int	i;
  char		*way;
  int		total;
  
  i = 0;
  while (tab[i])
    {
      way = path(rep, tab[i]);
      stat(way, &(ls->s));
      free(way);
      ttx = fill_size(ttx, ls->s);
    }
  return (total);
}

int		get_total(char **tab, char *rep, t_data *ls)
{
  t_lsize	*ttx;
  int		total;

  total = 0;
  ttx = init_size(ttx);
  total = calc_total(tab, rep, ttx, ls);
  free(ttx);
  return (total);
}

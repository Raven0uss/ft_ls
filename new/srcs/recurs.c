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

static char	**place(char **recur, t_data *ls, int pos, int size)
{
  char		*tmp;
  int		i;

  i = 0;
  if (!ls->reps[pos + 1])
    {
      while (i <= size)
	ls->reps[++pos] = ft_strdup(recur[i++]);
    }
  while (i != size)
    {
       (ls->reps[pos])
	
	  tmp = ls->reps[pos];
    
      
    }
}


static char	**add_repository(t_data *ls, char *rep, int pos)
{
  static char	**recur = NULL;
  char		*tmp;
  int		i;

  i = 0;
  if (recur == NULL)
    if (!(recur = malloc(sizeof(char *) * 1024)))
      return (NULL);
  while (recur[i])
    i++;
  recur[i++] = ft_strdup(rep);
  recur[i] = 0;
  if (ft_strchr(ls->args, 't'))
    {
      if (ft_strchr(ls->args, 'r'))
	recur = revtime(recur, ls, i - 1);
      else
	recur = sortime(recur, ls, i - 1);
    }
  else if (ft_strchr(l->args, 'r'))
    recur = ft_rev_tab(recur, i - 1);
  else
    recur = ft_sort_tab(recur, i - 1);
  ls->reps = place(recur, ls, pos, i - 1);
}

void		ft_optreps(t_data *ls, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ls->reps[j])
	    ls->reps[j] = ft_strdup('.');
	while (ls->reps[j])
	{
		i = 0;
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
				  ls->reps = add_repository(ls, tab[i], j)
				i++;
			}
		aff_ls(ls, tab, i);
		closedir(ls->dir);
		free(tab);
		j++;
	}
}

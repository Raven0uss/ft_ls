/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:56:04 by sbelazou          #+#    #+#             */
/*   Updated: 2016/12/20 21:08:57 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*checker_av(char *str, char *args)
{
  int		i;
  int		j;
  int		k;

  k = 0;
  i = 1;
  j = 0;
  if (args != NULL)
    k = ft_strlen(args);
  while (str[i])
    {  
      while (OPTS[j])
	if (str[i] == OPTS[j++])
	  {
	    args[k++] = str[i++];
	    j = 0;
	    break ;
	  }
      if (j != 0)
	exit(1); //message error to fix
    }
  return (args);
}

static void	ft_ls_opt(t_ls *dc)
{
  int		i;
  int		j;

  j = 0;
  if (dc->reps == NULL)
    {
      dc->dir = opendir(".");
      ft_ls(dc);
      closedir(dc->dir);
    }
  else
    {
      i = ft_sizetab(dc->reps) - 1;
      closedir(dc->dir);
      if ((dc->file = malloc(sizeof(t_file))) == NULL)
	return ;
      if ((dc->file->tab = malloc(sizeof(char *) * 1024)) == NULL)
	return ;
      while (i > -1)
	{
	  if ((dc->dir = opendir(dc->reps[i])) == NULL)
	    {
	      ft_putstr(dc->bin);
	      perror(dc->reps[i]);
	    }
	  else
	    {
	      j = 0;
	      if (ft_sizetab(dc->reps) != 1)
		{
		  ft_putstr(dc->reps[i]);
		  ft_putendl(":");
		}
	      ft_ls(dc);
	      while ((dc->file->ent = readdir(dc->dir)))
		dc->file->tab[j++] = ft_strdup(dc->file->ent->d_name);
	      dc->file->tab[j] = NULL;
	      ft_aff_tab(ft_sort_tab(dc->file->tab, j - 1), "  ");
	      closedir(dc->dir);
	    }
	  i--;
	  if (i != -1 && j != 0)
	    ft_putchar('\n');
	}
    }
}

void	opt(t_ls *dc, char **av, int ac)
{
  int	i;
  int	k;

  i = 1;
  k = 0;
  if ((dc->reps = malloc(sizeof(char *) * ac)) == NULL)
    return ;
  if ((dc->l_args = malloc(sizeof(char *) * ac)) == NULL)
    return ;
  while (av[i])
    {
      if (av[i][0] == '-')
	dc->l_args = checker_av(av[i], dc->l_args);
      else
	dc->reps[k++] = ft_strdup(av[i]);
      i++;
    }
  if (k == 0)
    dc->reps = NULL;
  if (dc->l_args == NULL)
    return ;
  dc->l_args = ft_onlyone(dc->l_args);
  ft_putendl(dc->l_args);
  ft_ls_opt(dc);
}

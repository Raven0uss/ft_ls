/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:55:56 by sbelazou          #+#    #+#             */
/*   Updated: 2016/12/20 21:08:52 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_ls(t_ls *dc)
{
  int		hide;
  int		f;

  f = 0;
  hide = 0;
  if ((dc->file = malloc(sizeof(t_file))) == NULL)
    return ;
  dc->file->ent = readdir(dc->dir);
  while (dc->file->ent)
    {
      hide = 1;
      if (dc->file->ent->d_name[0] != '.')
	{
	  ft_putstr(dc->file->ent->d_name);
	  f = 1;
	}
      if ((dc->file->ent = readdir(dc->dir)) == NULL)
	ft_putchar('\n');
      else if (dc->file->ent->d_name[0] == '.')
	hide = 0;
      if (hide && dc->file->ent != NULL && f)
	ft_putchar(' ');
    }
}

static char *crt_bname(char *name)
{
  char		*bin;

  if ((bin = ft_strdup(name)) == NULL)
    return (NULL);
  if ((bin = ft_strjoin(name, ": ")) == NULL)
    return (NULL);
  return (bin);
}

int		main(int ac, char **av)
{
	t_ls		*dir_content;

	if ((dir_content = malloc(sizeof(t_ls))) == NULL)
		return (-1);
	if ((dir_content->bin = crt_bname(av[0])) == NULL)
		return (-1);
	dir_content->dir = NULL;
	if (ac == 1)
    {
		if ((dir_content->dir = opendir(".")) == NULL)
			perror(dir_content->bin);
		else
			ft_ls(dir_content);
    }
	else
	{
		if ((dir_content->reps = malloc(sizeof(char *) * ac)) == NULL)
			return (-1);
		opt(dir_content, av);
		free(dir_content->reps);
	}
	if (dir_content->dir)
		closedir(dir_content->dir);
	free(dir_content->bin);
	free(dir_content);
	return (0);
}

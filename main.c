/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 15:33:33 by sbelazou          #+#    #+#             */
/*   Updated: 2017/01/10 19:18:08 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(t_ls *dc)
{
	int		i;
	char	*sep;

	i = 0;
	if (ft_strchr(dc->l_args, 'l'))
		sep = ft_strdup("\n");
	else
		sep = ft_strdup("  ");
	if ((dc->file = malloc(sizeof(t_file))) == NULL)
		return ;
	if ((dc->file->tab = malloc(sizeof(char *) * 1024)) == NULL)
		return ;
	while ((dc->file->ent = readdir(dc->dir)))
		if (dc->file->ent->d_name[0] != '.' || ft_strchr(dc->l_args, 'a'))
			dc->file->tab[i++] = ft_strdup(dc->file->ent->d_name);
	if (ft_strchr(dc->l_args, 'r'))
		ft_aff_tab(ft_rev_tab(dc->file->tab, i - 1), sep);
	else
		ft_aff_tab(ft_sort_tab(dc->file->tab, i - 1), sep);
}

static char	*crt_bname(char *name)
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
  if ((dir_content->dir = opendir(".")) == NULL)
    perror(dir_content->bin);
  if (ac == 1)
    ft_ls(dir_content);
  else
    opt(dir_content, av, ac);
  if (ac == 1)
    closedir(dir_content->dir);
  free(dir_content->bin);
  free(dir_content);
  return (0);
}

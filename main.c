/*
** main.c for  in /home/ravenous/42/ft_ls
** 
** Made by Sofiane Belazouz
** 
** Started on  Fri Dec 16 19:31:48 2016 Sofiane Belazouz
** Last update Thu Dec 22 13:25:46 2016 Sofiane Belazouz
*/

#include "ft_ls.h"

static void	ft_ls(t_ls *dc)
{
  int		hide;
  int		i;

  i = 0;
  if ((dc->file = malloc(sizeof(t_file))) == NULL)
    return ;
  if ((dc->file->tab = malloc(sizeof(char *) * 1024)) == NULL)
    return ;
  while ((dc->file->ent = readdir(dc->dir)))
    if (dc->file->ent->d_name[0] != '.')
      dc->file->tab[i++] = ft_strdup(dc->file->ent->d_name);
  ft_aff_tab(ft_sort_tab(dc->file->tab, i - 1), "  ");
}

static char	*crt_bname(char *name)
{
  char		*bin;
  
  if ((bin = ft_strdup(name)) == NULL)
    return (NULL);
  if ((bin = ft_strjoin(name, ": ")) == NULL)
    return (NULL);
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
    opt(dir_content, av);
  closedir(dir_content->dir);
  free(dir_content->bin);
  free(dir_content);
  return (0);
}

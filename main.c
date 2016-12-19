/*
** main.c for  in /home/ravenous/42/ft_ls
** 
** Made by Sofiane Belazouz
** 
** Started on  Fri Dec 16 19:31:48 2016 Sofiane Belazouz
** Last update Mon Dec 19 19:20:28 2016 Sofiane Belazouz
*/

#include "ft_ls.h"

static void	ft_ls(t_ls *dc)
{
  int		hide;

  hide = 10;
  dc->ent = readdir(dc->dir);
  while (dc->ent)
    {
      hide = 0;
      if (dc->ent->d_name[0] != '.')
	  ft_putstr(dc->ent->d_name);
      if ((dc->ent = readdir(dc->dir)) == NULL)
	ft_putchar('\n');
      if (dc->ent->d_name[0] == '.')
	hide = 1;
      if (!hide && dc->ent != NULL)
	ft_putchar(' ');
    }
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
  if (ac == 1)
    {
      if ((dir_content->dir = opendir(".")) == NULL)
	perror(dir_content->bin);
      else
	ft_ls(dir_content);
    }
  else
    puts(av[1]);
    //ft_ls_wo(ac, av);
    /*if ((dir = opendir(av[1])) == NULL)
      perror(ft_strcat(bin, av[1]));*/
  closedir(dir_content->dir);
  free(dir_content->bin);
  free(dir_content);
  return (0);
}

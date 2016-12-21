/*
** options.c for  in /home/ravenous/42/ft_ls
** 
** Made by Sofiane Belazouz
** Login   <belazo_s@epitech.net>
** 
** Started on  Mon Dec 19 19:23:42 2016 Sofiane Belazouz
** Last update Mon Dec 19 22:18:22 2016 Sofiane Belazouz
*/

#include "ft_ls.h"

static int	checker_av(char *str)
{
  int		i;

  i = 0;
  while (i != OPT_NB)
      if (ft_strcmp(str, OPTS[i++]) == 0)
	return (1);
  return (0);
}

void	opt(t_ls *dc, char **av)
{
  int	i;

  i = 1;
  while (av[i])
    {
      if (checker_av(av[i]))
	ft_putstr(av[i]);
      else
	{
	  if ((dc->dir = opendir(av[i])) == NULL)
	    {
	      perror(ft_strjoin(dc->bin, av[i]));
	      return ;
	    }
	}
      i++;
    }
  if (av[i])
    ft_putendl(av[i]);
}

/*
** ft_ls.h for  in /home/ravenous/42/ft_ls
** 
** Made by Sofiane Belazouz
** 
** Started on  Fri Dec 16 20:43:08 2016 Sofiane Belazouz
** Last update Mon Dec 19 19:00:08 2016 Sofiane Belazouz
*/

#ifndef FT_LS
# define FT_LS

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>

typedef struct		s_ls
{
  DIR			*dir;
  struct dirent		*ent;
  char			*bin;
}			t_ls;

#endif /* FT_LS */

/*
** ft_ls.h for  in /home/ravenous/42/ft_ls
** 
** Made by Sofiane Belazouz
** 
** Started on  Fri Dec 16 20:43:08 2016 Sofiane Belazouz
** Last update Mon Dec 19 20:29:50 2016 Sofiane Belazouz
*/

#ifndef FT_LS
# define FT_LS

# define OPTS ((char const*[]){"-l", "-R", "-a", "-r", "-t"})
# define OPT_NB 5

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>

typedef	struct		s_file
{
  struct dirent		*ent;
  char			*sep;
  struct s_file		*next;
}			t_file;

typedef struct		s_ls
{
  DIR			*dir;
  struct s_file		*file;
  char			*bin;
}			t_ls;

void			opt(t_ls *dc, char **arg);

#endif /* FT_LS */

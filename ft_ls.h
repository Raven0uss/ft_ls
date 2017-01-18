/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:55:47 by sbelazou          #+#    #+#             */
/*   Updated: 2017/01/11 16:04:04 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPTS " lRart"
# define OPT_NB 5

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

typedef	struct		s_file
{
	struct dirent	*ent;
	char			**tab;
	struct stat		s;
}					t_file;

typedef struct		s_ls
{
	DIR				*dir;
	struct s_file	*file;
	char			*bin;
	char			*l_args;
	char			**reps;
}					t_ls;

void				opt(t_ls *dc, char **arg, int ac);
void				ft_ls(t_ls *dc, char *rep);
char				*path(char *rep, char *name);

#endif
















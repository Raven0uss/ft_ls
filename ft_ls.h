/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:55:47 by sbelazou          #+#    #+#             */
/*   Updated: 2016/12/20 21:09:09 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPTS ((char const*[]){"-l", "-R", "-a", "-r", "-t"})
# define OPT_NB 5

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>

typedef	struct		s_file
{
	struct dirent	*ent;
	char		**tab;
	struct s_file	*next;
}					t_file;

typedef struct		s_ls
{
	DIR				*dir;
	struct s_file	*file;
	char			*bin;
	char			l_args[OPT_NB];
	char			**reps;
}					t_ls;

void				opt(t_ls *dc, char **arg);

#endif
















/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:16:53 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/06 21:33:35 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define OPTS " lRart"

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

typedef struct		s_data
{
	DIR				*dir;
	struct dirent	*ent;
	struct stat		s;
	char			**reps;
	char			*args;
	char			**recs;
}					t_data;

void				ft_ls(t_data *ls);
char				**sortime(char **tab, t_data *ls, int size, char *rep);
char				**revtime(char **tab, t_data *ls, int size, char *rep);
void				aff_ls_list(char **tab, t_data *ls, char *rep);
void				ft_optreps(t_data *ls, char **tab, int j);
void				aff_ls(t_data *ls, char **tab, int i, char *rep);
char				*path(char *dir, char *str);
char				**organize(char **tab, t_data *ls, int i, char *rep);
char				**aff_ls_list_rec(char **tab, t_data *ls, char *rep);
char				**add_repository(char *to_add, char *dir, t_data *ls);

#endif

/*
TODO:

!- calculer le padding + calc total dans aff_ls_list
!!- ameliorer -R
- flags gcc
- leaks

 */







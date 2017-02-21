/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:16:53 by sbelazou          #+#    #+#             */
/*   Updated: 2017/02/21 01:17:40 by sbelazou         ###   ########.fr       */
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
}					t_data;

void				ft_ls(t_data *ls);
char				**sortime(char **tab, t_data *ls, int size, char *rep);
char				**revtime(char **tab, t_data *ls, int size, char *rep);
void				aff_ls_list(char **tab, t_data *ls, char *rep);
void				ft_optreps(t_data *ls, char **tab);
void				aff_ls(t_data *ls, char **tab, int i, char *rep);
char				*path(char *dir, char *str);
char				**organize(char **tab, t_data *ls, int i, char *rep);

#endif

/*
TODO:

!- organiser le tableau des recurs
!- calculer le padding + calc total dans aff_ls_list
- norme au niveau des lignes
- flags gcc
- leaks

 */








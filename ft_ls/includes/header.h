/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:16:53 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/13 18:40:48 by sbelazou         ###   ########.fr       */
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

# define LOW(x) ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define UP(x) ((int32_t)((x) & 0xffffff))

typedef struct		s_lsize
{
	unsigned int	ttl;
	unsigned int	sze;
	unsigned int	grp;
	unsigned int	usr;
	unsigned int	lnk;
	unsigned int	low;
	unsigned int	upr;
}					t_lsize;

typedef struct		s_data
{
	DIR				*dir;
	struct dirent	*ent;
	struct stat		s;
	char			**reps;
	char			*args;
	char			**recs;
	t_lsize			*ttx;
}					t_data;

void				ft_ls(t_data *ls, int i);
char				**sortime(char **tab, t_data *ls, int size, char *rep);
char				**revtime(char **tab, t_data *ls, int size, char *rep);
void				aff_ls_list(char **tab, t_data *ls, char *rep);
void				ft_optreps(t_data *ls, char **tab, int j);
void				aff_ls(t_data *ls, char **tab, int i, char *rep);
char				*path(char *dir, char *str);
char				**organize(char **tab, t_data *ls, int i, char *rep);
char				**aff_ls_rec(t_data *ls, char **tab, int i, char *rep);
char				**aff_ls_list_rec(char **tab, t_data *ls, char *rep);
char				**add_repository(char *to_add, char *dir, t_data *ls);
t_data				*get_ttx(char **tab, char *rep, t_data *ls);
void				aff_stat(t_data *ls);
t_data				*ft_stat(char *rep, char *str, t_data *ls);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsl_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:42:42 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/12 17:56:35 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void			aff_perm(mode_t m)
{
	if (S_ISDIR(m))
		ft_putchar('d');
	else if (S_ISLNK(m))
		ft_putchar('l');
	else if (S_ISBLK(m))
		ft_putchar('b');
	else if (S_ISFIFO(m))
		ft_putchar('p');
	else if (S_ISCHR(m))
		ft_putchar('c');
	else if (S_ISSOCK(m))
		ft_putchar('s');
	else
		ft_putchar('-');
	ft_putchar((m & S_IRUSR) ? 'r' : '-');
	ft_putchar((m & S_IWUSR) ? 'w' : '-');
	ft_putchar((m & S_IXUSR) ? 'x' : '-');
	ft_putchar((m & S_IRGRP) ? 'r' : '-');
	ft_putchar((m & S_IWGRP) ? 'w' : '-');
	ft_putchar((m & S_IXGRP) ? 'x' : '-');
	ft_putchar((m & S_IROTH) ? 'r' : '-');
	ft_putchar((m & S_IWOTH) ? 'w' : '-');
	ft_putchar((m & S_IXOTH) ? 'x' : '-');
}

static void			data_padd(char *d)
{
	char			str[25];
	int				i;
	int				j;

	i = 0;
	j = 4;
	d[16] = 0;
	while (d[j])
		str[i++] = d[j++];
	str[i] = 0;
	ft_putstr(str);
}

static void			affgiduid(uid_t uid, gid_t gid)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(uid);
	grp = getgrgid(gid);
	ft_putstr(pwd->pw_name);
	ft_putstr(" ");
	ft_putstr(grp->gr_name);
}

static void			aff_stat(t_data *ls)
{
	aff_perm(ls->s.st_mode);
	ft_putstr("  ");
	ft_putnbr(ls->s.st_nlink);
	ft_putstr(" ");
	affgiduid(ls->s.st_uid, ls->s.st_gid);
	ft_putstr("  ");
	ft_putnbr(ls->s.st_size);
	ft_putstr("  ");
	data_padd(ctime(&(ls->s.st_mtime)));
	ft_putstr(" ");
}

char				**aff_ls_list_rec(char **tab, t_data *ls, char *rep)
{
	int				i;
	char				*way;
	
	i = 0;
	ft_putstr("total ");
	ft_putnbr(0);
	ft_putchar('\n');//Calculer le total + checker le padding
	while (tab[i])
	{
		way = path(rep, tab[i]);
		stat(way, &(ls->s));
		free(way);
		aff_stat(ls);
		if (ft_strchr(ls->args, 'R') && S_ISDIR(ls->s.st_mode)
			&& (ft_strcmp(".", tab[i]) && ft_strcmp("..", tab[i])))
			ls->recs = add_repository(tab[i], rep, ls);
		ft_putendl(tab[i++]);
	}
	return (ls->recs);
}

void				aff_ls_list(char **tab, t_data *ls, char *rep)
{
	int				i;

	i = 0;
	ft_putendl("total ");
	//Calculer le total + checker le padding
	while (tab[i])
	{
		stat(path(rep, tab[i]), &(ls->s));
		aff_stat(ls);
		ft_putendl(tab[i++]);
	}
}

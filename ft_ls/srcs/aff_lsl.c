/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:16 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/13 19:07:13 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void			affgiduid(uid_t uid, gid_t gid)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(uid);
	grp = getgrgid(gid);
	ft_putstr(pwd->pw_name);
	ft_putstr("  ");
	ft_putstr(grp->gr_name);
	ft_putchar(' ');
}

static void			write_space(int max, int nb)
{
	if (nb != 0)
		nb = (int)ft_intlen(nb);
	ft_putchar(' ');
	while (nb != max)
	{
		ft_putchar(' ');
		nb++;
	}
}

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
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 4;
	d[16] = 0;
	while (d[j])
		str[i++] = d[j++];
	str[i] = 0;
	ft_putstr(str);
}

void				aff_stat(t_data *ls)
{
	aff_perm(ls->s.st_mode);
	write_space(ls->ttx->lnk, ls->s.st_nlink);
	ft_putnbr(ls->s.st_nlink);
	write_space(1, 0);
	affgiduid(ls->s.st_uid, ls->s.st_gid);
	write_space(ls->ttx->sze, ls->s.st_size);
	ft_putnbr(ls->s.st_size);
	write_space(0, 0);
	data_padd(ctime(&(ls->s.st_mtime)));
	write_space(0, 0);
}

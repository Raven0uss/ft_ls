/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:16 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/22 16:28:34 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void					write_space(int max, int nb, char *str)
{
	if (str == NULL)
	{
		if (nb != 0)
			nb = (int)ft_intlen(nb);
		if (nb != 0)
			ft_putchar(' ');
		while (nb != max)
		{
			ft_putchar(' ');
			nb++;
		}
	}
	else
	{
		nb = ft_strlen(str);
		ft_putchar(' ');
		while (nb != max)
		{
			ft_putchar(' ');
			nb++;
		}
	}
}

static void					affgiduid(uid_t uid, gid_t gid, t_data *ls)
{
	static struct passwd	*pwd;
	static struct group		*grp;

	pwd = getpwuid(uid);
	grp = getgrgid(gid);
	ft_putstr(pwd->pw_name);
	write_space(ls->ttx->usr + 1, 0, pwd->pw_name);
	ft_putstr(grp->gr_name);
	write_space(ls->ttx->grp, 0, grp->gr_name);
}

static void					aff_perm(mode_t m)
{
	if (S_ISLNK(m))
		ft_putchar('l');
	else if (S_ISDIR(m))
		ft_putchar('d');
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

static void					data_padd(char *d)
{
	char					str[25];
	unsigned int			i;
	unsigned int			j;

	i = 0;
	j = 4;
	d[16] = 0;
	while (d[j])
		str[i++] = d[j++];
	str[i] = 0;
	ft_putstr(str);
}

void						aff_stat(t_data *ls)
{
	ls->ttx->sze = ls->ttx->upr + ls->ttx->low + 3 > ls->ttx->sze ?
		ls->ttx->upr + ls->ttx->low + 3 : ls->ttx->sze;
	aff_perm(ls->s.st_mode);
	ft_putchar(' ');
	write_space(ls->ttx->lnk, ls->s.st_nlink, NULL);
	ft_putnbr(ls->s.st_nlink);
	ft_putchar(' ');
	affgiduid(ls->s.st_uid, ls->s.st_gid, ls);
	if (S_ISCHR(ls->s.st_mode) || S_ISBLK(ls->s.st_mode))
	{
		write_space(ls->ttx->low + 1, LOW(ls->s.st_rdev), NULL);
		ft_putnbr(LOW(ls->s.st_rdev));
		ft_putchar(',');
		write_space(ls->ttx->upr, UP(ls->s.st_rdev), NULL);
		ft_putnbr(UP(ls->s.st_rdev));
	}
	else
	{
		write_space(ls->ttx->sze, ls->s.st_size, NULL);
		ft_putnbr(ls->s.st_size);
	}
	write_space(1, 0, NULL);
	data_padd(ctime(&(ls->s.st_mtime)));
	write_space(1, 0, NULL);
}

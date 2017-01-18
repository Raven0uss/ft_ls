/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 15:33:33 by sbelazou          #+#    #+#             */
/*   Updated: 2017/01/11 16:13:03 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void aff_perm(mode_t m)
{
  if (S_ISDIR(m))
    ft_putchar('d');
  else if (S_ISLNK(m))
    ft_putchar('l');
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

static void data_padd(char *d)
{
	char	str[25];
	int		i;
	int		j;

	i = 0;
	j = 4;
	d[16] = 0;
	while (d[j])
		str[i++] = d[j++];
	str[i] = 0;
	ft_putstr(str);
}

static void	affgiduid(uid_t uid, gid_t gid)
{
  struct passwd	*pwd;
  struct group	*grp;

  pwd = getpwuid(uid);
  grp = getgrgid(gid);
  ft_putstr(pwd->pw_name);
  ft_putstr(" ");
  ft_putstr(grp->gr_name);
}

static void	aff_stat(t_ls *dc)
{
	aff_perm(dc->file->s.st_mode);
	ft_putstr(" ");
	ft_putnbr(dc->file->s.st_nlink);
	ft_putstr(" ");
	affgiduid(dc->file->s.st_uid, dc->file->s.st_gid);
	ft_putstr(" ");
	ft_putnbr(dc->file->s.st_size);
	ft_putstr(" ");
	data_padd(ctime(&dc->file->s.st_mtime));
	ft_putstr(" ");
}

static char **ft_revtime(t_ls *dc, int size, char *rep)
{
	int		i;
	char	*tmp;
	int		timod;

	i = 0;
	timod = 0;
	dc->file->tab = ft_rev_tab(dc->file->tab, size);
	stat(dc->file->tab[i], &(dc->file->s));
	while (i < size)
	{
		timod = dc->file->s.st_mtime;
		stat(path(rep, dc->file->tab[i + 1]), &(dc->file->s));
		if (timod > dc->file->s.st_mtime)
		{
			tmp = dc->file->tab[i];
			dc->file->tab[i] = dc->file->tab[i + 1];
			dc->file->tab[i + 1] = tmp;
			i = 0;
			stat(path(rep, dc->file->tab[i]), &(dc->file->s));
		}
		else
			i++;
	}
	return (dc->file->tab);
}

//  BUG NIVEAU DU TEMPS. LE CHEMIN SPECIFIE EST SUREMENT INCOMPLET POUR UN REPO AUTRE QUE LE REPO COURANT

static char **ft_sortime(t_ls *dc, int size, char *rep)
{
	int		i;
	char	*tmp;
	int	timod;

	i = 0;
	timod = 0;
	dc->file->tab = ft_sort_tab(dc->file->tab, size);
	stat(path(rep, dc->file->tab[i]), &(dc->file->s));
	while (i < size)
	{
		timod = dc->file->s.st_mtime;
		stat(path(rep, dc->file->tab[i + 1]), &(dc->file->s));
		if (timod < dc->file->s.st_mtime)
		{
			tmp = dc->file->tab[i];
			dc->file->tab[i] = dc->file->tab[i + 1];
			dc->file->tab[i + 1] = tmp;
			i = 0;
			stat(path(rep, dc->file->tab[i]), &(dc->file->s));
		}
		else
			i++;
	}
	return (dc->file->tab);
}

char	*path(char *rep, char *name)
{
  int	i;
  int	j;
  char	*new;

  i = 0;
  j = 0;
  if (rep == NULL)
    return (name);
  if ((new = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(rep)))) == NULL)
    return (NULL);
  while (rep[i])
    new[i] = rep[i++];
  j = i;
  i = 0;
  if (new[j - 1] != '/')
    new[j++] = '/';
  while (name[i])
    new[j++] = name[i++];
  new[j] = 0;
  return (new);
}

static int	size_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

static char	**add_to_tab(char **tab, int i, char *str)
{
  char		**tmp;
  int		j;

  j = 0;
  if ((tmp = malloc(sizeof(char *) * size_tab(tab) + 2)) == NULL)
    return (NULL);
  while (j != i)
    tmp[j] = ft_strdup(tab[j++]);
  tmp[j++] = ft_strdup(str);
  while (tab[i])
    tmp[j] = ft_strdup(tab[i++]);
  tmp[j] = 0;
  return (tmp);
}

static char	**add_to_reps(t_ls *dc, char *str, char *rep)
{
  int	i;

  i = 0;
  if (dc->reps[0] == 0)
    dc->reps[0] = ft_strdup(str);
  else
    {
      while (dc->reps[i] && ft_strcmp(dc->reps[i], rep) != 0)
	i++;
      dc->reps = add_to_tab(dc->reps, i + 1, (ft_strcmp(rep, ".") != 0) ?
			    path(rep, str) : str);
    }
  return (dc->reps);
}

static char	**detect_directory(t_ls *dc, char *rep)
{
  int		i;

  i = 0;
  while (dc->file->tab[i])
    {
      stat(path(rep, dc->file->tab[i]), &dc->file->s);
      if (S_ISDIR(dc->file->s.st_mode))
	dc->reps = add_to_reps(dc, dc->file->tab[i], rep);
      i++;
    }
  return (dc->reps);
}

void	ft_ls(t_ls *dc, char *rep)
{
	int		i;
	char	*sep;

	i = 0;
	if (ft_strchr(dc->l_args, 'l'))
		sep = ft_strdup("\n");
	else
		sep = ft_strdup("  ");
	if ((dc->file = malloc(sizeof(t_file))) == NULL)
		return ;
	if ((dc->file->tab = malloc(sizeof(char *) * 1024)) == NULL)
		return ;
	while ((dc->file->ent = readdir(dc->dir)))
		if (dc->file->ent->d_name[0] != '.' || ft_strchr(dc->l_args, 'a'))
			dc->file->tab[i++] = ft_strdup(dc->file->ent->d_name);
	if (ft_strchr(dc->l_args, 't'))
	{
		if (ft_strchr(dc->l_args, 'r'))
		  dc->file->tab = ft_revtime(dc, i - 1, rep);
		else
		  dc->file->tab = ft_sortime(dc, i - 1, rep);
	}
	else
	{
		if (ft_strchr(dc->l_args, 'r'))
			dc->file->tab = ft_rev_tab(dc->file->tab, i - 1);
		else
			dc->file->tab = ft_sort_tab(dc->file->tab, i - 1);
	}
	if (ft_strchr(dc->l_args, 'R'))
	  dc->reps = detect_directory(dc, rep);
	if (ft_strchr(dc->l_args, 'l'))
	{
		ft_putstr("total ");
		ft_putnbr(i - 1);
		write(1, "\n", 1);
		i = 0;
		while (dc->file->tab[i])
		{
			stat(path(rep, dc->file->tab[i]), &(dc->file->s));
			aff_stat(dc);
			ft_putendl(dc->file->tab[i++]);
		}
	}
	else
	{
		ft_aff_tab(dc->file->tab, sep);
	}
}

static char	*crt_bname(char *name)
{
  char		*bin;

  if ((bin = ft_strdup(name)) == NULL)
    return (NULL);
  if ((bin = ft_strjoin(name, ": ")) == NULL)
    return (NULL);
  return (bin);
}

int		main(int ac, char **av)
{
  t_ls		*dir_content;

  if ((dir_content = malloc(sizeof(t_ls))) == NULL)
    return (-1);
  if ((dir_content->bin = crt_bname(av[0])) == NULL)
    return (-1);
  if ((dir_content->dir = opendir(".")) == NULL)
    perror(dir_content->bin);
  opt(dir_content, av, ac);
  free(dir_content->bin);
  free(dir_content);
  return (0);
}

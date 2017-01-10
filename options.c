/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:56:04 by sbelazou          #+#    #+#             */
/*   Updated: 2017/01/10 17:19:38 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*checker_av(char *str, char *args)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 1;
	j = 0;
	if (args != NULL)
		k = ft_strlen(args);
	while (str[i])
    {
		while (OPTS[j])
			if (str[i] == OPTS[j++])
			{
				args[k++] = str[i++];
				j = 0;
				break ;
			}
		if (j != 0)
			exit(1); //message error to fix
    }
	args[k] = 0;
	return (args);
}

static void	ft_ls_opt(t_ls *dc)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (dc->reps[0] == 0)
    {
		dc->dir = opendir(".");
		ft_ls(dc);
		closedir(dc->dir);
    }
	else
    {
		dc->reps = ft_sort_tab(dc->reps, ft_sizetab(dc->reps) - 1);
		closedir(dc->dir);
		if ((dc->file = malloc(sizeof(t_file))) == NULL)
			return ;
		if ((dc->file->tab = malloc(sizeof(char *) * 1024)) == NULL)
			return ;
		while (dc->reps[i])
		{

			if ((dc->dir = opendir(dc->reps[i])) == NULL)
			{
				ft_putstr(dc->bin);
				perror(dc->reps[i]);
			}
			else
			{
				j = 0;
				if (ft_sizetab(dc->reps) != 1)
				{
					ft_putstr(dc->reps[i]);
					ft_putendl(":");
				}
				ft_ls(dc);
				while ((dc->file->ent = readdir(dc->dir)))
					dc->file->tab[j++] = ft_strdup(dc->file->ent->d_name);
				dc->file->tab[j] = NULL;
				ft_aff_tab(ft_sort_tab(dc->file->tab, j - 1), "  ");
				closedir(dc->dir);
			}
			if (dc->reps[++i])
			  ft_putchar('\n');
		}
    }
}

void	opt(t_ls *dc, char **av, int ac)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if ((dc->reps = malloc(sizeof(char *) * ac)) == NULL)
		return ;
	dc->l_args = ft_memalloc(1024);
	while (av[i])
    {
		if (av[i][0] == '-' && av[i][1])
			dc->l_args = checker_av(av[i], dc->l_args);
		else
			dc->reps[k++] = ft_strdup(av[i]);
		i++;
    }
	dc->reps[k] = 0;
	if (dc->l_args[0])
	{
		dc->l_args = ft_onlyone(dc->l_args);
		ft_putendl(dc->l_args);
	}
	ft_ls_opt(dc);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 20:19:26 by sbelazou          #+#    #+#             */
/*   Updated: 2017/03/12 15:28:32 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char		*arg_error(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putendl("\nusage: ft_ls [-Ralrt] [file ...]");
	return (NULL);
}

static char		*arg_checker(char *str, char *args)
{
	int			i;
	int			j;
	int			k;

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
			return (arg_error(str[i]));
	}
	args[k] = 0;
	return (args);
}

static t_data	*params_loader(t_data *ls, char **av)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	if (!(ls->reps = malloc(sizeof(char *) * 10240)))// Allocation non precise
		return (NULL);
	if (!(ls->args = ft_memalloc(1024)))// Allocation non precise
		return (NULL);
	if (!(ls->recs = malloc(sizeof(char *) * 10240)))
		return (NULL);
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1])
		{
			if (!(ls->args = arg_checker(av[i], ls->args)))
				return (NULL);
		}
		else
			ls->reps[j++] = ft_strdup(av[i]);
		i++;
	}
	ls->reps[j] = 0;
	if (ls->args[0])
		ls->args = ft_onlyone(ls->args);
	return (ls);
}

int				main(int ac, char **av)
{
	t_data		*ls;

	if (!(ls = malloc(sizeof(t_data))))
		return (-1);
	if (ac > 1)
	{
		if (!(ls = params_loader(ls, av)))
			return (-1);
	}
	else
		ls = NULL;
	ft_ls(ls);
	free(ls);
	return (0);
}

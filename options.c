/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:56:04 by sbelazou          #+#    #+#             */
/*   Updated: 2016/12/20 21:08:57 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	checker_av(char *str)
{
	int		i;

	i = 0;
	while (i != OPT_NB)
		if (ft_strcmp(str, OPTS[i++]) == 0)
			return (1);
	return (0);
}

void	opt(t_ls *dc, char **av)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	k = 0;
	while (av[i])
    {
		if (checker_av(av[i]))
			dc->l_args[j++] = av[i][1];
		else
			dc->reps[k++] = ft_strdup(av[i]);
		i++;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:31:06 by sbelazou          #+#    #+#             */
/*   Updated: 2016/11/09 19:25:26 by sbelazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f) (char))
{
	int		i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	if ((new = malloc(sizeof(char) * ft_strlen(s) + 1)) == NULL)
		return (NULL);
	while (s[i])
	{
		new[i] = f(s[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}

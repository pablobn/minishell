/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:39:05 by pbengoec          #+#    #+#             */
/*   Updated: 2022/09/30 15:53:48 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*a;
	char	*b;
	size_t	i;
	size_t	j;

	a = (char *) haystack;
	b = (char *) needle;
	i = 0;
	if (ft_strlen(needle) == 0)
		return (a);
	while (a[i] && i < len)
	{
		j = 0;
		while (b[j] == a[i + j] && i + j < len)
		{
			if (b[j + 1] == '\0')
				return (&a[i]);
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:49:47 by pbengoec          #+#    #+#             */
/*   Updated: 2022/09/29 18:32:44 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*a;
	size_t	i;

	a = (char *) s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char) a[i] == (unsigned char) c)
			return (&a[i]);
		i++;
	}
	return (0);
}

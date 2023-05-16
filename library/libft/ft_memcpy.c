/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:12:12 by pbengoec          #+#    #+#             */
/*   Updated: 2022/09/26 19:29:50 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*a;
	char	*b;

	a = (char *) src;
	b = dst;
	i = 0;
	if (!a && !b)
		return (dst);
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dst);
}

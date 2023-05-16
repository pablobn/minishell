/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:26:20 by pbengoec          #+#    #+#             */
/*   Updated: 2022/09/30 16:47:16 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*a;

	a = (char *) src;
	i = 0;
	if (dstsize <= 0)
		return (ft_strlen(src));
	while (a[i] && i < dstsize - 1)
	{
		dst[i] = a[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

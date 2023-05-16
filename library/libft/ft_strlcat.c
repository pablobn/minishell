/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:28:15 by pbengoec          #+#    #+#             */
/*   Updated: 2023/04/27 19:50:27 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;
	char	*a;

	a = (char *) src;
	size = ft_strlen(dst);
	i = 0;
	if (dstsize <= size)
		return (ft_strlen(src) + dstsize);
	while (src[i] && (size + i) < dstsize - 1)
	{
		dst[size + i] = src[i];
		i++;
	}
	dst[size + i] = '\0';
	return (size + ft_strlen(src));
}

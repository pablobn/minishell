/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:34:04 by pbengoec          #+#    #+#             */
/*   Updated: 2022/10/01 19:47:42 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	newlen;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set,*s1))
		s1++;
	newlen = ft_strlen(s1);
	while (newlen > 0 && ft_strchr(set, s1[newlen]))
		newlen--;
	new = ft_substr(s1, 0, newlen + 1);
	return (new);
}

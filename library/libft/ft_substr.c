/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:11:19 by pbengoec          #+#    #+#             */
/*   Updated: 2022/10/01 16:47:18 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;
	size_t	memory;

	strlen = ft_strlen(s);
	memory = strlen + 1 - start;
	if (start > strlen || strlen == 0)
		return (ft_strdup(""));
	if (len + start < strlen + 1)
		memory = len + 1;
	else if (len == strlen + 1)
		memory = len;
	substr = ft_calloc(memory, sizeof(char));
	if (substr == 0)
		return (0);
	ft_strlcpy(substr, &s[start], memory);
	return (substr);
}

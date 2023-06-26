/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:33:13 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/26 15:14:16 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{	
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *) &*s);
		s++;
	}
	if ((char)c == *s)
		return ((char *) &*s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *str, char *buf)
{
	char	*new;
	int		i;
	int		j;

	if (str == NULL)
	{
		str = (char *) malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (buf == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen_gnl(str) + ft_strlen_gnl(buf) + 1));
	if (new == NULL)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
		new[j++] = str[i++];
	i = 0;
	while (buf[i])
		new[j++] = buf[i++];
	new[j] = '\0';
	return (free(str), new);
}

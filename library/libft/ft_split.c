/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:38:36 by pbengoec          #+#    #+#             */
/*   Updated: 2022/10/03 21:09:50 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	words;
	size_t	j;

	words = 0;
	j = 0;
	while (s[j])
	{
		if (j == 0 && s[j] != c)
			words++;
		else if (s[j] != c && s[j - 1] == c)
			words++;
		j++;
	}
	return (words);
}

static char	**ft_splitfree(char **split, size_t cont)
{
	while (cont--)
		free(split[cont]);
	free(split);
	return (NULL);
}

static char	**ft_splitpriv(char const *s, char c, size_t	i, char **split)
{
	size_t	start;
	size_t	cont;

	cont = 0;
	start = 0;
	while (s[i])
	{
		if (i == 0 && s[i] == c)
			start++;
		else if ((s[i] == c && s[i - 1] != c)
			|| (s[i] != c && s[i + 1] == '\0'))
		{	
			if (s[i] != c && s[i + 1] == '\0')
				split[cont++] = ft_substr(s, start, i - start + 1);
			else
				split[cont++] = ft_substr(s, start, i - start);
			if (split[cont - 1] == NULL)
				return (ft_splitfree(split, cont));
			start = i + 1;
		}
		else if (s[i] == c)
			start++;
		i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	size;

	size = ft_countwords(s, c);
	split = ft_calloc(size + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	split = ft_splitpriv(s, c, 0, split);
	return (split);
}

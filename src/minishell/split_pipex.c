/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:15 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 15:26:34 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 1;
	if (s[i] != c)
		words++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			words++;
		i++;
	}
	return (words);
}

static int	next_del(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
			while (s[++i + 1] && (s[i] != '"'))
				;
		else if (s[i] == '\'')
			while (s[++i + 1] && (s[i] != '\''))
				;
		i++;
	}
	return (i);
}

static char	**ft_split_words(char **arr, const char *s, const char c)
{
	int	i;
	int	del_pos;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			del_pos = next_del(s, c);
			if (!del_pos)
				break ;
			arr[i] = ft_calloc(del_pos + 1, sizeof(char));
			if (!arr[i])
				return (NULL);
			ft_memcpy(arr[i], s, del_pos);
			s += del_pos;
			i++;
		}
	}
	return (arr);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**arr;
	int		count;

	count = ft_count_words(s, c);
	arr = ft_calloc(count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft_split_words(arr, s, c));
}

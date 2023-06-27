/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:29:16 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 15:32:51 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_normi_quotes(int j, t_command *list)
{
	char	*temp;

	while (list->line[j] && list->line[j] != '\'')
	{
		if ((list->line[j] == '$' || list->line[j] == ' ')
			&& list->line[j - 1] != '\\')
		{
			temp = ft_substr(list->line, 0, j);
			temp = ft_strjoin_free(temp, "\\");
			temp = ft_strjoin_free(temp, &list->line[j]);
			free(list->line);
			list->line = temp;
			j += 2;
		}
		else
			j++;
	}
	return (j);
}

static int	ft_normi_quotes_doble(int j, t_command *list)
{
	char	*temp;

	while (list->line[j] && list->line[j] != '\"')
	{
		if (list->line[j] == '$')
		{
			while (list->line[j] && list->line[j] != ' '
				&& list->line[j] != '\"')
				j++;
		}
		else
		{
			if (list->line[j] && j - 1 >= 0 && list->line[j - 1] != '\\')
			{
				temp = ft_substr(list->line, 0, j);
				temp = ft_strjoin_free(temp, "\\");
				temp = ft_strjoin_free(temp, &list->line[j]);
				free(list->line);
				list->line = temp;
				j += 2;
			}
			else
				j++;
		}
	}
	return (j);
}

static void	ft_delete_quotes(int j, t_command *list)
{
	char	*temp;

	if (list->line[j + 1])
	{
		temp = ft_substr(list->line, 0, j);
		temp = ft_strjoin_free(temp, "");
		temp = ft_strjoin_free(temp, &list->line[j + 1]);
		free(list->line);
		list->line = temp;
	}
	else
		list->line[ft_strlen(list->line) - 1] = 0;
}

static int	ft_normi_quotes_doble2(int j, t_command *list)
{
	char	*temp;

	if (list->line[j] == '\"')
	{
		if (list->line[j + 1])
		{
			temp = ft_substr(list->line, 0, j);
			temp = ft_strjoin_free(temp, &list->line[j + 1]);
			free(list->line);
			list->line = temp;
			j = ft_normi_quotes_doble(j, list);
		}
		else
			list->line[ft_strlen(list->line) - 1] = 0;
	}
	if (list->line[j] == '\"')
		ft_delete_quotes(j, list);
	if (list->line[j] != '\'')
		j++;
	return (j);
}

t_command	*ft_quotes(t_command *list)
{
	int		j;

	j = 0;
	if (!list->line)
		return (NULL);
	while (list->line[j])
	{
		if (list->line[j] == '\'')
		{
			ft_delete_quotes(j, list);
			j = ft_normi_quotes(j, list);
			if (list->line[j] == '\'')
				ft_delete_quotes(j, list);
		}
		j = ft_normi_quotes_doble2(j, list);
	}
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:28:19 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 16:03:12 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_normi(t_command *list, t_ms *ms, int i)
{
	if (list->flags[0][ft_strlen(list->flags[0]) - 1] == '\\')
		list->flags[0][ft_strlen(list->flags[0]) - 1] = '\0';
	if (list->flags[0] && list->line[i - 1] != '\\')
	{
		list->flags[1] = ft_get_env_key(ms->env, &list->flags[0][1]);
		free(list->flags[0]);
	}
	else
		list->flags[1] = list->flags[0];
	if (list->flags[1])
	{
		list->flags[2] = ft_strjoin_free(list->flags[2], list->flags[1]);
		free(list->flags[1]);
	}
}

static void	ft_normi_2(t_command *list, t_ms *ms, int i)
{
	if (list->flags[0][1] == '?' && !list->flags[0][2])
	{
		free(list->flags[0]);
		list->flags[0] = ft_itoa(ms->status);
		list->flags[2] = ft_strjoin_free(list->flags[2], list->flags[0]);
		free(list->flags[0]);
	}
	else if (list->flags[0][0] == '$' && (!list->flags[0][1]
		|| !ft_isalnum(list->flags[0][1])))
	{
		list->flags[2] = ft_strjoin_free(list->flags[2], list->flags[0]);
		free(list->flags[0]);
	}
	else if (list->flags[0][1] != '$' && list->flags[0][1])
		ft_normi(list, ms, i);
	else
		list->flags[1] = list->flags[0];
}

t_command	*ft_expand(t_command *list, t_ms *ms, int i, int j)
{
	if (!ms->env || !list->line || !list->line[i])
		return (list);
	while (list->line[i] && list->line[i] != '$')
		i++;
	if ((i - 1 >= 0 && list->line[i - 1] == '\\')
		|| (int)ft_strlen(list->line) == i)
		return (list);
	list->flags = ft_calloc(3, sizeof(char *));
	list->flags[2] = ft_substr(list->line, 0, i);
	while (list->line[i + j] && list->line[i + j] != ' '
		&& list->line[i + j] != '\'' && list->line[i + j] != '\"')
		if (list->line[i + ++j] == '$' || list->line[i + j] == '|')
			break ;
	list->flags[0] = ft_substr(list->line, i, j);
	ft_normi_2(list, ms, i);
	list->flags[2] = ft_strjoin_free(list->flags[2], &list->line[i + j]);
	free(list->line);
	list->line = list->flags[2];
	free(list->flags);
	ft_expand(list, ms, i + j + 1, 0);
	return (list);
}

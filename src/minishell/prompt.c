/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:29:09 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 12:54:46 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	**ft_split_line(t_command **list, char *line)
{
	int		i;
	char	**line_split;

	line_split = ft_split_pipex(line, '|');
	if (!line_split)
		return (NULL);
	i = -1;
	while (line_split[++i])
		;
	list = ft_calloc(i + 1, sizeof(t_command *));
	i = -1;
	while (line_split[++i])
		list[i] = ft_calloc(1, sizeof(t_command));
	i = -1;
	while (line_split[++i])
	{
		list[i]->line = ft_strdup(line_split[i]);
		if (i + 1 <= -1)
			list[i]->next = NULL;
		else
			list[i]->next = list[i + 1];
	}
	return (ft_free_matrix(line_split), list);
}

static t_command	*ft_tilde(t_command *list, t_env *env)
{
	int		i;
	char	*temp;
	char	*home;

	i = 0;
	if (!env || !list->line)
		return (list);
	home = ft_get_env_key(env, "HOME");
	while (list->line[i] && home)
	{
		if (list->line[i] == '~')
		{
			if (i - 1 >= 0 && (list->line[i - 1] == '\\'
					|| list->line[i - 1] != ' '))
				break ;
			if (list->line[i + 1] && list->line[i + 1] != ' ')
				break ;
			temp = ft_strjoin(ft_substr(list->line, 0, i), home);
			temp = ft_strjoin_free(temp, &list->line[i + 1]);
			free(list->line);
			list->line = temp;
		}
		i++;
	}
	return (free(home), list);
}

void	ft_prompt(t_ms *ms)
{
	int		i;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	rl_replace_line("", 0);
	if (ms->line)
		free(ms->line);
	ms->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!ms->line)
		return ;
	if (!ft_is_empty(ms->line))
		add_history(ms->line);
	ms->list = ft_split_line(ms->list, ms->line);
	if (!ms->list)
		return ;
	i = 0;
	while (ms->list[i])
	{
		ms->list[i] = ft_quotes(ms->list[i]);
		ms->list[i] = ft_expand(ms->list[i], ms, 0, 0);
		ms->list[i] = ft_tilde(ms->list[i], ms->env);
		i++;
	}
	return ;
}

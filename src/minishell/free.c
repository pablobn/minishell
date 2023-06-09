/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:15 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/26 19:47:17 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	return (NULL);
}

void	ft_free_ms(t_ms *g_ms)
{
	free_env(g_ms->env);
	free_env(g_ms->exp);
	if (g_ms->line)
		free(g_ms->line);
	free(g_ms);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(matrix);
	}
}

void	ft_free_list(t_command	**list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list[i])
		{
			if (list[i]->heredoc)
			{
				unlink(".here_doc");
				free(list[i]->heredoc);
			}
			ft_free_matrix(list[i]->flags);
			free(list[i]->cmd);
			free(list[i]->line);
			if (list[i]->in != 0)
				close(list[i]->in);
			if (list[i]->out != 0)
				close(list[i]->out);
			free(list[i]);
			i++;
		}
		free(list);
	}
}

char	*ft_strjoin_free(char *str, char *buf)
{
	char	*new;
	int		i;
	int		j;

	if (str == NULL)
		return (NULL);
	if (buf == NULL)
		return (free(str), NULL);
	new = (char *) malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(buf) + 1));
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

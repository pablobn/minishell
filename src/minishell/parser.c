/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:29:02 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 10:29:03 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_infile_file(t_command *cmd, char *aux)
{
	if (cmd->in)
		close(cmd->in);
	if (cmd->in_f != 0 && !ft_is_empty(aux))
		cmd->heredoc = ft_strdup(aux);
	else
		cmd->in = open(aux, O_RDONLY);
}

static int	ft_infile(t_command *cmd, int i)
{
	int		j;
	char	aux[255];

	j = -1;
	if (!cmd->line[i] || cmd->line[i] != '<')
		return (i);
	i++;
	if (cmd->line[i] == '<')
		cmd->in_f = i++;
	else
		cmd->in_f = 0;
	i = ft_space_iter(cmd->line, i);
	if (cmd->line[i] == '<' || cmd->line[i] == '>')
		return (i);
	while (cmd->line[i] && cmd->line[i] != ' ')
	{
		if (cmd->line[i + 1] && cmd->line[i] == '\\')
			i++;
		aux[++j] = cmd->line[i];
		i++;
	}
	aux[++j] = 0;
	ft_infile_file(cmd, aux);
	return (i);
}

static void	ft_outfile_file(t_command *cmd, char *aux)
{
	if (cmd->out)
		close(cmd->out);
	if (!cmd->out_f)
		cmd->out = open(aux, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	else
		cmd->out = open(aux, O_APPEND | O_CREAT | O_WRONLY, 0777);
}

static int	ft_outfile(t_command *cmd, int i)
{
	int		j;
	char	aux[255];

	j = -1;
	if (!cmd->line[i])
		return (i);
	if (cmd->line[i] != '>')
		return (i);
	if (cmd->line[++i] == '>')
		cmd->out_f = ++i;
	else
		cmd->out_f = 0;
	i = ft_space_iter(cmd->line, i);
	if (cmd->line[i] == '<')
		return (i);
	while (cmd->line[i] && cmd->line[i] != ' ')
	{
		if (cmd->line[i + 1] && cmd->line[i] == '\\')
			i++;
		aux[++j] = cmd->line[i];
		i++;
	}
	aux[++j] = 0;
	ft_outfile_file(cmd, aux);
	return (i);
}

void	ft_parser(t_command *list)
{
	int		i;

	i = ft_space_iter(list->line, 0);
	while (list->line && list->line[i])
	{
		i = ft_outfile(list, i);
		i = ft_space_iter(list->line, i);
		i = ft_infile(list, i);
		i = ft_space_iter(list->line, i);
		i = ft_command(list, i);
		i = ft_space_iter(list->line, i);
	}
	if (list->cmd)
		list->flags = ft_split_pipex(list->cmd, ' ');
	else
		list->flags = ft_calloc(sizeof(char *), 1);
	if (list->flags && list->flags[0]
		&& ft_space_iter(list->flags[0], 0) == (int)ft_strlen(list->flags[0]))
		list->flags[0] = NULL;
	return ;
}

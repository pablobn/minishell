/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:05:45 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/27 15:12:35 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_exit(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(255);
}

static void	ft_open_heredoc(t_command *list)
{
	if (!list->in)
	{
		list->in = open(".here_doc", O_RDONLY);
		if (list->in < 0)
		{
			unlink(".here_doc");
			ft_error_exit("Error abriendo archivo here_doc");
		}
	}
}

static int	ft_exit_heredoc(char *str)
{
	if (!str)
	{
		rl_replace_line("                      ", 0);
		printf("\n");
		return (1);
	}
	return (0);
}

static void	ft_create_heredoc(t_command *list)
{
	int		file;
	char	*str;
	size_t	size;

	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file < 0)
		ft_error_exit("Error creando archivo here_doc");
	while (1)
	{
		size = ft_strlen(list->heredoc);
		ft_putstr_fd("heredoc> ", 1);
		str = get_next_line(0);
		if (ft_exit_heredoc(str))
			break ;
		if (ft_strlen(str) - 1 > size)
			size = ft_strlen(str) - 1;
		if (ft_strncmp(str, list->heredoc, size) == 0)
			break ;
		write(file, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(file);
	ft_open_heredoc(list);
}

void	ft_get_here_doc(t_command *list)
{
	while (list)
	{
		if (list->heredoc)
			ft_create_heredoc((list));
		list = list->next;
	}
}

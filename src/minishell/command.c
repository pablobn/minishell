/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:28:06 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 10:28:07 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_command(t_command *list, int i)
{
	int		j;
	char	*temp;

	j = 0;
	while (list->line[i + j] && list->line[i + j] != ' ')
		j++;
	temp = ft_calloc(sizeof(char *), j + 255);
	if (!temp)
		return (i);
	j = 0;
	while (list->line[i] && list->line[i] != ' '
		&& list->line[i] != '<' && list->line[i] != '>')
	{
		if (list->line[i + 1] && list->line[i] == '\\')
			i++;
		temp[j++] = list->line[i++];
	}
	if (list->cmd)
	{
		list->cmd = ft_strjoin_free(list->cmd, temp);
		free(temp);
	}
	else
		list->cmd = temp;
	return (list->cmd = ft_strjoin_free(list->cmd, " \0"), i);
}

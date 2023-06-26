/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:46:54 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/26 19:46:56 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_list(t_command *list)
{
	int	i;

	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}	
	return (i);
}

int	ft_size_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

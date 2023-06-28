/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:28:27 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/28 12:04:16 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms	*g_ms;

void	ft_handler(int sig)
{
	if (g_ms->pid != 0 && g_ms->pid != -1)
	{
		printf("\n");
		kill(g_ms->pid, SIGKILL);
		g_ms->status = 130;
		g_ms->pid = 0;
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

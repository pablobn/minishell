/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:28:53 by sdiaz-ru          #+#    #+#             */
/*   Updated: 2023/06/27 16:48:15 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*g_ms;

static void	ft_exit()
{
	int	i;

	i = -1;
	while (g_ms->list[++i] && g_ms->list[i]->flags)
	{
		if (!ft_strncmp(g_ms->list[i]->flags[0], "exit", 4))
		{
			if (g_ms->list[i]->flags[1])
			{	
				g_ms->status = ft_atoi(g_ms->list[i]->flags[1]);
				ft_free_list(g_ms->list);
				rl_clear_history();
				free_env(g_ms->env);
				free_env(g_ms->exp);
				if (g_ms->line)
					free(g_ms->line);
				exit(g_ms->status);
			}
			ft_free_list(g_ms->list);
			ft_free_ms(g_ms);
			rl_clear_history();
			exit(255);
		}
	}
}
//atexit(ft_leaks);

int	main(int argc, char **argv, char **envp)
{
	g_ms = ft_calloc(1, sizeof(t_ms));
	ft_init_env(g_ms, envp);
	while (42)
	{
		ft_prompt(g_ms);
		if (!g_ms->line)
			break ;
		argc = -1;
		while (g_ms->list && g_ms->list[++argc])
			ft_parser(g_ms->list[argc]);
		ft_exit();
		if (g_ms->list[0])
			ft_execute_line(g_ms);
		ft_free_list(g_ms->list);
		g_ms->pid = 0;
	}
	return (ft_free_ms(g_ms), rl_clear_history(), (void)argv, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:45:28 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/27 15:15:15 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_cmd(char *str, char *path)
{
	char		**cases;
	char		*new;
	char		*tmp;
	int			i;

	if (!str)
		return (NULL);
	if (access(str, X_OK) == 0)
		return (ft_strdup(str));
	cases = ft_split(path, ':');
	i = 0;
	new = ft_strjoin("/", str);
	while (cases[i])
	{
		tmp = ft_strjoin(cases[i], new);
		if (access(tmp, X_OK) == 0)
			return (free(new), tmp);
		free(tmp);
		i++;
	}
	perror(str);
	return (free(new), ft_free_matrix(cases), NULL);
}

void	ft_execute_command(t_command *list, t_env *env)
{
	char	*path;
	char	*cmd_path;

	path = ft_get_env_key(env, "PATH");
	if (!path)
	{
		ft_putstr_fd("No existe PATH\n", 2);
		exit (127);
	}
	cmd_path = ft_get_cmd(list->flags[0], path);
	if (!cmd_path)
	{
		free(path);
		exit (127);
	}
	free(path);
	if (execve(cmd_path, list->flags, ft_get_envp(env)) == -1)
	{
		perror(cmd_path);
		exit(-1);
	}
}

int	ft_execute_line(t_ms *ms)
{
	t_command	*list;

	list = ms->list[0];
	ft_get_here_doc(list);
	if (!list->next)
	{
		ft_built_in_cd(list, ms);
		if (ft_check_built_in_cd(list))
			list = list->next;
		else
			return (ft_start_pipex(list, ms));
	}
	else
		return (ft_start_pipex(list, ms));
	return (0);
}

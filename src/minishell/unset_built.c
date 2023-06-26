#include "minishell.h"

int	ft_search_env(t_env *env, char *str)
{
	if (ft_strncmp(env->key, str, ft_strlen(env->key)) == 0)
		return (1);
	return (0);
}

void	ft_remove_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	if (ft_search_env(tmp, str))
	{
		*env = tmp->next;
		return ;
	}
	while (tmp && !ft_search_env(tmp, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	free(tmp);
}

int	ft_unset(t_ms *ms, char *str)
{
	ft_remove_env(&ms->env, str);
	ft_remove_env(&ms->exp, str);
	return (0);
}

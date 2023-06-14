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

char	*ft_strjoin_free(char *str, char *buf)
{
	char	*new;
	int		i;
	int		j;

	if (str == NULL)
	{
		str = (char *) malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (buf == NULL)
		return (NULL);
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
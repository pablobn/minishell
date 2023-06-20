#include "minishell.h"

int	ft_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_order_matrix(char **matrix)
{
	int		i;
	int		ord;
	int		size;
	char	*swap;

	ord = 1;
	while (ord)
	{
		ord = 0;
		i = 0;
		while (i < ft_size_matrix(matrix) - 1)
		{
			size = ft_strlen(matrix[i]);
			if (ft_strlen(matrix[i + 1]) > (size_t) size)
				size = ft_strlen(matrix[i + 1]);
			if (ft_strncmp(matrix[i], matrix[i + 1], size) > 0)
			{
				ord = 1;
				swap = matrix[i];
				matrix[i] = matrix[i + 1];
				matrix[i + 1] = swap;
			}
			i++;
		}
	}
	return (matrix);
}

void	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("declare -x %s\n", matrix[i]);
		i++;
	}
}

void	ft_print_env(t_env *env)
{
	char	*str;
	char	**matrix;
	int		i;

	matrix = ft_calloc(ft_size_env(env) + 1, sizeof(char **));
	i = 0;
	while (env)
	{
		str = ft_strdup(env->key);
		if (env->value)
		{
			str = ft_strjoin(str, "=\"");
			str = ft_strjoin(str, ft_strdup(env->value));
			str = ft_strjoin(str, "\"");
		}
		matrix[i] = ft_strdup(str);
		env = env->next;
		i++;
	}
	matrix = ft_order_matrix(matrix);
	ft_print_matrix(matrix);
	ft_free_matrix(matrix);
	free(str);
}

int	ft_export(t_ms *ms, char *new)
{
	char	**split;
	char	*second;

	if (!new)
		ft_print_env(ms->exp);
	else
	{
		if (!ft_strrchr(new, '='))
			return (ft_insert_env(&ms->exp, ft_strdup(new), NULL), 0);
		split = ft_split(new, '=');
		if (!split)
			return (perror(new), 1);
		if (split[1])
			second = ft_strdup(split[1]);
		else
			second = ft_strdup("");
		if (!second)
		{
			perror("Memory allocation failed");
			ft_free_matrix(split);
			return (1);
		}
		ft_insert_env(&ms->exp, ft_strdup(split[0]), ft_strdup(second));
		ft_insert_env(&ms->env, ft_strdup(split[0]), ft_strdup(second));
		ft_free_matrix(split);
		free(second);
	}
	return (0);
}

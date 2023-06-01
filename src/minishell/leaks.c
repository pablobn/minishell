#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		// free(matrix);
		// matrix = NULL;
	}
}

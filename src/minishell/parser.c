#include "minishell.h"

int	ft_parser(void)
{
	int		i;
	int		j;
	char	aux[255];

	i = 0;
	j = -1;
	g_cmd.command = ft_calloc(ft_strlen(g_cmd.line) + 1, sizeof(char *));
	if (!g_cmd.command)
		return (-1);
	while (g_cmd.line[i])
	{
		while (g_cmd.line[i] == ' ')
			i++;
		if (g_cmd.line[i] == '>')
		{
			i++;
			if (g_cmd.line[i] == '>')
			{
				g_cmd.out_f = 1;
				i++;
				while (g_cmd.line[i] != ' ')
				{
					aux[++j] = g_cmd.line[i];
					i++;
				}
			aux[++j] = 0;
			}
			else
				g_cmd.out_f = 0;
			while (g_cmd.line[i] != ' ')
			{
				aux[++j] = g_cmd.line[i];
				i++;
			}
			aux[++j] = 0;
			g_cmd.out = open(aux, O_CREAT | O_TRUNC, 664);
		}
		//g_cmd.command[++j] = g_cmd.line[i];
		i++;
	}
	return (0);
}

#include "minishell.h"

int	ft_parser(void)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	g_cmd.command = ft_calloc(ft_strlen(g_cmd.line) + 1, sizeof(char *));
	if (!g_cmd.command)
		return (-1);
	while (g_cmd.line[i])
	{
		while (g_cmd.line[i] == ' ')
			i++;
		if (g_cmd.line[i] == '<')
			ft_infile();
		else if (g_cmd.line[i] == '<<')
			ft_here_doc();
		else if (g_cmd.line[i] == '>')
			ft_out_file();
		else if (g_cmd.line[i] == '>>')
			ft_out_file();
		else if (g_cmd.line[i] == '|')
			ft_new_pipe();
		g_cmd.command[++j] = g_cmd.line[i];
		i++;
	}
	return (0);
}

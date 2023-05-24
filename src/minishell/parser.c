#include "minishell.h"

int	ft_parser(t_command *cmd)
{
	int		i;
	int		j;
	char	aux[255];

	i = 0;
	j = -1;
	cmd->command = ft_calloc(ft_strlen(cmd->line) + 1, sizeof(char *));
	if (!cmd->command)
		return (-1);
	while (cmd->line[i])
	{
		while (cmd->line[i] == ' ')
			i++;
		if (cmd->line[i] == '>')
		{
			i++;
			if (cmd->line[i] == '>')
			{
				cmd->out_f = 1;
				i++;
				while (cmd->line[i] != ' ')
				{
					aux[++j] = cmd->line[i];
					i++;
				}
			aux[++j] = 0;
			}
			else
				cmd->out_f = 0;
			while (cmd->line[i] != ' ')
			{
				aux[++j] = cmd->line[i];
				i++;
			}
			aux[++j] = 0;
			cmd->out = open(aux, O_CREAT | O_TRUNC, 664);
		}
		//g_cmd.command[++j] = g_cmd.line[i];
		i++;
	}
	return (0);
}

#include "minishell.h"

static int	ft_space_iter(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

static void	ft_outfile(t_command *cmd, int i)
{
	int		j;
	char	aux[255];

	j = -1;
	if (cmd->line[i] == '>')
	{
		i++;
		while (cmd->line[i] != ' ')
		{
			aux[++j] = cmd->line[i];
			i++;
		}
		aux[++j] = 0;
		if (!cmd->out_f)
			cmd->out = open(aux, O_TRUNC | O_CREAT | O_WRONLY, 664);
		else
			cmd->out = open(aux, O_APPEND | O_CREAT | O_WRONLY, 664);
	}
}

int	ft_parser(t_command *cmd)
{
	int		i;

	i = 0;
	cmd->command = ft_calloc(ft_strlen(cmd->line) + 1, sizeof(char *));
	if (!cmd->command)
		return (-1);
	while (cmd->line[i])
	{
		i = ft_space_iter(cmd->line, i);
		ft_outfile(cmd, i);
		//g_cmd.command[++j] = g_cmd.line[i];
		i++;
	}
	return (0);
}

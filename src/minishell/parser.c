#include "minishell.h"

static int	ft_space_iter(char *str, int i)
{
	if (!str[i])
		return (i);
	while (str[i] == ' ')
		i++;
	return (i);
}

static int	ft_outfile(t_command *cmd, int i)
{
	int		j;
	char	aux[255];

	j = -1;
	if (!cmd->line[i])
		return (i);
	if (cmd->line[i] == '>')
	{
		i++;
		if (cmd->line[i] == '>')
		{
			cmd->out_f = 1;
			i++;
		}
		else
			cmd->out_f = 0;
		i = ft_space_iter(cmd->line, i);
		while (cmd->line[i] && cmd->line[i] != ' ')
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
	i = ft_space_iter(cmd->line, i);
	return (i);
}

int	ft_parser(t_command *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	cmd->command = ft_calloc(ft_strlen(cmd->line) + 1, sizeof(char *));
	if (!cmd->command)
		return (-1);
	while (cmd->line[i])
	{
		i = ft_space_iter(cmd->line, i);
		i = ft_outfile(cmd, i);

		cmd->command[++j] = cmd->line[i];
		i++;
	}
	return (0);
}

#include "minishell.h"

static int	ft_space_iter(char *str, int i)
{
	if (!str[i])
		return (i);
	while (str[i] == ' ')
		i++;
	return (i);
}

static int	ft_infile(t_command *cmd, int i)
{
	int		j;
	char	aux[255];

	j = -1;
	if (!cmd->line[i])
		return (i);
	if (cmd->line[i] == '<')
	{
		i++;
		if (cmd->line[i] == '<')
		{
			cmd->in_f = 1;
			i++;
		}
		else
			cmd->in_f = 0;
		i = ft_space_iter(cmd->line, i);
		while (cmd->line[i] && cmd->line[i] != ' ')
		{
			aux[++j] = cmd->line[i];
			i++;
		}
		aux[++j] = 0;
		if (cmd->in)
			close(cmd->in);
		cmd->in = open(aux, O_RDONLY);
	}
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
		if (cmd->out)
			close(cmd->out);
		if (!cmd->out_f)
			cmd->out = open(aux, O_TRUNC | O_CREAT | O_WRONLY, 777);
		else
			cmd->out = open(aux, O_APPEND | O_CREAT | O_WRONLY, 777);
	}
	return (i);
}

static int	ft_command(t_command *cmd, int i)
{
	int	j;

	j = -1;
	if (cmd->command[0])
		return (i);
	while (cmd->line[i] && ft_isalnum(cmd->line[i]))
	{
		cmd->command[++j] = cmd->line[i];
		i++;
	}
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
	cmd->flags = ft_calloc(ft_strlen(cmd->line) + 1, sizeof(char *));
	if (!cmd->flags)
		return (-1);
	while (cmd->line[i])
	{
		i = ft_space_iter(cmd->line, i);
		i = ft_outfile(cmd, i);
		i = ft_infile(cmd, i);
		i = ft_command(cmd, i);
		i++;
	}
	cmd->command = &cmd->command[ft_space_iter(cmd->command, 0)];
	return (0);
}

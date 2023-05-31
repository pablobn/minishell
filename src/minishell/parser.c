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

	j = 0;
	while (cmd->cmd[j])
		j++;
	while (cmd->line[i] && cmd->line[i] != ' ')
	{
		cmd->cmd[j] = cmd->line[i];
		i++;
		j++;
	}
	cmd->cmd[j] = ' ';
	return (i);
}

static int	ft_expand(t_ms *ms, int i)
{
	int	j;
	int	size;

	j = 0;
	if (ms->list->line[i] == '$')
	{
		i++;
		size = -1;
		while (ft_isalnum(ms->list->line[i + ++size]))
			;
			
	}
	return (i);
}

int	ft_parser(t_ms *ms)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	ms->list->cmd = ft_calloc(ft_strlen(ms->list->line) + 1, sizeof(char *));
	if (!ms->list->cmd)
		return (-1);
	ms->list->flags = ft_calloc(ft_strlen(ms->list->line) + 1, sizeof(char *));
	if (!ms->list->flags)
		return (-1);
	while (ms->list->line[i])
	{
		i = ft_space_iter(ms->list->line, i);
		i = ft_outfile(ms->list, i);
		i = ft_infile(ms->list, i);
		i = ft_expand(ms, i);
		i = ft_command(ms->list, i);
		i++;
	}
	//cmd->flags = ft_split(cmd->cmd, ' ');
	return (0);
}

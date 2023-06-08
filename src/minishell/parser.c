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
			if (cmd->line[i + 1] && cmd->line[i] == '\\')
				i++;
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
			if (cmd->line[i + 1] && cmd->line[i] == '\\')
				i++;
			aux[++j] = cmd->line[i];
			i++;
		}
		aux[++j] = 0;
		if (cmd->out)
			close(cmd->out);
		if (!cmd->out_f)
			cmd->out = open(aux, O_TRUNC | O_CREAT | O_WRONLY, 0777);
		else
			cmd->out = open(aux, O_APPEND | O_CREAT | O_WRONLY, 0777);
	}
	return (i);
}

static int	ft_command(t_command *list, int i)
{
	int		j;
	char	*temp;

	j = 0;
	while (list->line[i + j] && list->line[i + j] != ' ')
		j++;
	temp = ft_calloc(sizeof(char *), j + 1);
	if (!temp)
		return (i);
	j = 0;
	while (list->line[i] && list->line[i] != ' ')
	{
		if (list->line[i + 1] && list->line[i] == '\\')
			i++;
		temp[j] = list->line[i];
		j++;
		i++;
	}
	//leaks
	if (list->cmd)
	{
		list->cmd = ft_strjoin(list->cmd, temp);
		free(temp);
		temp = NULL;
	}
	else
		list->cmd = temp;
	list->cmd = ft_strjoin(list->cmd, " ");
	return (i);
}

int	ft_parser(t_ms *ms)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (ms->list->line[i])
	{
		//i = ft_space_iter(ms->list->line, i);
		i = ft_outfile(ms->list, i);
		i = ft_infile(ms->list, i);
		i = ft_command(ms->list, i);
		i++;
	}
	if (ms->list->cmd)
		ms->list->flags = ft_split(ms->list->cmd, ' ');
	return (0);
}

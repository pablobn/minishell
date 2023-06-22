#include "minishell.h"

static int	ft_space_iter(char *str, int i)
{
	if (!str)
		return (i);
	while (str[i] && str[i] == ' ' && (i - 1 >= -1 || str[i - 1] == '\\'))
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
			//cmd->in_f = 1;
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

static void	ft_outfile_file(t_command *cmd, char *aux)
{
	if (cmd->out)
		close(cmd->out);
	if (!cmd->out_f)
		cmd->out = open(aux, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	else
		cmd->out = open(aux, O_APPEND | O_CREAT | O_WRONLY, 0777);
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
		if (cmd->line[++i] == '>')
			cmd->out_f = i;
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
		ft_outfile_file(cmd, aux);
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
	temp = ft_calloc(sizeof(char *), j + 255);
	if (!temp)
		return (i);
	j = 0;
	while (list->line[i] && list->line[i] != ' '
		&& list->line[i] != '<' && list->line[i] != '>')
	{
		if (list->line[i + 1] && list->line[i] == '\\')
			i++;
		temp[j++] = list->line[i++];
	}
	if (list->cmd)
	{
		list->cmd = ft_strjoin_free(list->cmd, temp);
		free(temp);
	}
	else
		list->cmd = temp;
	return (list->cmd = ft_strjoin_free(list->cmd, " \0"), i);
}

void	ft_parser(t_command *list)
{
	int		i;

	i = ft_space_iter(list->line, 0);
	while (list->line && list->line[i])
	{
		i = ft_outfile(list, i);
		i = ft_space_iter(list->line, i);
		i = ft_infile(list, i);
		i = ft_space_iter(list->line, i);
		i = ft_command(list, i);
		i = ft_space_iter(list->line, i);
	}
	if (list->cmd)
		list->flags = ft_split(list->cmd, ' ');
	else
		list->flags = ft_calloc(sizeof(char *), 1);
	if (list->flags && list->flags[0]
		&& ft_space_iter(list->flags[0], 0) == (int)ft_strlen(list->flags[0]))
		list->flags[0] = NULL;
	return ;
}

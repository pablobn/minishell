#include "minishell.h"

void	ft_parser(t_command *cmd)
{
	cmd->command = "ls";
	cmd->next = NULL;
	cmd->back = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
}

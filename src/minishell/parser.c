#include "minishell.h"

extern t_ms *g_ms;

void	ft_parser(t_command *cmd)
{
	g_ms->list->command = "ls";
	g_ms->list->next = NULL;
	g_ms->list->back = NULL;
}

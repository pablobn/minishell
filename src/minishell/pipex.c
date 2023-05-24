#include "minishell.h"

extern t_command *g_cmd;


void	ft_give_value()
{
	t_command	b;
	char *first[] = {"ls", "-l"};
	char *second[] = {"wc", "-l"};

	b.command = "wc";
	b.next = NULL;
	b.back = g_cmd;
	b.flags = second;
	g_cmd->command = "ls";
	g_cmd->next = &b;
	g_cmd->back = NULL;
	g_cmd->flags = first;
	g_cmd = g_cmd->next;
	g_cmd = g_cmd->back;
	printf("%s\n", g_cmd->command);
}

int	ft_pipex(void)
{
	int	i;

	ft_give_value();
	i = ft_size_list();
	return (0);
}

#include "minishell.h"

void	ft_give_value(t_command *a)
{
	t_command	b;
	char *first[] = {"ls", "-l"};
	char *second[] = {"wc", "-l"};

	b.cmd = "wc";
	b.next = NULL;
	b.back = a;
	b.flags = second;
	a->cmd = "ls";
	a->next = &b;
	a->back = NULL;
	a->flags = first;
}

int	ft_pipex(t_ms *ms)
{
	int			i;
	t_command	*list;

	list = ms->list;
	ft_give_value(list);
	i = ft_size_list(list);
	return (0);
}

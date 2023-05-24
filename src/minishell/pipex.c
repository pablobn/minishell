#include "minishell.h"

void	ft_give_value(t_command *a)
{
	t_command	b;
	char *first[] = {"ls", "-l"};
	char *second[] = {"wc", "-l"};

	b.command = "wc";
	b.next = NULL;
	b.back = a;
	b.flags = second;
	a->command = "ls";
	a->next = &b;
	a->back = NULL;
	a->flags = first;
	a = a->next;
	a = a->back;
	printf("%s\n", a->command);
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

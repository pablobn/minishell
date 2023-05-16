#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	line = "";
	while (line)
	{
		printf("minishell$ ");
		line = readline(line);
	}
	return (0);
}

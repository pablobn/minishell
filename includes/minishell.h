#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

//leaks.c
void	ft_leaks(void);
//parser.c
void	ft_parser(t_command **cmd);
//Structs
typedef struct s_command
{
	struct s_command	*next;
	struct s_command	*back;
	struct s_file		*out;
	struct s_file		*in;
	char				*command;
	char				**flags;
}t_command;

typedef struct s_file
{
	struct s_file	*next;
	struct s_file	*back;
	int				**fd;
	int				flag;
}t_file;

#endif
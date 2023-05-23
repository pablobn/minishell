#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
//Para silenciar los echos de la terminal
# include <termios.h>
# include "../library/libft/libft.h"
// COLORS
# define RED "\x1b[34m"
# define GREEN "\x1b[32m"
# define RESET "\x1b[37m"
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

t_command	g_cmd;

//Prototypes
//utils.c
int		ft_size_list(void);
//leaks.c
void	ft_leaks(void);
//parser.c
void	ft_parser(t_command *cmd);
//prompt.c
void	ft_prompt(void);
//handler.c
void	ft_handler(int sig);
//pipex.c
int		ft_pipex(void);
#endif
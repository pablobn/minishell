#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../library/libft/libft.h"
//Para silenciar los echos de la terminal
# include <termios.h>
# include "../library/libft/libft.h"
// COLORS
# define BLUE "\001\x1b[34m\002"
# define GREEN "\001\x1b[32m\002"
# define RESET "\001\x1b[37m\002"
//Structs

typedef struct s_command
{
	struct s_command	*next;
	struct s_command	*back;
	int					out;
	int					out_f;
	int					in;
	int					in_f;
	char				*line;
	char				*command;
	char				**flags;
}t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
}t_env;

typedef struct s_ms
{
	t_command	*list;
	t_env		*env;
}t_ms;


//Prototypes
//list_utils.c
int		ft_size_list(t_command *list);
//leaks.c
void	ft_leaks(void);
//parser.c
int		ft_parser(t_command *cmd);
//prompt.c
void	ft_prompt(t_command *cmd);
//handler.c
void	ft_handler(int sig);
//pipex.c
int		ft_pipex(t_ms *ms);
//init_env.c
int		ft_init_env(t_ms *ms, char **envp);
#endif
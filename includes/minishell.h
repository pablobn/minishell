#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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
	char				*cmd;
	char				**flags;
}t_command;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}t_env;

typedef struct s_ms
{
	t_command	**list;
	t_env		*env;
	t_env		*exp;
	char		*line;
}t_ms;

//Prototypes
//list_utils.c
int			ft_size_list(t_command *list);
int			ft_size_matrix(char **str);
//leaks.c
void		ft_leaks(void);
//parser.c
void		ft_parser(t_command *list);
//prompt.c
void		ft_prompt(t_ms *ms);
//handler.c
void		ft_handler(int sig);
//pipex.c
void		ft_pipex(t_command *list, t_env *env);
int			ft_execute_line(t_ms *ms);
//init_env.c
int			ft_init_env(t_ms *ms, char **envp);
void		ft_insert_env(t_env **env, char *key, char *value);
void		ft_insert_last_env(t_env **env, char *key, char *value);
char		*ft_get_env_key(t_env *env, char *str);
char		**ft_get_envp(t_env *env);
//built_in
int			ft_check_built_in(t_command *list);
int			ft_built_in(t_command *list, t_ms *ms);
//cd_built
int			ft_cd(t_command *list, t_ms *ms);
//unset_built
int			ft_unset(t_ms *ms, char *str);
void		ft_remove_env(t_env **env, char *str);
//export_built
int			ft_export(t_ms *ms, char *new);
//free
void		ft_free_matrix(char **matrix);
t_env		*free_env(t_env *env);
void		ft_free_ms(t_ms *ms);
void		ft_free_list(t_command	**list);
char		*ft_strjoin_free(char *str, char *buf);
#endif
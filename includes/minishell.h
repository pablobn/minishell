/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:45:10 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/26 19:45:13 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
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
	char				*heredoc;
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
	int			status;
	t_command	**list;
	t_env		*env;
	t_env		*exp;
	char		*line;
	pid_t		pid;
}t_ms;

//Prototypes
//built_in
int			ft_pwd(void);
int			ft_echo(t_command *list);
int			ft_built_in(t_command *list, t_ms *ms);
int			ft_built_in_cd(t_command *list, t_ms *ms);
int			ft_check_built_in_cd(t_command *list);
int			ft_check_built_in(t_command *list);
//cd_built
char		*ft_get_previous_path(char *pwd);
char		*ft_parse_absolute_rute(char *str, int i);
char		*ft_parse_cd(char *str);
char		*ft_path_cd(t_command *list, t_env *env);
int			ft_cd(t_command *list, t_ms *ms);
//command
int			ft_command(t_command *list, int i);
//expand
t_command	*ft_expand(t_command *list, t_ms *ms, int i, int j);
//export_built
int			ft_export(t_ms *ms, char *new);
//free
void		ft_free_matrix(char **matrix);
t_env		*free_env(t_env *env);
void		ft_free_ms(t_ms *ms);
void		ft_free_list(t_command	**list);
char		*ft_strjoin_free(char *str, char *buf);
//handler.c
void		ft_handler(int sig);
//init_env.c
int			ft_init_env(t_ms *ms, char **envp);
void		ft_insert_env(t_env **env, char *key, char *value);
void		ft_insert_last_env(t_env **env, char *key, char *value);
char		*ft_get_env_key(t_env *env, char *str);
char		**ft_get_envp(t_env *env);
//leaks.c
void		ft_leaks(void);
//list_utils.c
int			ft_size_list(t_command *list);
//minishell.c
int			main(int argc, char **argv, char **envp);
//parser.c
void		ft_parser(t_command *list);
int			ft_size_matrix(char **str);
//pipex.c
void		ft_pipex(t_command *list, t_ms *ms);
int			ft_start_pipex(t_command *list, t_ms *ms);
//prompt.c
void		ft_prompt(t_ms *ms);
//quotes
t_command	*ft_quotes(t_command *list);
//split_pipex
char		**ft_split_pipex(char const *s, char c);
//unset_built
int			ft_unset(t_ms *ms, char *str);
void		ft_remove_env(t_env **env, char *str);
//utils_prompt
int			ft_is_empty(char *str);
int			ft_space_iter(char *str, int i);
int			ft_count_env(t_env *env);
//gnl
char		*get_next_line(int fd);
//here_doc
void		ft_get_here_doc(t_command *list);
//execute_cmd
int			ft_execute_line(t_ms *ms);
void		ft_execute_command(t_command *list, t_env *env);
//check_built_in
int			ft_check_built_in(t_command *list);
int			ft_check_built_in_cd(t_command *list);
#endif
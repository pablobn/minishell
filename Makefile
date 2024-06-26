NAME = minishell
LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"
CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
CC = gcc -g3

CFLAGS = -Wall -Wextra -Werror

# SOURCES
SRCSFD = src/
MINISHELLFD = minishell/
MINISHELL_SRC = minishell.c 		\
				leaks.c				\
				parser.c			\
				pipex.c				\
				list_utils.c		\
				prompt.c			\
				handler.c			\
				init_env.c			\
				built_in.c			\
				cd_built.c			\
				unset_built.c		\
				export_built.c		\
				free.c				\
				utils_minishell.c	\
				quotes.c			\
				expand.c			\
				command.c			\
				split_pipex.c		\
				here_doc.c			\
				execute_cmd.c		\
				check_built_in.c
GNLPFD = get_next_line/
GNLPFD_SRC = get_next_line.c\
			get_next_line_utils.c
# OBJECTS
OBJSFD = objs/
MINISHELL_OBJ = $(addprefix $(OBJSFD)$(MINISHELLFD), $(MINISHELL_SRC:.c=.o))
GNL_OBJS = $(addprefix $(OBJSFD)$(GNLPFD), $(GNLPFD_SRC:.c=.o))
#HEADERS
HEADERFD = includes/
HEADER = minishell.h
HEADERS = $(addprefix $(HEADERFD), $(HEADER))
HEADER_READLINE = -I /Users/$(USER)/.brew/opt/readline/lib
#INCLUDES
# HEADER INCLUDES
HEADER_INC = -I./includes
# LIBFT INCLUDES
LIBFT_HDR = -I./library/libft/includes/
LIB_BINARY = -L./library/libft -lft
LIBFT = library/libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: ${NAME}

${LIBFT}:
	@make -C library/libft

$(OBJSFD):
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(OBJSFD)$(MINISHELLFD): $(OBJSFD)
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(OBJSFD)$(GNLPFD): $(OBJSFD)
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

${NAME}: ${LIBFT} $(OBJSFD)$(GNLPFD) ${GNL_OBJS} ${OBJSFD}$(MINISHELLFD) ${MINISHELL_OBJ} $(HEADERS)
	@${CC} ${CFLAGS} $(LIB_BINARY) ${GNL_OBJS} ${MINISHELL_OBJ} ${LIBFT} -o $@ -lreadline $(LDFLAGS) $(CPPFLAGS)
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

$(OBJSFD)$(MINISHELLFD)%.o: $(SRCSFD)$(MINISHELLFD)%.c $(HEADERS)
	@${CC} $(CFLAGS) $(HEADER_INC) ${LIBFT_HDR}  -o $@ -c $<

$(OBJSFD)$(GNLPFD)%.o: $(SRCSFD)$(GNLPFD)%.c
		@gcc $(CFLAGS) -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJSFD) debug
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@${MAKE} -s -C library/libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
	@${MAKE} -s -C library/libft/ fclean

re: fclean all

.PHONY: all clean fclean re debug
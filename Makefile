NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# SOURCES
SRCSFD = src/
MINISHELLFD = minishell/
MINISHELL_SRC = minishell.c \
				leaks.c		\
				parser.c

# OBJECTS
OBJSFD = objs/
MINISHELL_OBJ = $(addprefix $(OBJSFD)$(MINISHELLFD), $(MINISHELL_SRC:.c=.o))

#HEADERS
HEADERFD = includes/
HEADER = minishell.h
HEADERS = $(addprefix $(HEADERFD), $(HEADER))

#INCLUDES
# HEADER INCLUDES
HEADER_INC = -I./includes
# LIBFT INCLUDES
LIBFT_HRD = -I./library/libft/includes/
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

${NAME}: ${LIBFT} ${OBJSFD}$(MINISHELLFD) ${MINISHELL_OBJ}  $(HEADERS)
	@${CC} -lreadline ${CFLAGS} ${MINISHELL_OBJ} -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

$(OBJSFD)$(MINISHELLFD)%.o: $(SRCSFD)$(MINISHELLFD)%.c $(HEADERS) 
	@${CC} $(CFLAGS) $(HEADER_INC)  -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@${MAKE} -s -C library/libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
	@${MAKE} -s -C library/libft/ fclean

re: fclean all

.PHONY: all clean fclean re
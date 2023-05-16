NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# SOURCES
SRCSFD = src/
MINISHELLFD = minishell/
MINISHELL_SRC = minishell.c

# OBJECTS
OBJSFD = objs/
MINISHELL_OBJ = $(addprefix $(OBJSFD)$(MINISHELLFD), $(MINISHELL_SRC:.c=.o))

#HEADERS
HEADERFD = includes/
HEADER = minishell.h
HEADERS = $(addprefix $(HEADERFD), $(HEADER))

HEADER_INC = -I./includes

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: ${NAME}


$(OBJSFD):
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(OBJSFD)$(MINISHELLFD): $(OBJSFD)
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

${NAME}: ${OBJSFD}$(MINISHELLFD) ${MINISHELL_OBJ}  $(HEADERS)
	@gcc ${CFLAGS} ${MINISHELL_OBJ} -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

$(OBJSFD)$(MINISHELLFD)%.o: $(SRCSFD)$(MINISHELLFD)%.c $(HEADERS) 
	@gcc $(CFLAGS) $(HEADER_INC)  -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: all clean fclean re
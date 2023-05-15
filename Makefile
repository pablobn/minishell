NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# SOURCES
SRCSFD = src/
MINISHELLFD = minishell/
MINISHELL_SRC = philo.c

# OBJECTS
OBJSFD = objs/
PHILO_OBJ = $(addprefix $(OBJSFD)$(PHILOFD), $(PHILO_SRC:.c=.o))

HDRSFD = includes/
HDR = philo.h
HDRS = $(addprefix $(HDRSFD), $(HDR))

HDR_INC = -I./includes

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: ${HDRS} ${NAME}


$(OBJSFD):
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(OBJSFD)$(PHILOFD): $(OBJSFD)
		@mkdir $@
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

${NAME}: ${OBJSFD}$(PHILOFD) ${PHILO_OBJ}  $(HDRS)
	@gcc ${CFLAGS} ${PHILO_OBJ} -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

$(OBJSFD)$(PHILOFD)%.o: $(SRCSFD)$(PHILOFD)%.c $(HDRS) 
	@gcc $(CFLAGS) $(HDR_INC)  -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 15:45:05 by pbengoec          #+#    #+#              #
#    Updated: 2023/03/23 19:10:15 by pbengoec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= gcc
CFLAGS		= -Werror -Wall -Wextra
RM			= rm -f
SRCS		= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_tolower.c ft_toupper.c\
			  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
			  ft_strlcat.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
			  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS		= ${SRCS:.c=.o}

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

${NAME}	:
			@${CC} -c ${CFLAGS} ${SRCS} 
			@ar crs ${NAME} ${OBJS}
			@echo "\t[ $(GREEN)✔$(NONE) ] libft/libft.a library"
all		:	${NAME}

clean	:
		@${RM} ${OBJS}
		@echo "\t[ $(RED)✗$(NONE) ] libft/$(OBJ_DIR) directory"
	
fclean	:	clean
		@${RM} -f ${NAME}
		@echo "\t[ $(RED)✗$(NONE) ] libft/$(NAME) library"

re		:	fclean all

.PHONY: all clean fclean re
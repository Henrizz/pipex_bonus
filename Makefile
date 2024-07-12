# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:00:12 by hzimmerm          #+#    #+#              #
#    Updated: 2024/07/10 16:29:31 by hzimmerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -g -Wall -Wextra -Werror -Isrcs/libft
SRCS = srcs/main.c srcs/utils.c srcs/exits.c srcs/execution.c srcs/files.c srcs/pipes.c
LDFLAGS = -fsanitize=address
LIBFT = srcs/libft/libft.a
LIB = srcs/libft
OBJS = $(SRCS:.c=.o)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -f "$(LIBFT)" ]; then \
		make -C $(LIB); \
	fi
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	chmod +x $(NAME)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) srcs/*.o $(LIB)/*.o

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean $(NAME)

.PHONY: all clean fclean re

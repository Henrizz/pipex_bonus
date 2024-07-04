# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:00:12 by hzimmerm          #+#    #+#              #
#    Updated: 2024/06/18 17:32:36 by hzimmerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CFLAGS = -g -Wall -Wextra -Werror -Isrcs/libft
SRCS = srcs/main.c srcs/utils.c
BONUS_SRCS = bonus/main_bonus.c bonus/utils_bonus.c
LDFLAGS = -fsanitize=address
LIBFT = srcs/libft/libft.a
LIB = srcs/libft
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -f "$(LIBFT)" ]; then \
		make -C $(LIB); \
	fi
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	chmod +x $(NAME)

bonus : $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@if [ ! -f "$(LIBFT)" ]; then \
		make -C $(LIB); \
	fi
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	chmod +x $(BONUS_NAME)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) srcs/*.o $(LIB)/*.o bonus/*.o

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean $(NAME) $(BONUS_NAME)

.PHONY: all clean fclean re

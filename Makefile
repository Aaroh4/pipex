# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:36:32 by ahamalai          #+#    #+#              #
#    Updated: 2024/02/29 16:33:37 by ahamalai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
LIBFTDIR = ./libft
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror 
HEAD = includes/pipex.h
SRCS = srcs/main.c srcs/error_handling.c srcs/children.c 
OBJS = $(SRCS:.c=.o)
SRCS_B = bonus/children_bonus.c bonus/error_handling_bonus.c \
		bonus/main_bonus.c bonus/finding_files_bonus.c \
		
OBJS_B = $(SRCS_B:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C $(LIBFTDIR)
		@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) 

bonus:	$(OBJS_B)
		@$(MAKE) -C $(LIBFTDIR)
		@$(CC) $(CFLAGS) $(OBJS_B) ./libft/libft.a -o $(NAME) 

clean:
		@rm -f $(OBJS)
		@rm -f $(OBJS_B)
		@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
		@rm -f $(NAME)
		@rm -f libft.a
		@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re bonus

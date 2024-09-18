# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habouda <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 01:37:02 by Habouda           #+#    #+#              #
#    Updated: 2024/09/18 17:30:41 by habouda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPIL #####################################################################

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
NAME 	= pipex

### SRC ########################################################################

SRCS	=	pipex.c \
### OBJS ###########################################################################
			
OBJS	= $(SRCS:.c=.o)

### LIBFT ###########################################################################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

### COMMANDS #######################################################################

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all re fclean clean 
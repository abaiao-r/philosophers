# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 14:04:06 by codespace         #+#    #+#              #
#    Updated: 2023/06/12 17:52:25 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 

# Directories
SRCDIR = ./src
OBJDIR = ./objs

# Source Files

SRCS = 	$(SRCDIR)/main.c \


OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Targets
NAME = philo

all: 	$(NAME)

clean:
		rm -rf $(OBJDIR)

fclean:	clean
		rm -f $(NAME)

run:	all
		./$(NAME)
		

re:		fclean all

lldb:	all
		lldb $(NAME)

gdb:	all
		gdb $(NAME)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) $(CFLAGS) -pthread -o  $(NAME) 

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ 

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean bonus re run
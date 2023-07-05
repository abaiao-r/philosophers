# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 14:04:06 by codespace         #+#    #+#              #
#    Updated: 2023/07/05 18:35:42 by abaiao-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

# Directories
SRCDIR = ./src
OBJDIR = ./objs

# Source Files

SRCS = 	$(SRCDIR)/main.c \
		$(SRCDIR)/arg_check.c \
		$(SRCDIR)/free_resources.c \
		$(SRCDIR)/philo_data.c \
		$(SRCDIR)/routine.c \
		$(SRCDIR)/routine_actions.c \
		$(SRCDIR)/routine_utils.c \
		$(SRCDIR)/utils.c \
		$(SRCDIR)/utils_2.c


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

valgrind_drd: 	all
			valgrind --tool=drd ./$(NAME) $(ARGS)

valgrind_helgrind: 	all
					valgrind --tool=helgrind ./$(NAME) $(ARGS)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) $(CFLAGS) -pthread -o  $(NAME) 

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ 

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean bonus re run
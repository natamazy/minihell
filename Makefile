# Project name
NAME = minishell

# Readline name
READLINE = readline

# Compilator
CC = cc
# Compilator flags
CFLAGS = -Wall -Wextra -Werror -Iincludes #-g3 -fsanitize=thread

# Headers
HEADERS = includes/minishell.h

# Source directory
SRCS_DIR = sources/
# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = minishell.c \

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Configuring readline
$(READLINE):
	./config_readline readline

# Cleaning
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	rm -rf $(READLINE)
	make clean -C readline-8.2

# Remaking
re: clean all

# PHONY files
.PHONY: all clean fclean re
#Executable Name
NAME = ft_traceroute

#Directories
SRCS_DIR = srcs
OBJS_DIR = objects
INC_DIR  = include

#Sources / Headers
SRC	=	main.c
SRCS =	$(addprefix $(SRCS_DIR)/, $(SRC))						\
HEADERS = $(INC_DIR)/ft_traceroute.h

#Objects
OBJS = $(subst $(SRCS_DIR)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

#Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INC_FOLDER = -I $(INC_DIR)

#Rules
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC_FOLDER) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) $(INC_FOLDER) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

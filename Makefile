#####################
#  Executable Name	#
#####################
NAME = ft_traceroute

#####################
#    Directories	#
#####################
SRCS_DIR = srcs
OBJS_DIR = objects
INC_DIR  = include

#####################
# Sources / Headers #
#####################
SRC	=	main.c						\
		ft_traceroute.c				\
		get_addr_struct.c			\
		process_checksum.c			\
		create_socket.c				\
		loop.c						\
		display_traceroute_dest.c	\
		receive_icmp_reply.c		\

SRC_PARSING =	parsing.c	\

SRC_DISPLAY =	display_help_and_exit.c			\
				display_bad_option_and_exit.c	\

SRCS =	$(addprefix $(SRCS_DIR)/, $(SRC))			\
		$(addprefix $(SRCS_DIR)/parsing/, $(SRC_PARSING))	\
		$(addprefix $(SRCS_DIR)/display/, $(SRC_DISPLAY))	\

HEADERS = $(INC_DIR)/ft_traceroute.h

#####################
#      Objects      #
#####################
OBJS = $(subst $(SRCS_DIR)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

#####################
#    Compilation	#
#####################
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INC_FOLDER = -I $(INC_DIR)

#####################
#       Rules       #
#####################
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC_FOLDER) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p	$(OBJS_DIR)/parsing	\
				$(OBJS_DIR)/display	\

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

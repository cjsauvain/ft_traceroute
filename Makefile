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
SRC	=	main.c							\
		ft_traceroute.c					\
		get_addr_structures.c			\
		create_sockets.c				\
		loop.c							\
		receive_icmp_reply.c			\
		clean_exit.c					\
		build_ip_pckt.c					\
		initialize_traceroute_struct.c	\
		get_time.c						\
		get_checksum.c					\

SRC_PARSING =	parsing.c	\

SRC_DISPLAY =	display_help_and_exit.c			\
				display_bad_option_and_exit.c	\
				display_routing_infos.c			\
				display_traceroute_dest.c		\

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
CC = clang
CFLAGS = -Wall -Wextra -std=c23
INC_FOLDER = -I $(INC_DIR)

ifeq ($(DEV), 1)
CFLAGS += -g3
USE_WARNINGS := 1
EXTRA_DEPS += compile_commands.json
endif

ifneq ($(USE_WARNINGS), 1)
CFLAGS += -Werror
endif

ifeq ($(SILENT), 1)
CC=@clang
endif

#####################
#       Rules       #
#####################

all: $(EXTRA_DEPS) $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FOLDER) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

compile_commands.json: clean
	@bear -- make --no-print-directory SILENT=1 USE_WARNINGS=1 $(NAME) -j$(shell nproc)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re compile_commands.json

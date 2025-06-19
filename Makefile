#####################
#  Executable Name	#
#####################
NAME = ft_traceroute

#####################
#  Library Name 	#
#####################
LIBFT = libft.a

#####################
#    Directories	#
#####################
SRCS_DIR = srcs
OBJS_DIR = obj
INC_DIR  = inc
LIBFT_DIR = libft
LIBFT_INC = $(LIBFT_DIR)/inc

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
		get_time.c						\
		get_checksum.c					\

SRC_PARSING =	parsing.c	\

SRC_DISPLAY =	display_help_and_exit.c				\
				display_routing_infos.c				\
				display_traceroute_dest.c			\
				display_invalid_number_of_probes.c	\
				display_invalid_dest_port.c			\
				display_invalid_max_hop.c			\
				display_invalid_first_hop.c			\
				display_invalid_wait.c			\

SRCS =	$(addprefix $(SRCS_DIR)/, $(SRC))			\
		$(addprefix $(SRCS_DIR)/parsing/, $(SRC_PARSING))	\
		$(addprefix $(SRCS_DIR)/display/, $(SRC_DISPLAY))	\

HEADERS = $(INC_DIR)/ft_traceroute.h $(LIBFT_INC)

#####################
#      Objects      #
#####################
OBJS = $(subst $(SRCS_DIR)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

#####################
#    Compilation	#
#####################
CC = clang
CFLAGS = -Wall -Wextra -std=c23
LIBFLAGS = -L$(LIBFT_DIR) -lft
INC_FOLDER = -I $(INC_DIR) -I $(LIBFT_INC)

ifeq ($(DEV), 1)
CFLAGS += -g3
USE_WARNINGS := 1
EXTRA_DEPS += compile_commands.json
endif

#####################
#       Rules       #
#####################

all: $(EXTRA_DEPS) $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FOLDER) -c $< -o $@

$(LIBFT):
	make --no-print-directory -s -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFLAGS) -o $(NAME)

compile_commands.json: clean
	@bear -- make --no-print-directory -s USE_WARNINGS=1 $(NAME) -j$(shell nproc)

clean:
	make clean --no-print-directory -s -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(LIBFT_DIR)/$(LIBFT)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re compile_commands.json

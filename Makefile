# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongjule <yongjule@42student.42seoul.kr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:00:27 by yongjule          #+#    #+#              #
#    Updated: 2021/09/19 15:22:27 by yongjule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address
#	CFLAGS = -g
else
	CFLAGS = -Wall -Wextra -Werror
endif

NAME			= minishell 

SRCS_DIR		= ./src/
#SRCS_DIR_BONUS = ./srcs/bonus/
SRCS_PIPE_DIR	= ./src/pipe/
SRCS_PARSE_DIR	= ./src/parse/

# NOTE - referring to M1 rosetta arch -86_64 brew readline lib
ARCH := $(shell arch)
ifeq ($(ARCH), i386)
	RDLN_LFLAGS	= -l readline -L$(HOME)/.brew/opt/readline/lib
	RDLN_INC	= -I$(HOME)/.brew/opt/readline/include
endif
ifeq ($(ARCH), arm64)
	RDLN_LFLAGS	= -l readline -L /opt/homebrew/opt/readline/lib
	RDLN_INC	= -I /opt/homebrew/opt/readline/include
endif

LIB_DIR			= lib/
LIBFT_DIR		= $(LIB_DIR)libft/
LIBFT_FLAGS		= -L./$(LIBFT_DIR) -lft
LIBFT_FILE		= $(LIBFT_DIR)libft.a

INC_DIR_MAN		= ./include/
#INC_DIR_BONUS = ./incs/bonus/

SRCS_PIPE		= $(addprefix $(SRCS_PIPE_DIR), \
				breed_process.c\
				check_validity.c\
				connect_pipe.c\
				file_redirection.c\
				ft_atoi_fd.c\
				get_next_line.c\
				get_next_line_utils.c\
				get_params.c\
				parse_commend.c\
				pipe_main.c\
				pipe_signal.c\
				rdr_info.c\
				rdr_list.c\
				rdr_read_info.c\
				rdr_write_info.c\
				wait_info.c\
				waiting.c\
				string_utils.c\
				)

SRCS_PARSE		= $(addprefix $(SRCS_PARSE_DIR), \
				parse_main.c\
				parse_split.c\
				sub_env.c\
				utils_main.c\
				utils_split.c\
				check_syntax.c\
				split_rdr.c\
				)

SRCS_MAN		= $(addprefix $(SRCS_DIR), \
				main.c\
				)

# NOTE - parse only
# SRCS_MAN		+= $(SRCS_PARSE)
SRCS_MAN		+= $(SRCS_PIPE) $(SRCS_PARSE)

SRCS_BONUS		= $(addprefix $(SRCS_DIR_BONUS), \
	   			)

OBJS_MAN		= ${SRCS_MAN:%.c=%.o}

OBJS_BONUS		= ${SRCS_BONUS:%.c=%.o}

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS_BONUS)
else
	OBJ_FILES = $(OBJS_MAN)
endif

ifdef WITH_BONUS
	INC_DIR = $(INC_DIR_BONUS)
else
	INC_DIR = $(INC_DIR_MAN)
endif


.PHONY			: all
all				: $(LIBFT_FILE) $(OBJ_FILES) $(NAME)

$(NAME)			: $(LIBFT_FILE) $(OBJ_FILES)
				$(CC) $(CFLAGS) $(OBJ_FILES) $(RDLN_LFLAGS) $(RDLN_INC) $(LIBFT_FLAGS) -I$(INC_DIR) -o $@ 

.PHONY			: bonus
bonus			:
				@make WITH_BONUS=1 $(NAME)

%.o				: %.c
				$(CC) $(CFLAGS) $(RDLN_INC) -I$(INC_DIR) -c $< -o $@

$(LIBFT_FILE)	:
				@make -C $(LIBFT_DIR) bonus

.PHONY			: clean
clean			:
				rm -f $(OBJS_MAN) $(OBJS_BONUS)
				make -C $(LIBFT_DIR) clean

.PHONY			: fclean
fclean			: clean
				rm -f $(NAME)
				make -C $(LIBFT_DIR) fclean

.PHONY			: ffclean
ffclean			: clean
				rm -f $(NAME)
				rm -rf $(NAME).dSYM

.PHONY			: re
re				: fclean all

.PHONY			: re_bonus
re_bonus		: fclean bonus

.PHONY			: debug
debug			: 
				@make -C $(LIBFT_DIR) DEBUG=1
				@make DEBUG=1

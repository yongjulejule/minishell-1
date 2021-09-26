# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:00:27 by yongjule          #+#    #+#              #
#    Updated: 2021/09/26 18:50:26 by ghan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc

ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address
else ifdef LEAKS
	CFLAGS = -g
else 
	CFLAGS = -Wall -Wextra -Werror
endif

NAME			= minishell 

SRCS_DIR		= ./src/
#SRCS_DIR_BONUS = ./srcs/bonus/
SRCS_RDR_DIR	= ./src/redir/
SRCS_EXEC_DIR	= ./src/exec/
SRCS_PARSE_DIR	= ./src/parse/
SRCS_BLTIN_DIR	= ./src/builtin/

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

SRCS_BLTIN		= $(addprefix $(SRCS_BLTIN_DIR), \
				chdir.c\
				echo.c\
				env.c\
				exit.c\
				export.c\
				handle_error.c\
				pwd.c\
				)

SRCS_RDR	= $(addprefix $(SRCS_RDR_DIR),\
				rdr_info.c\
				rdr_list.c\
				rdr_read_info.c\
				rdr_write_info.c\
				connect_pipe.c\
				file_redirection.c\
				ft_atoi_fd.c\
			  	)

SRCS_EXEC		= $(addprefix $(SRCS_EXEC_DIR), \
				execute_subshell.c\
				check_validity.c\
				get_params.c\
				parse_command.c\
				exec_main.c\
				exec_signal.c\
				wait_info.c\
				waiting.c\
				string_utils.c\
				free_structure.c\
				)

SRCS_PARSE		= $(addprefix $(SRCS_PARSE_DIR), \
				parse_main.c\
				internal_prompt.c\
				parse_split.c\
				split_rdr.c\
				parse_lst.c\
				sub_env.c\
				check_syntax.c\
				utils_parse_main.c\
				utils_split.c\
				utils_syntax.c\
				)

SRCS_MAN		= $(addprefix $(SRCS_DIR), \
				main.c\
				utils_main.c\
				main_signal.c\
				diy_envp.c\
				)

SRCS_MAN		+= $(SRCS_EXEC) $(SRCS_RDR) $(SRCS_PARSE) $(SRCS_BLTIN)

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

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
L_BLUE="\033[1;34m"
MUTED="\033[130m"
RESET="\033[0m"
BOLD="\033[1m"
L_PUPLE="\033[1;35m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"

########################## Rule ##########################

.PHONY			:	all
all				:	$(LIBFT_FILE) $(OBJ_FILES) $(NAME)

$(NAME)			: 	$(LIBFT_FILE) $(OBJ_FILES)
					@$(CC) $(CFLAGS) $(OBJ_FILES) $(RDLN_LFLAGS) $(RDLN_INC) $(LIBFT_FLAGS) -I$(INC_DIR) -o $@ 
					@printf $(CUT)$(DOWN)$(CUT)
					@echo $(CUT)$(UP)$(BOLD)$(L_PUPLE) 🚀 Elephant🐘 Shell Compiled 🥳$(RESET)

.PHONY			:	bonus
bonus			:
					@make WITH_BONUS=1 $(NAME)

%.o				: 	%.c
					@$(CC) $(CFLAGS) $(RDLN_INC) -I$(INC_DIR) -c $< -o $@
					@echo $(SAVE)$(CUT)$(BOLD)$(L_GREEN) Compiling with $(CFLAGS)...$(RESET)
					@echo $(CUT)$(GREEN) [$(notdir $^)] to [$(notdir $@)] $(RESET)
					@printf $(UP)$(UP)

$(LIBFT_FILE)	:
					@echo $(CUT)$(YELLOW) Get Library 🏃 $(RESET)
					@make -C $(LIBFT_DIR) bonus

.PHONY			:	clean
clean			:
					@rm -f $(OBJS_MAN) $(OBJS_BONUS)
					@make -C $(LIBFT_DIR) clean
					@echo $(L_RED) Remove🧹 OBJ files in minishell 👋 $(RESET)


.PHONY			:	fclean
fclean			:	clean
					@rm -f $(NAME)
					@make -C $(LIBFT_DIR) fclean
					@echo $(RED) Remove🧹 $(NAME)🦪 $(RESET)


.PHONY			:	ffclean
ffclean			:	fclean
					@rm -rf $(NAME).dSYM
					@echo $(RED) Remove🧹 $(NAME).dSYM 🎉 $(RESET)

.PHONY			:	re
re				:	fclean all

.PHONY			:	re_bonus
re_bonus		:	fclean bonus

.PHONY			:	debug
debug			: 
					@make -C $(LIBFT_DIR) DEBUG=1
					@make DEBUG=1
					@echo $(CUT)$(RED)$(BOLD) It\'s DEBUG TIME🤪$(RESET)

leaks			:
					@make -C $(LIBFT_DIR) LEAKS=1
					@make LEAKS=1
					@echo $(CUT)$(RED)$(BOLD) Is there Leaks?🚰$(RESET)

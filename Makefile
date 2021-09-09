# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongjule <yongjule@42student.42seoul.kr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:00:27 by yongjule          #+#    #+#              #
#    Updated: 2021/09/09 17:43:25 by ghan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address
#	CFLAGS = -g
else
	CFLAGS = -Wall -Wextra -Werror
endif

NAME		= minishell 

SRCS_DIR	= ./src/
#SRCS_DIR_BONUS = ./srcs/bonus/

LFLAGS		= -l readline
LIB_DIR		= lib/

LIBFT_DIR	= $(LIB_DIR)libft/
LIBFT_FLAGS	= -L./$(LIBFT_DIR) -lft
LIBFT_FILE	= $(LIBFT_DIR)libft.a

INC_DIR_MAN	= ./include/
#INC_DIR_BONUS = ./incs/bonus/

SRCS_MAN	= $(addprefix $(SRCS_DIR), \
			main.c\
	   )

SRCS_BONUS	= $(addprefix $(SRCS_DIR_BONUS), \
	   )

OBJS_MAN	= ${SRCS_MAN:%.c=%.o}

OBJS_BONUS	= ${SRCS_BONUS:%.c=%.o}

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
				$(CC) $(CFLAGS) $(OBJ_FILES) $(LFLAGS) $(LIBFT_FLAGS) -I$(INC_DIR) -o $@ 

.PHONY			: bonus
bonus			:
				@make WITH_BONUS=1 $(NAME)

%.o				: %.c
				$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

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
				@make DEBUG=1

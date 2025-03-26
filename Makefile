# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:34:27 by danpalac          #+#    #+#              #
#    Updated: 2025/03/26 11:26:18 by danpalac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==========COLOURS=============================================================#

# Basic Colors
BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

# Bright Colors
BOLD_BLACK  = \033[1;30m
BOLD_RED    = \033[1;31m
BOLD_GREEN  = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE   = \033[1;34m
BOLD_MAGENTA= \033[1;35m
BOLD_CYAN   = \033[1;36m
BOLD_WHITE  = \033[1;37m

# Extended Colors (256 colors)
ORANGE      = \033[38;5;208m
WINE        = \033[38;5;88m
LIME        = \033[38;5;190m
TURQUOISE   = \033[38;5;38m
LIGHT_PINK  = \033[38;5;13m
DARK_GRAY   = \033[38;5;235m
LIGHT_RED   = \033[38;5;203m
LIGHT_BLUE  = \033[38;5;75m

BRIGHT_BLUE = \033[38;5;27m
BRIGHT_GREEN= \033[38;5;46m
BRIGHT_YELLOW=\033[38;5;226m
BRIGHT_CYAN = \033[38;5;51m
BRIGHT_WHITE= \033[38;5;231m

# Reseteo de color
NO_COLOR    = \033[0m
DEF_COLOR   = \033[0;39m
CLEAR_LINE  = \033[2K
MOVE_UP     = \033[1A

#==========NAMES===============================================================#

NAME		:= libparse.a
EXE			:= exe
MEMTRACK_LIB:= libmt.a
LIBFT_LIB	:= libft.a

#==========DIRECTORIES=======================================================#

INC 			:= inc/
SRC_DIR 		:= src/

##

CHECK_FUNC_DIR  := check_func/
EXTRACT_FUNC_DIR:= extract_func/
NODE_FUNC_DIR	:= node_func/
PRINT_FUNC_DIR	:= print_func/
PROCESS_FUNC_DIR:= process_func/
STATE_FUNC_DIR	:= state_func/
TREE_FUNC_DIR	:= tree_func/

##
OBJ_DIR 		:= obj/
LIBFT_DIR		:= ../libft/
LIB_DIR			:= ../lib/
MEMTRACK_DIR 	:= ../memtrack/

MEMTRACK	:= $(MEMTRACK_DIR)$(MEMTRACK_LIB)
LIBFT		:= $(LIBFT_DIR)$(LIBFT_LIB)
SRC_DIR		:= src/
INCLUDES		:= $(INC)*.h

#==========COMMANDS============================================================#

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			:= rm -rf
AR			:= ar rcs
MKDIR 		:= mkdir -p
LIB 		:= -L$(LIB_DIR) -lmt -lft -lreadline
IFLAGS		:= -I$(LIB_DIR)$(INC) -I$(INC)
LFLAGS		:= $(LIB) -fsanitize=address

#==========SOURCES============================================================#

SRC_SOURCE	:= ft_validate ft_extend ft_parser ft_tokenizer ft_manage_signals ft_advanced_readline\

CHECK_FUNC_FILES := helpers_check_1 helpers_check_2 check_follow_commands check_follow_redout ft_check_swaps 
EXTRACT_FUNC_FILES := ft_extract_operator_token ft_extract_parentheses_token ft_extract_quoted_token \
					ft_extract_word_token ft_extract_expantion_token ft_extract_token
NODE_FUNC_FILES := helpers_node_1 helpers_priority
PRINT_FUNC_FILES := print_tokens print_tree
PROCESS_FUNC_FILES := ft_process_token ft_process_operator ft_process_expantion ft_process_parentheses ft_process_quote ft_process_redirection \
					ft_process_word ft_process_argument
STATE_FUNC_FILES := state_utils helpers_state helpers_state-1
TREE_FUNC_FILES := create_binary_tree endicize


#==========FILES==============================================================#

SRC_FILES +=$(addprefix $(SRC_DIR), $(SRC_SOURCE))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(CHECK_FUNC_DIR), $(CHECK_FUNC_FILES)))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(EXTRACT_FUNC_DIR), $(EXTRACT_FUNC_FILES)))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(NODE_FUNC_DIR), $(NODE_FUNC_FILES)))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(PRINT_FUNC_DIR), $(PRINT_FUNC_FILES)))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(PROCESS_FUNC_DIR), $(PROCESS_FUNC_FILES)))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(STATE_FUNC_DIR), $(STATE_FUNC_FILES)))
SRC_FILES +=$(addprefix $(SRC_DIR), $(addprefix $(TREE_FUNC_DIR), $(TREE_FUNC_FILES)))
SRCS := $(addsuffix .c, $(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS := $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

#==========RULES==============================================================#

-include $(DEPS)
all: $(NAME)

$(OBJ_DIR)%.o: %.c Makefile
	@$(MKDIR) $(dir $@)	
	@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) -MP -MMD -c $< -o $@

$(NAME): $(LIBFT) $(MEMTRACK) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(BOLD_BLUE)[$(BRIGHT_GREEN)$(NAME)$(DEF_COLOR)$(BOLD_BLUE)] compiled!$(DEF_COLOR)"
	@echo "$(TURQUOISE)------------\n| Done! 👌 |\n------------$(DEF_COLOR)"
	@mkdir -p $(LIB_DIR)
	@$(MKDIR) $(LIB_DIR) 
	@cp -r $(NAME) inc $(LIB_DIR)

$(EXE): main.c $(NAME)
	@$(CC) $(CFLAGS) $(LFLAGS) -L. $(IFLAGS)  main.c $(NAME) -lmt -lft -o $(EXE)
	@echo "$(BOLD_BLUE)[$(BRIGHT_GREEN)$(EXE)$(DEF_COLOR)$(BOLD_BLUE)] compiled!$(DEF_COLOR)"
	@echo "$(TURQUOISE)------------\n| Done! 👌 |\n------------$(DEF_COLOR)"

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MEMTRACK):
	@make -sC $(MEMTRACK_DIR)
	
clean:
	@make clean -sC $(LIBFT_DIR)	
	@make clean -sC $(MEMTRACK_DIR)
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) $(OBJ_DIR) $(LIB_DIR); \
		echo "$(CYAN)[$(NAME)]:\tobject files $(GREEN) => Cleaned!$(DEF_COLOR)"; \
	fi
	

fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@make fclean -sC $(MEMTRACK_DIR)
	@$(RM) $(NAME) $(EXE)

re: fclean all

.SILENT: all clean fclean
.PHONY: all clean fclean re
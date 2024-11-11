# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:34:27 by danpalac          #+#    #+#              #
#    Updated: 2024/11/11 01:39:49 by danpalac         ###   ########.fr        #
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

NAME		:= memtrack.a
EXEC		:= exec

#==========DIRECTORIES=======================================================#

INC 			:= inc/
SRC_DIR 		:= src/
OBJ_DIR 		:= obj/

ALLOC_DIR		:= alloc/
DEALLOC_DIR		:= dealloc/
MEMTRACK_DIR	:= memtrack/

#==========COMMANDS============================================================#

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			:= rm -rf
AR			:= ar rcs
LIB			:= ranlib
MKDIR 		:= mkdir -p
IFLAGS		:= -I$(INC)
LFLAGS		:= -L.

#==========SOURCES============================================================#

ALLOC_FILES		:= #mt_calloc mt_malloc mt_realloc mt_strdup mt_strndup
DEALLOC_FILES	:= #mt_free mt_free_all mt_free_node mt_free_list
MEMTRACK_FILES	:= ft_mtnew

#==========FILES==============================================================#

SRC_FILES+=$(addprefix $(MEMTRACK_DIR), $(MEMTRACK_FILES))

SRCS := $(addsuffix .c, $(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS := $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

#==========RULES==============================================================#

all: $(NAME)
-include $(DEPS)

$(OBJ_DIR)%.o: %.c Makefile
	@$(MKDIR) $(dir $@)	
	@$(CC) $(CFLAGS) $(IFLAGS) -MP -MMD -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(LIB) $(NAME)
	@echo "$(BOLD_BLUE)[$(BRIGHT_GREEN)$(NAME)$(DEF_COLOR)$(BOLD_BLUE)] compiled!$(DEF_COLOR)"
	@echo "$(TURQUOISE)------------\n| Done! 👌 |\n------------$(DEF_COLOR)"

exe: $(NAME)
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o exec main.c $(NAME)
	@echo "$(BOLD_BLUE)[$(BRIGHT_GREEN)$(EXEC)$(DEF_COLOR)$(BOLD_BLUE)] compiled!$(DEF_COLOR)"
	@echo "$(TURQUOISE)------------\n| Done! 👌 |\n------------$(DEF_COLOR)"

clean:
	@$(RM) -rf $(OBJ_DIR) $(DEPS)
	@echo "$(CYAN)[$(NAME)]:\tobject files $(GREEN) => Cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) -rf $(NAME) $(EXEC)
	@echo "$(CYAN)[$(NAME)]:\texec. files $(GREEN) => Cleaned!$(DEF_COLOR)"

re: fclean all

.SILENT: all clean fclean
.PHONY: all clean fclean re bonus

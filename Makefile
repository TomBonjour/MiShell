# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tobourge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:17:36 by tobourge          #+#    #+#              #
#    Updated: 2025/04/22 17:17:50 by tobourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------------------CFLAGS---------------------------------------------------#
CFLAGS = -g -Wall -Wextra -Werror

#-------------------------------------------------------LIBRARY--------------------------------------------------#
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
DPRINTF_PATH = ft_dprintf
DPRINTF = $(DPRINTF_PATH)/dprintf.a

#-------------------------------------------------------SRCS----------------------------------------------------#
SRCS = main.c \
	   parsing/tokenizer/ft_tokenizer.c \
	   parsing/tokenizer/utils_tokenize.c \
	   parsing/tokenizer/token_redir.c \
	   parsing/tokenizer/token_heredoc.c \
	   parsing/expander/ft_syntaxer.c \
	   parsing/expander/ft_expander.c \
	   parsing/expander/utils_expand.c \
	   parsing/expander/utils_expand2.c \
	   parsing/expander/utils_expand3.c \
	   parsing/expander/utils_quote.c \
	   parsing/heredoc/heredoc.c \
	   parsing/heredoc/heredoc2.c \
	   parsing/heredoc/expand_heredoc.c \
	   builtin/echo.c \
	   builtin/cd.c \
	   builtin/env_pwd.c \
	   builtin/unset.c \
	   builtin/export.c \
	   builtin/export2.c \
	   builtin/exit.c \
	   builtin/utils_builtin.c \
	   signals/signals.c \
	   signals/signals2.c \
	   signals/signals_init.c \
	   utils/utils_generals.c \
	   utils/utils_generals2.c \
	   utils/utils_generals3.c \
	   utils/utils_generals4.c \
	   utils/utils_generals5.c \
	   utils/utils_list.c \
	   utils/utils_list2.c \
	   exec/exec_cmd.c \
	   exec/exec_cmd2.c \
	   exec/exec_cmd3.c \
	   exec/exec_utils.c \
	   exec/parsing_path.c \
	   exec/exec_redir.c
#-------------------------------------------------------OBJECTS--------------------------------------------------#
OBJ = $(SRCS:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# Calculate total objects
OBJS_TOTAL := $(words $(SRCS))
CURR_OBJ := 0

#-------------------------------------------------------INCLUDES------------------------------------------------#
INC_DIR = includes
INCS = -I $(LIBFT_PATH) -I $(DPRINTF_PATH) -I $(INC_DIR) 
#-------------------------------------------------------LDFLAGS--------------------------------------------------#
LDFLAGS = -L /usr/local/lib -l readline

#-------------------------------------------------------NAME-----------------------------------------------------#
NAME = minishell

#-------------------------------------------------------COLORS--------------------------------------------------#
BOLD = \033[1m
RESET = \033[0m
CYAN = \033[36m
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
DEFAULT = \033[39m
BLUE = "\e[34m"
DEFAULT2 = "\e[39m"
#-------------------------------------------------------RULES---------------------------------------------------#

.PHONY: all clean fclean re $(LIBFT) $(DPRINTF)

# Default target to build the project
all: $(NAME)

# Build the file descriptor printf
$(DPRINTF):
	@make --no-print-directory -C $(DPRINTF_PATH) -j

# Build the libft library
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH) -j

# Link the objects and create the executable
$(NAME): $(OBJS) $(LIBFT) $(DPRINTF)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(INCS) $(OBJS) $(DPRINTF) $(LIBFT) -o $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	@$(eval CURR_OBJ=$(shell echo $$(($(CURR_OBJ) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURR_OBJ) * 100 / $(OBJS_TOTAL)))))
	@ \
	if [ $(PERCENT) -lt 25 ]; then \
		COLOR="$(RED)"; \
	elif [ $(PERCENT) -lt 50 ]; then \
		COLOR="$(YELLOW)"; \
	elif [ $(PERCENT) -lt 75 ]; then \
		COLOR="$(CYAN)"; \
	else \
		COLOR="$(GREEN)"; \
	fi; \
	printf "$${COLOR}($(BOLD)%3s%%$(RESET)$${COLOR})$(RESET) Compiling $(BOLD)$<$(RESET)\n" "$(PERCENT)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@; 

# Clean object files and temporary files
clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(DPRINTF_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "$(YELLOW)>>> Minishell is cleaned 🧹 <<<$(DEFAULT)"

# Fully clean the project (including executable and libft)
fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(DPRINTF_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)>>> Minishell is fully cleaned 🧼 <<<$(DEFAULT)"

re: fclean all

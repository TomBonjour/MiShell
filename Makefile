
#-------------------------------------------------------CFLAGS---------------------------------------------------#
CFLAGS = -g -Wall -Wextra -Werror

#-------------------------------------------------------LIBRARY--------------------------------------------------#
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

#-------------------------------------------------------SRCS----------------------------------------------------#
SRCS =	main.c \
			parsing/ft_tokenizer.c \
			parsing/ft_syntaxer.c \
			parsing/ft_expander.c \
			parsing/utils_parsing.c \
			parsing/utils_tokenize.c \
			parsing/utils_list.c \
			parsing/utils_generals.c \
			builtin/echo_exit.c \
			builtin/env_exp_unset.c \
			builtin/pwd_cd.c \
			builtin/unset.c \
			signals/signals.c

#-------------------------------------------------------OBJECTS--------------------------------------------------#
OBJ = $(SRCS:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# Calculate total objects
OBJS_TOTAL := $(words $(SRCS))
CURR_OBJ := 0

#-------------------------------------------------------INCLUDES------------------------------------------------#
INC_DIR = includes
INCS = -I $(LIBFT_PATH) -I $(INC_DIR)

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

.PHONY: all clean fclean re $(LIBFT)

# Default target to build the project
all: $(NAME)

# Build the libft library
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH) -j

# Link the objects and create the executable
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(INCS) $(OBJS) $(LIBFT) -o $(NAME)

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
	@rm -rf $(OBJ_PATH)
	@echo "$(YELLOW)>>> Minishell is cleaned 🧹 <<<$(DEFAULT)"

# Fully clean the project (including executable and libft)
fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)>>> Minishell is fully cleaned 🧼 <<<$(DEFAULT)"

re: fclean all

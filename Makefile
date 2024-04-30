NAME		= ft_ls
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
LIBFT		= libft/libft.a
INC			= ./includes/
SRC_DIRS 	= ./src/ ./src/flags/
OBJ_DIR		= ./objects
NAME		= ft_ls
SRC			= $(wildcard src/*.c src/flags/*.c)
OBJS		= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(OBJ_DIR):
	@echo "$(YELLOW)Creating: $(DEF_COLOR)$(CYAN)OBJ_DIR$(DEF_COLOR)"
	mkdir -p $(OBJ_DIR)/src
	mkdir -p $(OBJ_DIR)/src/flags
	@echo "$(GREEN)DONE$(DEF_COLOR)"
	@echo ""
	@echo "$(YELLOW)Creating: $(DEF_COLOR)$(CYAN)OBJ_FILES$(DEF_COLOR)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "$(GREEN)DONE$(DEF_COLOR)"
	@echo ""
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(CYAN)FT_LS $(DEF_COLOR)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(GREEN)DONE$(DEF_COLOR)"
	@echo ""

$(LIBFT):
	@echo ""
	@echo "$(PURPLE)Updating: $(DEF_COLOR)$(CYAN)SUBMODULE$(DEF_COLOR)"
	@git submodule update --init --recursive --remote
	@echo "$(GREEN)DONE$(DEF_COLOR)"
	@echo ""
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(CYAN)LIBFT$(DEF_COLOR)"
	make -C ./libft
	@echo "$(GREEN)DONE$(DEF_COLOR)"
	@echo ""

clean:
	@echo ""
	@echo "$(RED)Cleaning: $(DEF_COLOR)$(CYAN)OBJ_DIR$(DEF_COLOR)"
	rm -rf $(OBJ_DIR)
	make -C ./libft clean
	@echo "$(GREEN)DONE$(DEF_COLOR)"

fclean: clean
	@echo ""
	@echo "$(RED)FCleaning: $(DEF_COLOR)$(CYAN)EVERYTHING$(DEF_COLOR)"
	rm -f $(NAME)
	make -C ./libft fclean
	@echo "$(GREEN)DONE$(DEF_COLOR)"
	@echo ""

re: fclean all

DEF_COLOR = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[0;91m
GREEN = \033[0;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m

.PHONY: all clean fclean re